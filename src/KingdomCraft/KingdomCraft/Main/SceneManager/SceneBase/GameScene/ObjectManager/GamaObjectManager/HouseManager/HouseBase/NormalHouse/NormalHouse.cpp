/**
 * @file   NormalHouse.cpp
 * @brief  NormalHouseクラスの実装
 * @author morimoto
 */
#include "NormalHouse.h"
#include "DX11Manager\DX11Manager.h"
#include "FbxFileManager\FbxFileManager.h"
#include "ShaderManager\ShaderManager.h"


NormalHouse::NormalHouse(const D3DXVECTOR3* _pHousePos, float _houseAngle, int _modelIndex, int _vertexShaderIndex, int _pixelShaderIndex) :
HouseBase(_pHousePos, _houseAngle),
m_ModelIndex(_modelIndex),
m_VertexShaderIndex(_vertexShaderIndex),
m_PixelShaderIndex(_pixelShaderIndex)
{
	InitVertexLayout();
	InitDepthStencilState();
	InitConstantBuffer();
	WriteConstantBuffer();
}

NormalHouse::~NormalHouse()
{
	ReleaseConstantBuffer();
	ReleaseDepthStencilState();
	ReleaseVertexLayout();
}

void NormalHouse::Control()
{
}

void NormalHouse::Draw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(true);

	DX11Manager::GetInstance()->GetDeviceContext()->VSSetShader(ShaderManager::GetInstance()->GetVertexShader(m_VertexShaderIndex), NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetShader(ShaderManager::GetInstance()->GetPixelShader(m_PixelShaderIndex), NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->OMSetDepthStencilState(m_pDepthStencilState, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->HSSetShader(NULL, NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->DSSetShader(NULL, NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->GSSetShader(NULL, NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->CSSetShader(NULL, NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);

	FbxFileManager::GetInstance()->GetFbxModel(m_ModelIndex)->Draw();
}

void NormalHouse::InitVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,                                         D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL",   0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(D3DXVECTOR3),                       D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,    0, sizeof(D3DXVECTOR3) + sizeof(D3DXVECTOR3), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	if (FAILED(DX11Manager::GetInstance()->GetDevice()->CreateInputLayout(
		InputElementDesc,
		sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
		ShaderManager::GetInstance()->GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferPointer(),
		ShaderManager::GetInstance()->GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferSize(),
		&m_pVertexLayout)))
	{
		MessageBox(
			DX11Manager::GetInstance()->GetWindowHandle(), 
			TEXT("NormalHouseクラスのVertexLayoutの生成に失敗しました"), 
			TEXT("エラー"),
			MB_ICONSTOP);
	}
}

void NormalHouse::InitDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
	ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc));
	DepthStencilDesc.DepthEnable = TRUE;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthStencilDesc.StencilEnable = FALSE;

	if (FAILED(DX11Manager::GetInstance()->GetDevice()->CreateDepthStencilState(&DepthStencilDesc, &m_pDepthStencilState)))
	{
		MessageBox(
			DX11Manager::GetInstance()->GetWindowHandle(), 
			TEXT("DepthStencilStateの生成に失敗しました"), 
			TEXT("エラー"), 
			MB_ICONSTOP);
	}
}

void NormalHouse::InitConstantBuffer()
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ConstantBufferDesc.ByteWidth = sizeof(MODEL_CONSTANT_BUFFER);
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.StructureByteStride = 0;

	if (FAILED(DX11Manager::GetInstance()->GetDevice()->CreateBuffer(&ConstantBufferDesc, NULL, &m_pConstantBuffer)))
	{
		MessageBox(
			DX11Manager::GetInstance()->GetWindowHandle(), 
			TEXT("NormalHouseクラスのConstantBufferの生成に失敗しました"), 
			TEXT("エラー"), 
			MB_ICONSTOP);
	}
}

void NormalHouse::WriteConstantBuffer()
{
	D3D11_MAPPED_SUBRESOURCE SubResourceData;
	if (SUCCEEDED(DX11Manager::GetInstance()->GetDeviceContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResourceData)))
	{
		D3DXMATRIX World, PositionMatrix;
		D3DXMatrixIdentity(&World);
		D3DXMatrixIdentity(&PositionMatrix);
		D3DXMatrixTranslation(&PositionMatrix, m_HousePos.x, m_HousePos.y, m_HousePos.z);
		D3DXMatrixMultiply(&World, &World, &PositionMatrix);

		MODEL_CONSTANT_BUFFER ConstantBuffer;
		ConstantBuffer.World = World;
		D3DXMatrixTranspose(&ConstantBuffer.World, &ConstantBuffer.World);
		memcpy_s(SubResourceData.pData, SubResourceData.RowPitch, static_cast<void*>(&ConstantBuffer), sizeof(ConstantBuffer));
		DX11Manager::GetInstance()->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);
	}
}

void NormalHouse::ReleaseVertexLayout()
{
	if (m_pVertexLayout != NULL)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = NULL;
	}
}

void NormalHouse::ReleaseDepthStencilState()
{
	if (m_pDepthStencilState != NULL)
	{
		m_pDepthStencilState->Release();
		m_pDepthStencilState = NULL;
	}
}

void NormalHouse::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}

