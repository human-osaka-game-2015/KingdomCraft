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

const D3DXVECTOR2 OperationWindow::m_OperationWindowPos = D3DXVECTOR2(1015, 650);
const D3DXVECTOR2 OperationWindow::m_OperationWindowSize = D3DXVECTOR2(500, 140);


OperationWindow::OperationWindow() :
WindowUI(&m_OperationWindowPos, &m_OperationWindowSize)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\OperationUI.png"),
		&m_ButtonTextureIndex);

	m_pButtonUI.push_back(new BuildButtonUI(&m_OperationWindowPos, m_ButtonTextureIndex));
	m_pButtonUI.push_back(new PoliticsButtonUI(&m_OperationWindowPos, m_ButtonTextureIndex));
	m_pButtonUI.push_back(new SaveButtonUI(&m_OperationWindowPos, m_ButtonTextureIndex));
	m_pButtonUI.push_back(new LoadButtonUI(&m_OperationWindowPos, m_ButtonTextureIndex));
	m_pButtonUI.push_back(new BackToTitleButtonUI(&m_OperationWindowPos, m_ButtonTextureIndex));
}

OperationWindow::~OperationWindow()
{
	for (unsigned int i = 0; i < m_pButtonUI.size(); i++)
	{
		delete m_pButtonUI[i];
	}

	TextureManager::GetInstance()->ReleaseTexture(m_ButtonTextureIndex);
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
}
