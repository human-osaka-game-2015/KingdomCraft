/**
 * @file   Road.cpp
 * @brief  Roadクラスの実装
 * @author kotani
 */
#include "Road.h"
#include "DX11Manager\DX11Manager.h"
#include "ShaderManager\ShaderManager.h"

const float Road::m_RoadHeight = 0.25;
const float Road::m_RoadWidth = 0.25;


Road::Road(int _vertexShaderIndex, int _pixelShaderIndex, D3DXVECTOR3* _pStartPos, D3DXVECTOR3* _pEndPos) :
m_VertexShaderIndex(_vertexShaderIndex),
m_PixelShaderIndex(_pixelShaderIndex),
m_StartPos(*_pStartPos),
m_EndPos(*_pEndPos)
{
	float length = sqrt(
		(m_EndPos.x - m_StartPos.x) * (m_EndPos.x - m_StartPos.x) +
		(m_EndPos.z - m_StartPos.z) * (m_EndPos.z - m_StartPos.z));

	int DividNum = static_cast<int>(length / m_RoadHeight);
	CreateVertex(DividNum);

	InitVertexLayout();
	InitVertexBuffer();
	InitDepthStencilState();
	InitConstantBuffer();
	WriteConstantBuffer();
}

Road::~Road()
{
	ReleaseConstantBuffer();
	ReleaseDepthStencilState();
	ReleaseVertexBuffer();
	ReleaseVertexLayout();
	delete[] m_pRightLinePos;
	delete[] m_pLeftLinePos;
	delete[] m_pVertex;
	delete[] m_pAngle;
}

void Road::Control()
{
}

void Road::Draw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
	DX11Manager::GetInstance()->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
	DX11Manager::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->VSSetShader(ShaderManager::GetInstance()->GetVertexShader(m_VertexShaderIndex), NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetShader(ShaderManager::GetInstance()->GetPixelShader(m_PixelShaderIndex), NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->OMSetDepthStencilState(m_pDepthStencilState, 0);
	UINT Stride = sizeof(VERTEX);
	UINT Offset = 0;
	DX11Manager::GetInstance()->GetDeviceContext()->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &Stride, &Offset);
	DX11Manager::GetInstance()->GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	DX11Manager::GetInstance()->GetDeviceContext()->Draw(m_VertexNum, 0);
}

void Road::CreateVertex(int _dividNum)
{
	CreateCenterPos(_dividNum);
	CreateAngle(_dividNum);

	m_VertexNum = _dividNum * 2;
	m_pVertex = new VERTEX[m_VertexNum];
	m_pLeftLinePos = new D3DXVECTOR3[_dividNum];
	m_pRightLinePos = new D3DXVECTOR3[_dividNum];

	for (int i = 0; i < _dividNum; i++)
	{
		D3DXVECTOR3 p;
		p.x = m_CenterLinePos[i].x + -(m_RoadHeight / 2) * sin(m_pAngle[i]);
		p.y = 0.1f;
		p.z = m_CenterLinePos[i].z + -(m_RoadHeight / 2) * -cos(m_pAngle[i]);
		m_pLeftLinePos[i] = p;

		p.x = m_CenterLinePos[i].x + (m_RoadHeight / 2) * sin(m_pAngle[i]);
		p.z = m_CenterLinePos[i].z + (m_RoadHeight / 2) * -cos(m_pAngle[i]);
		m_pRightLinePos[i] = p;
	}

	for (int i = 0; i < _dividNum; i++)
	{
		m_pVertex[i * 2].Pos = m_pRightLinePos[i];
		m_pVertex[i * 2 + 1].Pos = m_pLeftLinePos[i];
	}
}

void Road::CreateCenterPos(int _dividNum)
{
	m_CenterLinePos.resize(_dividNum);
	float dx = m_EndPos.x - m_StartPos.x;
	float dy = m_EndPos.z - m_StartPos.z;
	float angle = atan2(dy, dx) + static_cast<float>(D3DXToRadian(90.f));

	m_CenterLinePos[0] = m_StartPos;
	m_CenterLinePos[0].y = 0.05f;

	for (int i = 1; i < _dividNum; i++)
	{
		m_CenterLinePos[i].x = m_CenterLinePos[i - 1].x + m_RoadHeight * sin(angle);
		m_CenterLinePos[i].z = m_CenterLinePos[i - 1].z + m_RoadHeight * -cos(angle);
		m_CenterLinePos[i].y = 0.05f;
	}
}

void Road::CreateAngle(int _dividNum)
{
	m_pAngle = new float[_dividNum];

	for (int i = 0; i < _dividNum - 1; i++)
	{
		m_pAngle[i] =
			atan2(m_CenterLinePos[i + 1].z - m_CenterLinePos[i].z,
			m_CenterLinePos[i + 1].x - m_CenterLinePos[i].x);
	}
	m_pAngle[_dividNum - 1] =
		atan2(m_CenterLinePos[_dividNum - 1].z - m_CenterLinePos[_dividNum - 2].z,
		m_CenterLinePos[_dividNum - 1].x - m_CenterLinePos[_dividNum - 2].x);
}

void Road::InitVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	if (FAILED(DX11Manager::GetInstance()->GetDevice()->CreateInputLayout(
		InputElementDesc,
		sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
		ShaderManager::GetInstance()->GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferPointer(),
		ShaderManager::GetInstance()->GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferSize(),
		&m_pVertexLayout)))
	{
		MessageBox(DX11Manager::GetInstance()->GetWindowHandle(), TEXT("SkyクラスのVertexLayoutの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
	}
}

void Road::InitVertexBuffer()
{
	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
	BufferDesc.ByteWidth = sizeof(VERTEX) * m_VertexNum;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA InitVertexData;
	ZeroMemory(&InitVertexData, sizeof(D3D11_SUBRESOURCE_DATA));
	InitVertexData.pSysMem = m_pVertex;
	if (FAILED(DX11Manager::GetInstance()->GetDevice()->CreateBuffer(&BufferDesc, &InitVertexData, &m_pVertexBuffer)))
	{
		MessageBox(DX11Manager::GetInstance()->GetWindowHandle(), TEXT("VertexBufferの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
	}
}

void Road::InitDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
	ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc));
	DepthStencilDesc.DepthEnable = TRUE;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthStencilDesc.StencilEnable = FALSE;

	if (FAILED(DX11Manager::GetInstance()->GetDevice()->CreateDepthStencilState(&DepthStencilDesc, &m_pDepthStencilState)))
	{
		MessageBox(DX11Manager::GetInstance()->GetWindowHandle(), TEXT("DepthStencilStateの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
	}
}

void Road::InitConstantBuffer()
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	ConstantBufferDesc.ByteWidth = sizeof(MODEL_CONSTANT_BUFFER);
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.StructureByteStride = 0;

	DX11Manager::GetInstance()->GetDevice()->CreateBuffer(&ConstantBufferDesc, NULL, &m_pConstantBuffer);
}

void Road::WriteConstantBuffer()
{
	D3D11_MAPPED_SUBRESOURCE SubResourceData;
	if (SUCCEEDED(DX11Manager::GetInstance()->GetDeviceContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResourceData)))
	{
		D3DXMATRIX World;
		D3DXMatrixIdentity(&World);
		MODEL_CONSTANT_BUFFER ConstantBuffer;
		ConstantBuffer.World = World;
		D3DXMatrixTranspose(&ConstantBuffer.World, &ConstantBuffer.World);
		memcpy_s(SubResourceData.pData, SubResourceData.RowPitch, reinterpret_cast<void*>(&ConstantBuffer), sizeof(ConstantBuffer));
		DX11Manager::GetInstance()->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);
	}
}

void Road::ReleaseVertexLayout()
{
	if (m_pVertexLayout != NULL)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = NULL;
	}
}

void Road::ReleaseVertexBuffer()
{
	if (m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
}

void Road::ReleaseDepthStencilState()
{
	if (m_pDepthStencilState != NULL)
	{
		m_pDepthStencilState->Release();
		m_pDepthStencilState = NULL;
	}
}

void Road::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}
