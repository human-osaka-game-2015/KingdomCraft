/**
 * @file   OperationWindow.cpp
 * @brief  OperationWindowクラスの実装
 * @author morimoto
 */
#include "OperationWindow.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"


const D3DXVECTOR2 OperationWindow::m_OperationUISize = D3DXVECTOR2(64, 64);

const D3DXVECTOR2 OperationWindow::m_OperationUIPos[OPERATION_MAX] =
{
	D3DXVECTOR2(900,  630),	// 建築UI
	D3DXVECTOR2(964,  630),	// 政治UI
	D3DXVECTOR2(1028, 630),	// セーブUI
	D3DXVECTOR2(1092, 630),	// ロードUI
	D3DXVECTOR2(1156, 630)	// タイトルバックUI
};

const D3DXVECTOR2 OperationWindow::m_OperationUITexel[4] =
{
	D3DXVECTOR2(0,     0), 
	D3DXVECTOR2(0.125, 0), 
	D3DXVECTOR2(0,     0.125), 
	D3DXVECTOR2(0.125, 0.125)
};

const D3DXVECTOR2 OperationWindow::m_OperationUITexelOffset[OPERATION_MAX] =
{
	 D3DXVECTOR2(0,     0),	// 建築UI
	 D3DXVECTOR2(0.125, 0),	// 政治UI
	 D3DXVECTOR2(0.25,  0),	// セーブUI
	 D3DXVECTOR2(0.375, 0),	// ロードUI
	 D3DXVECTOR2(0.5,   0)	// タイトルバックUI
};


OperationWindow::OperationWindow() :
UIWindow(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(0, 0))
{
}

OperationWindow::~OperationWindow()
{
}

void OperationWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void OperationWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}
}
