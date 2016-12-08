/**
 * @file   UIWindow.cpp
 * @brief  UIWindowクラスの実装
 * @author morimoto
 */
#include "UIWindow.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 UIWindow::m_WindowPartsUV[UIWindow::PARTS_MAX][4] =
{
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) },	// ウインドウの左上
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) },	// ウィンドウの中央上	
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) },	// ウインドウの右上
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) },	// ウィンドウの左
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) },	// ウィンドウの中央
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) },	// ウィンドウの右
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) },	// ウインドウの左下
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) },	// ウィンドウの中央下
	{ D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0), D3DXVECTOR2(0, 0) }	// ウインドウの右下
};


UIWindow::UIWindow(const D3DXVECTOR2* _pWindowPos, const D3DXVECTOR2* _pWindowSize, bool _isVisible) :
m_WindowPos(*_pWindowPos),
m_WindowSize(*_pWindowSize),
m_IsVisible(_isVisible)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\ObjectManager\\UIManager\\UIWindow\\UIWindow.png"),
		&m_TextureIndex);
}

UIWindow::~UIWindow()
{
	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void UIWindow::Control()
{
}

void UIWindow::Draw()
{
}

