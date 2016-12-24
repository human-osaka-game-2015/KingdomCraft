/**
 * @file   KingdomParameterUI.cpp
 * @brief  KingdomParameterUIクラスの実装
 * @author morimoto
 */
#include "KingdomParameterUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 KingdomParameterUI::m_ParameterPos = D3DXVECTOR2(110, 10);
const D3DXVECTOR2 KingdomParameterUI::m_ParameterSize = D3DXVECTOR2(100, 100);
const D3DXVECTOR2 KingdomParameterUI::m_ParameterTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


KingdomParameterUI::KingdomParameterUI(const D3DXVECTOR2* _pParentPos) :
m_ParameterTextureIndex(TextureManager::m_InvalidIndex),
m_pParameterVertex(NULL),
m_ParentUIPos(*_pParentPos)
{
	TextureManager::GetInstance()->LoadTexture("File", &m_ParameterTextureIndex);

	m_pParameterVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pParameterVertex->Init(&m_ParameterSize, m_ParameterTexel);
	m_pParameterVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_ParameterTextureIndex));
	m_pParameterVertex->WriteConstantBuffer(&D3DXVECTOR2(m_ParameterPos + m_ParentUIPos));
}

KingdomParameterUI::~KingdomParameterUI()
{
	m_pParameterVertex->Release();
	delete m_pParameterVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_ParameterTextureIndex);
}

void KingdomParameterUI::Control()
{
}

void KingdomParameterUI::Draw()
{
	m_pParameterVertex->Draw();
}
