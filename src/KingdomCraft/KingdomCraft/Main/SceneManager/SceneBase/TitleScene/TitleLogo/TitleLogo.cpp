/**
 * @file TitleLogo.cpp
 * @brief TitleLogoクラス実装
 * @author morimoto
 */
#include "TitleLogo.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include "Vertex2D\Vertex2D.h"

const D3DXVECTOR2 TitleLogo::m_Pos = D3DXVECTOR2(640, 100);
const D3DXVECTOR2 TitleLogo::m_Size = D3DXVECTOR2(630, 100);
const D3DXVECTOR2 TitleLogo::m_Texel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


TitleLogo::TitleLogo() :
m_pVertex2D(NULL),
m_TextureIndex(TextureManager::m_InvalidIndex)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\TitleScene\\TitleLogo.jpg"), 
		&m_TextureIndex);

	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_Size, m_Texel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_Pos));
}

TitleLogo::~TitleLogo()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void TitleLogo::Control()
{
}

void TitleLogo::Draw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex2D->Draw();
}
