/**
 * @file   UIButton.cpp
 * @brief  UIButtonクラスの実装
 * @author morimoto
 */
#include "UIButton.h"
#include "InputDeviceManager\InputDeviceManager.h"


UIButton::UIButton(const D3DXVECTOR2* _pButtonPos, const D3DXVECTOR2* _pButtonSize, bool _isVisible) :
m_ButtonPos(*_pButtonPos),
m_ButtonSize(*_pButtonSize),
m_IsVisible(_isVisible)
{
}

UIButton::~UIButton()
{
}

bool UIButton::Control()
{
	return IsClicked();
}

void UIButton::Draw()
{
}

bool UIButton::IsClicked()
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
