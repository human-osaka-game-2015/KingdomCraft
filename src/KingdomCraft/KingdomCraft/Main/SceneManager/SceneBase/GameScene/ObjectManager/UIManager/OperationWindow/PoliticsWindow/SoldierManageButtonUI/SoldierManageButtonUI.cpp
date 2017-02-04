/**
 * @file   SoldierManageButtonUI.cpp
 * @brief  SoldierManageButtonUIクラスの実装
 * @author morimoto
 */
#include "SoldierManageButtonUI.h"
#include "EventManager.h"
#include "Event\PoliticsWindowEvent\PoliticsWindowEvent.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SoldierManageButtonUI::m_DefaultPos = D3DXVECTOR2(-170, -170);
const D3DXVECTOR2 SoldierManageButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 SoldierManageButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.0f,	0.0f),
	D3DXVECTOR2(1.0f,	0.0f),
	D3DXVECTOR2(0.0f,   1.0f),
	D3DXVECTOR2(1.0f,	1.0f)
};

SoldierManageButtonUI::SoldierManageButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
ButtonUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pParentUIPos(_pParentUIPos),
m_TextureIndex(_textureIndex)
{
	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
}

SoldierManageButtonUI::~SoldierManageButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool SoldierManageButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	m_ButtonPos = *m_pParentUIPos + m_DefaultPos;	// 判定用のボタン座標を更新
	bool IsClick = IsClicked();
	if (IsClick == true)
	{
		PoliticsWindowEvent::GetInstance()->SetEventType(PoliticsWindowEvent::SOLDIER_MANAGE_BUTTON_CLICK);
		EventManager::GetInstance()->SendEventMessage(PoliticsWindowEvent::GetInstance());
	}

	return IsClick;
}

void SoldierManageButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *m_pParentUIPos));
	m_pVertex2D->Draw();
}

