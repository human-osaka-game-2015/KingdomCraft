/**
 * @file TitleBackground.cpp
 * @brief TitleBackgroundクラス実装
 * @author morimoto
 */
#include "TitleBackground.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include "Vertex2D\Vertex2D.h"

const D3DXVECTOR2 TitleBackground::m_Pos = D3DXVECTOR2(640, 360);
const D3DXVECTOR2 TitleBackground::m_Size = D3DXVECTOR2(1280, 720);
const D3DXVECTOR2 TitleBackground::m_Texel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


TitleBackground::TitleBackground() :
m_pVertex2D(NULL),
m_TextureIndex(TextureManager::m_InvalidIndex)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\TitleScene\\TitleBackground.png"), 
		&m_TextureIndex);

	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_Size, m_Texel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_Pos));
}

TitleBackground::~TitleBackground()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void TitleBackground::Control()
{
}

void TitleBackground::Draw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex2D->Draw();
}
