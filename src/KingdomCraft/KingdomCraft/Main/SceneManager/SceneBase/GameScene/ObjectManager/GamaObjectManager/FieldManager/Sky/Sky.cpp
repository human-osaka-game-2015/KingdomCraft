/**
 * @file   Sky.cpp
 * @brief  Skyクラスの実装
 * @author kotani
 */
#include "Sky.h"
#include "FbxFileManager\FbxFileManager.h"
#include "ShaderManager\ShaderManager.h"
#include "DX11Manager\DX11Manager.h"


Sky::Sky()
{
	FbxFileManager::GetInstance()->LoadFbxModel(TEXT("Resource\\Fbx\\GameScene\\Sky.fbx"), &m_ModelIndex);
	ShaderManager::GetInstance()->LoadVertexShader(TEXT("Resource\\Effect\\GameScene\\Sky.fx"), "VS", &m_VertexShaderIndex);
	ShaderManager::GetInstance()->LoadPixelShader(TEXT("Resource\\Effect\\GameScene\\Sky.fx"), "PS", &m_PixelShaderIndex);
	InitDepthStencilState();
	InitVertexLayout();
	InitConstantBuffer(sizeof(MODEL_CONSTANT_BUFFER), &m_pConstantBuffer);
	WriteConstantBuffer();
}

Sky::~Sky()
{
	ReleaseConstantBuffer();
	ReleaseVertexLayout();
	ReleaseDepthStencilState();
	ShaderManager::GetInstance()->ReleasePixelShader(m_PixelShaderIndex);
	ShaderManager::GetInstance()->ReleaseVertexShader(m_VertexShaderIndex);
	FbxFileManager::GetInstance()->ReleaseFbxModel(m_ModelIndex);
}

void Sky::Control()
{
}

void Sky::Draw()
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

void Sky::InitVertexLayout()
{
	D3D11_INPUT_ELEMENT_DESC InputElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, sizeof(D3DXVECTOR3), D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	DX11Manager::GetInstance()->GetDevice()->CreateInputLayout(
		InputElementDesc,
		sizeof(InputElementDesc) / sizeof(InputElementDesc[0]),
		ShaderManager::GetInstance()->GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferPointer(),
		ShaderManager::GetInstance()->GetCompiledVertexShader(m_VertexShaderIndex)->GetBufferSize(),
		&m_pVertexLayout);
}

void Sky::WriteConstantBuffer()
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

void Sky::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}
