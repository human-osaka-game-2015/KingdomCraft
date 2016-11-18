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


TitleLogo::TitleLogo() :
m_TextureIndex(-1)	/// @todo TextureManagerクラスの定数を作るまで-1は仮置きしとく
{
	RECT VertexRect;
	VertexRect.left = 0;
	VertexRect.right = static_cast<LONG>(m_TitleLogoSize.x);
	VertexRect.top = 0;
	VertexRect.bottom = static_cast<LONG>(m_TitleLogoSize.y);

	D3DXVECTOR2 UV[4];
	UV[0] = D3DXVECTOR2(0, 0);
	UV[1] = D3DXVECTOR2(1, 0);
	UV[2] = D3DXVECTOR2(0, 1);
	UV[3] = D3DXVECTOR2(1, 1);


	m_pVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init(&VertexRect, UV);


	TextureManager::GetInstance()->LoadTexture(TEXT("Resource\\Texture\\TitleScene\\TitleLogo\\TitleLogo.png"), &m_TextureIndex);
	m_pVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

TitleLogo::~TitleLogo()
{
	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
	m_pVertex->Release();
	delete m_pVertex;
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
