/**
 * @file   DecelerateOfTimeButtonUI.cpp
 * @brief  DecelerateOfTimeButtonUIクラスの実装
 * @author morimoto
 */
#include "DecelerateOfTimeButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include "EventManager.h"
#include "Event\GameTimeEvent\GameTimeEvent.h"

const D3DXVECTOR2 DecelerateOfTimeButtonUI::m_DefaultPos = D3DXVECTOR2(66, -15);
const D3DXVECTOR2 DecelerateOfTimeButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 DecelerateOfTimeButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0,     0.25),
	D3DXVECTOR2(0.125, 0.25),
	D3DXVECTOR2(0,     0.375),
	D3DXVECTOR2(0.125, 0.375)
};

const D3DXVECTOR2 DecelerateOfTimeButtonUI::m_MouseOverTexelOffset = D3DXVECTOR2(0.0, 0.125);


DecelerateOfTimeButtonUI::DecelerateOfTimeButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
ButtonUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pVertex2D(NULL),
m_TextureIndex(_textureIndex),
m_ParentUIPos(*_pParentUIPos)
{
	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
}

DecelerateOfTimeButtonUI::~DecelerateOfTimeButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool DecelerateOfTimeButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	bool IsClick = IsClicked();
	if (IsClick == true)
	{
		GameTimeEvent::GetInstance()->SetEventType(GameTimeEvent::DECELERATE_TIME);
		EventManager::GetInstance()->SendEventMessage(GameTimeEvent::GetInstance());
	}

	return IsClick;
}

void DecelerateOfTimeButtonUI::Draw()
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

void DecelerateOfTimeButtonUI::MouseOverButtonDraw()
{
	m_pVertex2D->WriteConstantBuffer(
		&D3DXVECTOR2(m_DefaultPos + m_ParentUIPos),
		&D3DXVECTOR2(1.0f, 1.0f),
		&m_MouseOverTexelOffset);

	m_pVertex2D->Draw();
}

void DecelerateOfTimeButtonUI::ButtonDraw()
{
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + m_ParentUIPos));
	m_pVertex2D->Draw();
}

