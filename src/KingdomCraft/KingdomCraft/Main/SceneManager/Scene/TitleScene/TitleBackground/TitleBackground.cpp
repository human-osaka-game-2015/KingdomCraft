/**
 * @file TitleBackground.cpp
 * @brief TitleBackgroundクラス実装
 * @author morimoto
 */
#include "TitleBackground.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 TitleBackground::m_TitleBackgroundPos = D3DXVECTOR2(640, 360);
const D3DXVECTOR2 TitleBackground::m_TitleBackgroundSize = D3DXVECTOR2(1280, 720);
const D3DXVECTOR2 TitleBackground::m_TitleBackgroundTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


TitleBackground::TitleBackground() :
m_TextureIndex(TextureManager::m_InvalidIndex)
{
	TextureManager::GetInstance()->LoadTexture(TEXT("Resource\\Texture\\TitleScene\\TitleBackground.png"), &m_TextureIndex);

	m_pVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init(&m_TitleBackgroundSize, m_TitleBackgroundTexel);
	m_pVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

TitleBackground::~TitleBackground()
{
	m_pVertex->Release();
	delete m_pVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void TitleBackground::Control()
{
}

void TitleBackground::Draw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex->Draw(&D3DXVECTOR2(m_TitleBackgroundPos));
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}
