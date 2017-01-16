/**
 * @file   ButtonUI.cpp
 * @brief  ButtonUIクラスの実装
 * @author morimoto
 */
#include "ButtonUI.h"
#include "InputDeviceManager\InputDeviceManager.h"


ButtonUI::ButtonUI(const D3DXVECTOR2* _pButtonPos, const D3DXVECTOR2* _pButtonSize, bool _isVisible) :
m_ButtonPos(*_pButtonPos),
m_ButtonSize(*_pButtonSize),
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
	if (MouseState.CursorPos.x > (m_ButtonPos.x - m_ButtonSize.x / 2) &&
		MouseState.CursorPos.x < (m_ButtonPos.x + m_ButtonSize.x / 2) &&
		MouseState.CursorPos.y > (m_ButtonPos.y - m_ButtonSize.y / 2) &&
		MouseState.CursorPos.y < (m_ButtonPos.y + m_ButtonSize.y / 2))
	{
		m_IsMouseOver = true;

		if (MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_RELEASE)
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
