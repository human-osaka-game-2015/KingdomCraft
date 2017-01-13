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
#include "BuildWindow\BuildWindow.h"
#include "PoliticsWindow\PoliticsWindow.h"
#include "SaveWindow\SaveWindow.h"
#include "LoadWindow\LoadWindow.h"
#include "BackToTitleWindow\BackToTitleWindow.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 OperationWindow::m_DefaultPos = D3DXVECTOR2(1015, 650);
const D3DXVECTOR2 OperationWindow::m_DefaultSize = D3DXVECTOR2(500, 140);


OperationWindow::OperationWindow() :
WindowUI(&m_DefaultPos, &m_DefaultSize)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\OperationUI.jpg"),
		&m_TextureIndex);

	m_pButtonUI.push_back(new BuildButtonUI(&m_DefaultPos, m_TextureIndex));
	m_pButtonUI.push_back(new PoliticsButtonUI(&m_DefaultPos, m_TextureIndex));
	m_pButtonUI.push_back(new SaveButtonUI(&m_DefaultPos, m_TextureIndex));
	m_pButtonUI.push_back(new LoadButtonUI(&m_DefaultPos, m_TextureIndex));
	m_pButtonUI.push_back(new BackToTitleButtonUI(&m_DefaultPos, m_TextureIndex));

	m_pWindowUI.push_back(new BuildWindow(&m_DefaultPos));
	m_pWindowUI.push_back(new PoliticsWindow(&m_DefaultPos));
	m_pWindowUI.push_back(new SaveWindow(&m_DefaultPos));
	m_pWindowUI.push_back(new LoadWindow(&m_DefaultPos));
	m_pWindowUI.push_back(new BackToTitleWindow(&m_DefaultPos));
}

OperationWindow::~OperationWindow()
{
	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		delete m_pWindowUI[i];
	}

	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		delete m_pButtonUI[i];
	}

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void OperationWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}

	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Control();
	}

	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		m_pWindowUI[i]->Control();
	}
}

void OperationWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	WindowDraw();

	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		m_pButtonUI[i]->Draw();
	}

	for (unsigned int i = 0; i < m_pWindowUI.size(); i++)
	{
		m_pWindowUI[i]->Draw();
	}
}
