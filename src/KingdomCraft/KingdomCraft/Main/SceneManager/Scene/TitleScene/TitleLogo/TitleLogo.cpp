/**
 * @file TitleLogo.cpp
 * @brief TitleLogoクラス実装
 * @author morimoto
 */
#include "TitleLogo.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 TitleLogo::m_TitleLogoPos = D3DXVECTOR2(640, 100);
const D3DXVECTOR2 TitleLogo::m_TitleLogoSize = D3DXVECTOR2(400, 100);
const D3DXVECTOR2 TitleLogo::m_TitleLogoTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


TitleLogo::TitleLogo() :
m_TextureIndex(TextureManager::m_InvalidIndex)
{
	TextureManager::GetInstance()->LoadTexture(TEXT("Resource\\Texture\\TitleScene\\TitleLogo.png"), &m_TextureIndex);

	m_pVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init(&m_TitleLogoSize, m_TitleLogoTexel);
	m_pVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

TitleLogo::~TitleLogo()
{
	m_pVertex->Release();
	delete m_pVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void TitleLogo::Control()
{
}

void TitleLogo::Draw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex->Draw(&D3DXVECTOR2(m_TitleLogoPos));
	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}
