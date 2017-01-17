/**
 * @file   AccelerateOfTimeButtonUI.cpp
 * @brief  AccelerateOfTimeButtonUIクラスの実装
 * @author morimoto
 */
#include "AccelerateOfTimeButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include "EventManager.h"
#include "Event\GameTimeEvent\GameTimeEvent.h"

const D3DXVECTOR2 AccelerateOfTimeButtonUI::m_DefaultPos = D3DXVECTOR2(194, -15);
const D3DXVECTOR2 AccelerateOfTimeButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 AccelerateOfTimeButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.25,  0.25),
	D3DXVECTOR2(0.375, 0.25),
	D3DXVECTOR2(0.25,  0.375),
	D3DXVECTOR2(0.375, 0.375)
};

const D3DXVECTOR2 AccelerateOfTimeButtonUI::m_MouseOverTexelOffset = D3DXVECTOR2(0.0, 0.125);


AccelerateOfTimeButtonUI::AccelerateOfTimeButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
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

AccelerateOfTimeButtonUI::~AccelerateOfTimeButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool AccelerateOfTimeButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	bool IsClick = IsClicked();
	if (IsClick == true)
	{
		GameTimeEvent::GetInstance()->SetEventType(GameTimeEvent::ACCELERATE_TIME);
		EventManager::GetInstance()->SendEventMessage(GameTimeEvent::GetInstance());
	}

	return IsClick;
}

void AccelerateOfTimeButtonUI::Draw()
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

void AccelerateOfTimeButtonUI::MouseOverButtonDraw()
{
	m_pVertex2D->WriteConstantBuffer(
		&D3DXVECTOR2(m_DefaultPos + m_ParentUIPos),
		&D3DXVECTOR2(1.0f, 1.0f),
		&m_MouseOverTexelOffset);

	m_pVertex2D->Draw();
}

void AccelerateOfTimeButtonUI::ButtonDraw()
{
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + m_ParentUIPos));
	m_pVertex2D->Draw();
}
