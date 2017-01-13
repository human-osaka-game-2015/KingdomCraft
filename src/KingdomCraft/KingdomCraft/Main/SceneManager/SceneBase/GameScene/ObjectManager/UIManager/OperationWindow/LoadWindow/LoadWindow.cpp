/**
 * @file   LoadWindow.cpp
 * @brief  LoadWindowクラスの実装
 * @author morimoto
 */
#include "LoadWindow.h"

const D3DXVECTOR2 LoadWindow::m_DefaultPos = D3DXVECTOR2(0, 150);
const D3DXVECTOR2 LoadWindow::m_DefaultSize = D3DXVECTOR2(500, 140);


LoadWindow::LoadWindow(const D3DXVECTOR2* _pParentUIPos) :
WindowUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize)
{
}

LoadWindow::~LoadWindow()
{
}

void LoadWindow::Control()
{
}

void LoadWindow::Draw()
{
}

