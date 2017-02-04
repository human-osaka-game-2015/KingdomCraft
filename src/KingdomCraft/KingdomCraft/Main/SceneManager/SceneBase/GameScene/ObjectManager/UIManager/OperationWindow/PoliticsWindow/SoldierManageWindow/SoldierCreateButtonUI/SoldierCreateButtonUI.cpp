/**
 * @file   SoldierCreateButtonUI.cpp
 * @brief  SoldierCreateButtonUIクラスの実装
 * @author morimoto
 */
#include "SoldierCreateButtonUI.h"
#include "EventManager.h"
#include "Event\SoldierManageWindowEvent\SoldierManageWindowEvent.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SoldierCreateButtonUI::m_DefaultPos = D3DXVECTOR2(-20, -170);
const D3DXVECTOR2 SoldierCreateButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 SoldierCreateButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.0f, 0.0f),
	D3DXVECTOR2(1.0f, 0.0f),
	D3DXVECTOR2(0.0f, 1.0f),
	D3DXVECTOR2(1.0f, 1.0f)
};


SoldierCreateButtonUI::SoldierCreateButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
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

SoldierCreateButtonUI::~SoldierCreateButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool SoldierCreateButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	m_ButtonPos = *m_pParentUIPos + m_DefaultPos;
	bool IsClick = IsClicked();
	if (IsClick == true)
	{
		SoldierManageWindowEvent::GetInstance()->SetEventType(SoldierManageWindowEvent::SOLDIER_CREATE_BUTTON_CLICK);
		EventManager::GetInstance()->SendEventMessage(SoldierManageWindowEvent::GetInstance());
	}

	return IsClick;
}

void SoldierCreateButtonUI::Draw()
{
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *m_pParentUIPos));
	m_pVertex2D->Draw();
}
