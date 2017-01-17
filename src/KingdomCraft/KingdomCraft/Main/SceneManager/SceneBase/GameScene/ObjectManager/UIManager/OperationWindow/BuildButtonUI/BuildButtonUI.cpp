/**
 * @file   BuildButtonUI.cpp
 * @brief  BuildButtonUIクラスの実装
 * @author morimoto
 */
#include "BuildButtonUI.h"
#include "EventManager.h"
#include "Event\OperationWindowEvent\OperationWindowEvent.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 BuildButtonUI::m_DefaultPos = D3DXVECTOR2(-137, -15);
const D3DXVECTOR2 BuildButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 BuildButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0,		0),
	D3DXVECTOR2(0.125,	0),
	D3DXVECTOR2(0,		0.125),
	D3DXVECTOR2(0.125,	0.125)
};

const D3DXVECTOR2 BuildButtonUI::m_MouseOverTexelOffset = D3DXVECTOR2(0.0, 0.125);


BuildButtonUI::BuildButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
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

BuildButtonUI::~BuildButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool BuildButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	bool IsClick = IsClicked();
	if (IsClick == true)
	{
		OperationWindowEvent::GetInstance()->SetEventType(OperationWindowEvent::BUILD_BUTTON_CLICK);
		EventManager::GetInstance()->SendEventMessage(OperationWindowEvent::GetInstance());
	}

	return IsClick;
}

void BuildButtonUI::Draw()
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

void BuildButtonUI::MouseOverButtonDraw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex2D->WriteConstantBuffer(
		&D3DXVECTOR2(m_DefaultPos + m_ParentUIPos),
		&D3DXVECTOR2(1.0f, 1.0f),
		&m_MouseOverTexelOffset);

	m_pVertex2D->Draw();
}

void BuildButtonUI::ButtonDraw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + m_ParentUIPos));
	m_pVertex2D->Draw();
}
