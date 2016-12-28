/**
 * @file   ButtonUI.cpp
 * @brief  ButtonUIクラスの実装
 * @author morimoto
 */
#include "ButtonUI.h"
#include "InputDeviceManager\InputDeviceManager.h"


ButtonUI::ButtonUI(const D3DXVECTOR2* _pButtonPos, const D3DXVECTOR2* _pButtonSize, bool _isVisible) :
m_Pos(*_pButtonPos),
m_Size(*_pButtonSize),
m_IsVisible(_isVisible)
{
}

ButtonUI::~ButtonUI()
{
}

bool ButtonUI::Control()
{
	return IsClicked();
}

void ButtonUI::Draw()
{
}

bool ButtonUI::IsClicked()
{
	bool IsClick = false;
	MouseDevice::MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	// マウス座標が矩形内にあるか判定
	if (MouseState.CursorPos.x > (m_Pos.x - m_Size.x / 2) &&
		MouseState.CursorPos.x < (m_Pos.x + m_Size.x / 2) &&
		MouseState.CursorPos.y > (m_Pos.y - m_Size.y / 2) &&
		MouseState.CursorPos.y < (m_Pos.y + m_Size.y / 2))
	{
		m_IsMouseOver = true;

		if (MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_PUSH)
		{
			IsClick = true;
		}
	}
	else
	{
		m_IsMouseOver = false;
	}

	return IsClick;
}
