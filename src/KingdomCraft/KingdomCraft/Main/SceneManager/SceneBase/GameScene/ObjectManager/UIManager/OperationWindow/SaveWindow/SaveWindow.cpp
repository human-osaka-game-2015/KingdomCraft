/**
 * @file   SaveWindow.cpp
 * @brief  SaveWindowクラスの実装
 * @author morimoto
 */
#include "SaveWindow.h"

const D3DXVECTOR2 SaveWindow::m_DefaultPos = D3DXVECTOR2(0, 150);
const D3DXVECTOR2 SaveWindow::m_DefaultSize = D3DXVECTOR2(500, 140);


SaveWindow::SaveWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize)
{
}

SaveWindow::~SaveWindow()
{
}

void SaveWindow::Control()
{
}

void SaveWindow::Draw()
{
}

