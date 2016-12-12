/**
 * @file   OperationWindow.cpp
 * @brief  OperationWindowクラスの実装
 * @author morimoto
 */
#include "OperationWindow.h"
#include "BuildButtonUI\BuildButtonUI.h"
#include "PoliticsButtonUI\PoliticsButtonUI.h"
#include "SaveButtonUI\SaveButtonUI.h"
#include "LoadButtonUI\LoadButtonUI.h"
#include "BackToTitleButtonUI\BackToTitleButtonUI.h"
#include "TextureManager\TextureManager.h"


OperationWindow::OperationWindow() :
UIWindow(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(0, 0))
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\ObjectManager\\UIManager\\OperationWindow\\OperationUI.png"),
		&m_TextureIndex);

	m_pUIButton.push_back(new BuildButtonUI(m_TextureIndex));
	m_pUIButton.push_back(new PoliticsButtonUI(m_TextureIndex));
	m_pUIButton.push_back(new SaveButtonUI(m_TextureIndex));
	m_pUIButton.push_back(new LoadButtonUI(m_TextureIndex));
	m_pUIButton.push_back(new BackToTitleButtonUI(m_TextureIndex));
}

OperationWindow::~OperationWindow()
{
	for (unsigned int i = 0; i < m_pUIButton.size(); i++)
	{
		delete m_pUIButton[i];
	}

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void OperationWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}

	for (unsigned int i = 0; i < m_pUIButton.size(); i++)
	{
		m_pUIButton[i]->Control();
	}
}

void OperationWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	for (unsigned int i = 0; i < m_pUIButton.size(); i++)
	{
		m_pUIButton[i]->Draw();
	}
}
