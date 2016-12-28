/**
 * @file TitleMenu.cpp
 * @brief TitleMenuクラス実装
 * @author morimoto
 */
#include "TitleMenu.h"
#include "TitleMenuButton\TitleMenuButton.h"
#include "TitleSaveDataMenu\TitleSaveDataMenu.h"

D3DXVECTOR2	TitleMenu::m_StartButtonPos = D3DXVECTOR2(640, 500);
D3DXVECTOR2	TitleMenu::m_StartButtonSize = D3DXVECTOR2(300, 70);
D3DXVECTOR2	TitleMenu::m_ContinueButtonPos = D3DXVECTOR2(640, 600);
D3DXVECTOR2	TitleMenu::m_ContinueButtonSize = D3DXVECTOR2(300, 70);


TitleMenu::TitleMenu() :
m_pStartButton(new TitleMenuButton(&m_StartButtonPos, &m_StartButtonSize, TEXT("Resource\\Texture\\TitleScene\\TitleStart.png"))),
m_pContinueButton(new TitleMenuButton(&m_ContinueButtonPos, &m_ContinueButtonSize, TEXT("Resource\\Texture\\TitleScene\\TitleContinue.png"))),
m_pTitleSaveDataMenu(new TitleSaveDataMenu())
{
	m_pTitleSaveDataMenu->SetVisible(false);
	m_pStartButton->SetVisible(true);
	m_pContinueButton->SetVisible(true);
}

TitleMenu::~TitleMenu()
{
	delete m_pContinueButton;
	delete m_pStartButton;
	delete m_pTitleSaveDataMenu;
}

TitleMenu::MENU_ID TitleMenu::Control()
{
	TitleMenu::MENU_ID MenuID = NONE_ID;


	bool IsStartButtonClick = m_pStartButton->Control();
	bool IsContinueButtonClick = m_pContinueButton->Control();
	TitleSaveDataMenu::MENU_ID SaveDataMenuID = m_pTitleSaveDataMenu->Control();


	
	if (IsStartButtonClick == true)
	{
		MenuID = START_ID;
	}
	else if (IsContinueButtonClick == true)
	{
		m_pTitleSaveDataMenu->SetVisible(true);
		m_pStartButton->SetVisible(false);
		m_pContinueButton->SetVisible(false);
	}

	switch (SaveDataMenuID)
	{
	case TitleSaveDataMenu::NONE_ID:

		break;
	case TitleSaveDataMenu::STARTGAME_ID:
		MenuID = CONTINUE_ID;

		break;
	case TitleSaveDataMenu::CANCEL_ID:
		m_pTitleSaveDataMenu->SetVisible(false);
		m_pStartButton->SetVisible(true);
		m_pContinueButton->SetVisible(true);

		break;
	}

	return MenuID;
}

void TitleMenu::Draw()
{
	m_pTitleSaveDataMenu->Draw();
	m_pStartButton->Draw();
	m_pContinueButton->Draw();
}
