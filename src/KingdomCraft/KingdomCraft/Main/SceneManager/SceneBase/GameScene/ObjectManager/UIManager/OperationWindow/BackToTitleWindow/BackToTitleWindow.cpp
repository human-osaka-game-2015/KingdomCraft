/**
 * @file   BackToTitleWindow.cpp
 * @brief  BackToTitleWindowクラスの実装
 * @author morimoto
 */
#include "BackToTitleWindow.h"

const D3DXVECTOR2 BackToTitleWindow::m_DefaultPos = D3DXVECTOR2(0, 150);
const D3DXVECTOR2 BackToTitleWindow::m_DefaultSize = D3DXVECTOR2(500, 140);


BackToTitleWindow::BackToTitleWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize)
{
}

BackToTitleWindow::~BackToTitleWindow()
{
}

void BackToTitleWindow::Control()
{
}

void BackToTitleWindow::Draw()
{
}
