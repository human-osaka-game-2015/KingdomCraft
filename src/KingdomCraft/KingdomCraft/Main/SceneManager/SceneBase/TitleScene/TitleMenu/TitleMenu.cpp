/**
 * @file TitleMenu.cpp
 * @brief TitleMenuクラス実装
 * @author morimoto
 */
#include "TitleMenu.h"
#include "TitleStartButton\TitleStartButton.h"
#include "TitleContinueButton\TitleContinueButton.h"
#include "TitleSaveDataMenu\TitleSaveDataMenu.h"
#include "TextureManager\TextureManager.h"

D3DXVECTOR2	TitleMenu::m_StartButtonPos = D3DXVECTOR2(640, 430);
D3DXVECTOR2	TitleMenu::m_StartButtonSize = D3DXVECTOR2(330, 70);
D3DXVECTOR2	TitleMenu::m_ContinueButtonPos = D3DXVECTOR2(640, 510);
D3DXVECTOR2	TitleMenu::m_ContinueButtonSize = D3DXVECTOR2(330, 70);


TitleMenu::TitleMenu()
{
	TextureManager::GetInstance()->LoadTexture(TEXT("Resource\\Texture\\TitleScene\\TitleMenu.png"), &m_TextureIndex);

	m_pStartButton = new TitleStartButton(&m_StartButtonPos, &m_StartButtonSize, m_TextureIndex);
	m_pContinueButton = new TitleContinueButton(&m_ContinueButtonPos, &m_ContinueButtonSize, m_TextureIndex);
	m_pTitleSaveDataMenu = new TitleSaveDataMenu();

	m_pStartButton->SetVisible(true);
	m_pContinueButton->SetVisible(true);
	m_pTitleSaveDataMenu->SetVisible(false);
}

TitleMenu::~TitleMenu()
{
	delete m_pTitleSaveDataMenu;
	delete m_pContinueButton;
	delete m_pStartButton;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
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
