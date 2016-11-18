/**
 * @file TitleSaveDataMenu.cpp
 * @brief TitleSaveDataMenuクラス実装
 * @author morimoto
 */
#include "TitleSaveDataMenu.h"
#include "TitleSaveDataButton\TitleSaveDataButton.h"
#include "InputDeviceManager\InputDeviceManager.h"

const int TitleSaveDataMenu::m_SaveDataMenuButtonNum = 5;


TitleSaveDataMenu::TitleSaveDataMenu() :
m_IsVisible(false)
{
	for (int i = 0; i < m_SaveDataMenuButtonNum; i++)
	{
		/// @todo テクスチャがないので適当な文字列を渡している
		m_pSaveDataButton.push_back(new TitleSaveDataButton(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(0, 0), TEXT("file")));
	}
}

TitleSaveDataMenu::~TitleSaveDataMenu()
{
	for (int i = 0; i < m_SaveDataMenuButtonNum; i++)
	{
		delete m_pSaveDataButton[i];
	}
}

TitleSaveDataMenu::MENU_ID TitleSaveDataMenu::Control()
{
	if (!m_IsVisible)
	{
		return NONE_ID;
	}


	MENU_ID MenuID = NONE_ID;
	MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	if (MouseState.rgbButtons[1] == MOUSEBUTTON_PUSH)
	{
		MenuID = CANCEL_ID;
	}

	for (int i = 0; i < m_SaveDataMenuButtonNum; i++)
	{
		if (m_pSaveDataButton[i]->Control())
		{
			MenuID = STARTGAME_ID;
		}
	}

	return MenuID;
}

void TitleSaveDataMenu::Draw()
{
	if (!m_IsVisible)
	{
		return;
	}

	for (int i = 0; i < m_SaveDataMenuButtonNum; i++)
	{
		m_pSaveDataButton[i]->Draw();
	}
}

