/**
 * @file   KingdomParameterUI.cpp
 * @brief  KingdomParameterUIクラスの実装
 * @author morimoto
 */
#include "KingdomParameterUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 KingdomParameterUI::m_ParameterPos = D3DXVECTOR2(1100, 100);
const D3DXVECTOR2 KingdomParameterUI::m_ParameterSize = D3DXVECTOR2(100, 100);
const D3DXVECTOR2 KingdomParameterUI::m_ParameterTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


KingdomParameterUI::KingdomParameterUI()
{
	TextureManager::GetInstance()->LoadTexture("File", &m_TextureIndex);

	m_pVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init(&m_ParameterSize, m_ParameterTexel);
}

KingdomParameterUI::~KingdomParameterUI()
{
	m_pVertex->Release();
	delete m_pVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void KingdomParameterUI::Control()
{
}

void KingdomParameterUI::Draw()
{
	m_pVertex->Draw(&m_ParameterPos);
}
