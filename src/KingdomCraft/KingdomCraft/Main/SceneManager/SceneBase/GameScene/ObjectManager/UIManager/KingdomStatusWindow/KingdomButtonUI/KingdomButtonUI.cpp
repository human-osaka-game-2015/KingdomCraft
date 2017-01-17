/**
 * @file   KingdomButtonUI.cpp
 * @brief  KingdomButtonUIクラスの実装
 * @author morimoto
 */
#include "KingdomButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 KingdomButtonUI::m_DefaultPos = D3DXVECTOR2(195, -20);
const D3DXVECTOR2 KingdomButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 KingdomButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.375, 0.25),
	D3DXVECTOR2(0.5,   0.25),
	D3DXVECTOR2(0.375, 0.375),
	D3DXVECTOR2(0.5,   0.375)
};

const D3DXVECTOR2 KingdomButtonUI::m_MouseOverTexelOffset = D3DXVECTOR2(0.0, 0.125);


KingdomButtonUI::KingdomButtonUI(const D3DXVECTOR2* _pParentUIPos) :
ButtonUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pVertex2D(NULL),
m_TextureIndex(TextureManager::m_InvalidIndex),
m_ParentUIPos(*_pParentUIPos)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\MainUI.png"),
		&m_TextureIndex);

	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
}

KingdomButtonUI::~KingdomButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

bool KingdomButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void KingdomButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	if (m_IsMouseOver == true)
	{
		MouseOverButtonDraw();
	}
	else
	{
		ButtonDraw();
	}
}

void KingdomButtonUI::MouseOverButtonDraw()
{
	m_pVertex2D->WriteConstantBuffer(
		&D3DXVECTOR2(m_DefaultPos + m_ParentUIPos),
		&D3DXVECTOR2(1.0f, 1.0f),
		&m_MouseOverTexelOffset);

	m_pVertex2D->Draw();
}

void KingdomButtonUI::ButtonDraw()
{
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + m_ParentUIPos));
	m_pVertex2D->Draw();
}
