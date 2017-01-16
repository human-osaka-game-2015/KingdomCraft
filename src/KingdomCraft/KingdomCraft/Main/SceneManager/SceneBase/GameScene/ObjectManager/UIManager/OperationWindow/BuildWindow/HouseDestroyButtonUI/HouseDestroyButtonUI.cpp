/**
 * @file   HouseDestroyButtonUI.cpp
 * @brief  HouseDestroyButtonUIクラスの実装
 * @author morimoto
 */
#include "HouseDestroyButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include "EventManager.h"
#include "Event\BuildWindowEvent\BuildWindowEvent.h"

const D3DXVECTOR2 HouseDestroyButtonUI::m_DefaultPos = D3DXVECTOR2(-106, -170);
const D3DXVECTOR2 HouseDestroyButtonUI::m_DefaultSize = D3DXVECTOR2(64, 64);
const D3DXVECTOR2 HouseDestroyButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.125, 0),
	D3DXVECTOR2(0.25,  0),
	D3DXVECTOR2(0.125, 1),
	D3DXVECTOR2(0.25,  1) 
};


HouseDestroyButtonUI::HouseDestroyButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
ButtonUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pVertex2D(NULL),
m_TextureIndex(_textureIndex),
m_pParentUIPos(_pParentUIPos)
{
	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
}

HouseDestroyButtonUI::~HouseDestroyButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;
}

bool HouseDestroyButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	m_ButtonPos = *m_pParentUIPos + m_DefaultPos;	// 判定用のボタン座標を更新
	bool IsClick = IsClicked();
	if (IsClick == true)
	{
		BuildWindowEvent::GetInstance()->SetEventType(BuildWindowEvent::HOUSE_DESTROY_BUTTON_CLICK);
		EventManager::GetInstance()->SendEventMessage(BuildWindowEvent::GetInstance());
	}

	return IsClick;
}

void HouseDestroyButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(*m_pParentUIPos + m_DefaultPos));
	m_pVertex2D->Draw();
}
