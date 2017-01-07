/**
 * @file   GameObjectBase.cpp
 * @brief  GameObjectBaseクラスの実装
 * @author kotani
 */
#include "GameObjectBase.h"
#include "DX11Manager\DX11Manager.h"
#include "ShaderManager\ShaderManager.h"


GameObjectBase::GameObjectBase()
{
}

GameObjectBase::~GameObjectBase()
{
}

void GameObjectBase::InitConstantBuffer(UINT _constantBufferByteSize, ID3D11Buffer** _ppConstantBuffer)
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ConstantBufferDesc.ByteWidth = _constantBufferByteSize;
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.StructureByteStride = 0;

	if (FAILED(DX11Manager::GetInstance()->GetDevice()->CreateBuffer(&ConstantBufferDesc, NULL, _ppConstantBuffer)))
	{
		MessageBox(DX11Manager::GetInstance()->GetWindowHandle(), TEXT("ConstantBufferの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
	}
}

void GameObjectBase::InitDepthStencilState()
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

void GameObjectBase::ReleaseVertexLayout()
{
	if (m_pVertexLayout != NULL)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = NULL;
	}
}

void GameObjectBase::ReleaseDepthStencilState()
{
	if (m_pDepthStencilState != NULL)
	{
		m_pDepthStencilState->Release();
		m_pDepthStencilState = NULL;
	}
}
