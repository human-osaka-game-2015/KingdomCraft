/**
 * @file   Ground.cpp
 * @brief  Groundクラスの実装
 * @author kotani
 */
#include "Ground.h"
#include "FbxFileManager\FbxFileManager.h"
#include "ShaderManager\ShaderManager.h"
#include "DX11Manager\DX11Manager.h"


Ground::Ground()
{
	FbxFileManager::GetInstance()->LoadFbxModel(TEXT("Resource\\Fbx\\GameScene\\Ground.fbx"), &m_ModelIndex);
	ShaderManager::GetInstance()->LoadVertexShader(TEXT("Resource\\Effect\\GameScene\\Ground.fx"), "VS", &m_VertexShaderIndex);
	ShaderManager::GetInstance()->LoadPixelShader(TEXT("Resource\\Effect\\GameScene\\Ground.fx"), "PS", &m_PixelShaderIndex);
	InitVertexLayout();
	InitDepthStencilState();
	InitConstantBuffer();
	WriteConstantBuffer();
}

Ground::~Ground()
{
	ReleaseConstantBuffer();
	ReleaseDepthStencilState();
	ReleaseVertexLayout();
	ShaderManager::GetInstance()->ReleasePixelShader(m_PixelShaderIndex);
	ShaderManager::GetInstance()->ReleaseVertexShader(m_VertexShaderIndex);
	FbxFileManager::GetInstance()->ReleaseFbxModel(m_ModelIndex);
}

void Ground::Control()
{
}

void Ground::Draw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
	DX11Manager::GetInstance()->GetDeviceContext()->IASetInputLayout(m_pVertexLayout);
	DX11Manager::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->VSSetShader(ShaderManager::GetInstance()->GetVertexShader(m_VertexShaderIndex), NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetShader(ShaderManager::GetInstance()->GetPixelShader(m_PixelShaderIndex), NULL, 0);
	DX11Manager::GetInstance()->GetDeviceContext()->OMSetDepthStencilState(m_pDepthStencilState, 0);
	FbxFileManager::GetInstance()->GetFbxModel(m_ModelIndex)->Draw();
}

void Ground::WriteConstantBuffer()
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

void Ground::InitVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, sizeof(D3DXVECTOR3), D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(D3DXVECTOR3) + sizeof(D3DXVECTOR3), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	DX11Manager::GetInstance()->GetDevice()->CreateInputLayout(
		InputElementDesc,
		sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
		ShaderManager::GetInstance()->GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferPointer(),
		ShaderManager::GetInstance()->GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferSize(),
		&m_pVertexLayout);
}

void Ground::InitDepthStencilState()
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

void Ground::InitConstantBuffer()
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
		MessageBox(DX11Manager::GetInstance()->GetWindowHandle(), TEXT("GroundクラスのConstantBufferの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
	}
}

void Ground::ReleaseVertexLayout()
{
	if (m_pVertexLayout != NULL)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = NULL;
	}
}

void Ground::ReleaseDepthStencilState()
{
	if (m_pDepthStencilState != NULL)
	{
		m_pDepthStencilState->Release();
		m_pDepthStencilState = NULL;
	}
}

void Ground::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}
