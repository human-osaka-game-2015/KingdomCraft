/**
 * @file   GameTimeOperationUI.cpp
 * @brief  GameTimeOperationUIクラスの実装
 * @author morimoto
 */
#include "GameTimeOperationUI.h"
#include "TextureManager\TextureManager.h"
#include "DecelerateOfTimeButtonUI\DecelerateOfTimeButtonUI.h"
#include "AccelerateOfTimeButtonUI\AccelerateOfTimeButtonUI.h"
#include "NormalTimeButtonUI\NormalTimeButtonUI.h"
#include "GameTimeSpeedUI\GameTimeSpeedUI.h"


GameTimeOperationUI::GameTimeOperationUI(const D3DXVECTOR2* _pParentUIPos) :
m_ParentUIPos(*_pParentUIPos),
m_TextureIndex(TextureManager::m_InvalidIndex)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\MainUI.png"),
		&m_TextureIndex);

	m_pDecelerateButton = new DecelerateOfTimeButtonUI(_pParentUIPos, m_TextureIndex);
	m_pAccelerateButton = new AccelerateOfTimeButtonUI(_pParentUIPos, m_TextureIndex);
	m_pNormalButton = new NormalTimeButtonUI(_pParentUIPos, m_TextureIndex);
	m_pGameTimeSpeed = new GameTimeSpeedUI(_pParentUIPos);
}

GameTimeOperationUI::~GameTimeOperationUI()
{
	delete m_pGameTimeSpeed;
	delete m_pNormalButton;
	delete m_pAccelerateButton;
	delete m_pDecelerateButton;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void GameTimeOperationUI::Control()
{
	m_pDecelerateButton->Control();
	m_pAccelerateButton->Control();
	m_pNormalButton->Control();
	m_pGameTimeSpeed->Control();
}

void GameTimeOperationUI::Draw()
{
	m_pDecelerateButton->Draw();
	m_pAccelerateButton->Draw();
	m_pNormalButton->Draw();
	m_pGameTimeSpeed->Draw();
}
