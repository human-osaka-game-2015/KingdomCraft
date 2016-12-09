/**
 * @file   UIWindow.cpp
 * @brief  UIWindowクラスの実装
 * @author morimoto
 */
#include "UIWindow.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 UIWindow::m_WindowPartsTexel[4] =
{
	D3DXVECTOR2(0,			0),
	D3DXVECTOR2(0.1953125,	0),
	D3DXVECTOR2(0,			0.1953125),
	D3DXVECTOR2(0.1953125,	0.1953125)
};

const D3DXVECTOR2 UIWindow::m_WindowPartsTexelOffset[UIWindow::PARTS_MAX] =
{
	D3DXVECTOR2(0,			0),			// ウインドウの左上
	D3DXVECTOR2(0.1953125,	0),			// ウィンドウの中央上	
	D3DXVECTOR2(0.390625,	0),			// ウインドウの右上
	D3DXVECTOR2(0,			0.1953125),	// ウィンドウの左
	D3DXVECTOR2(0.1953125,	0.1953125),	// ウィンドウの中央
	D3DXVECTOR2(0.390625,	0.1953125),	// ウィンドウの右
	D3DXVECTOR2(0,			0.390625),	// ウインドウの左下
	D3DXVECTOR2(0.1953125,	0.390625),	// ウィンドウの中央下
	D3DXVECTOR2(0.390625,	0.390625)	// ウインドウの右下
};


UIWindow::UIWindow(const D3DXVECTOR2* _pWindowPos, const D3DXVECTOR2* _pWindowSize, bool _isVisible) :
m_WindowPos(*_pWindowPos),
m_WindowSize(*_pWindowSize),
m_IsVisible(_isVisible)
{
	m_WindowPartsPosOffset[LEFT_TOP].x = -m_WindowSize.x / 3;
	m_WindowPartsPosOffset[LEFT_TOP].y = -m_WindowSize.y / 3;
	m_WindowPartsPosOffset[CENTER_TOP].x = 0;
	m_WindowPartsPosOffset[CENTER_TOP].y = -m_WindowSize.y / 3;
	m_WindowPartsPosOffset[RIGHT_TOP].x = m_WindowSize.x / 3;
	m_WindowPartsPosOffset[RIGHT_TOP].y = -m_WindowSize.y / 3;

	m_WindowPartsPosOffset[LEFT].x = -m_WindowSize.x / 3;
	m_WindowPartsPosOffset[LEFT].y = 0;
	m_WindowPartsPosOffset[CENTER].x = 0;
	m_WindowPartsPosOffset[CENTER].y = 0;
	m_WindowPartsPosOffset[RIGHT].x = m_WindowSize.x / 3;
	m_WindowPartsPosOffset[RIGHT].y = 0;

	m_WindowPartsPosOffset[LEFT_BOTTOM].x = -m_WindowSize.x / 3;
	m_WindowPartsPosOffset[LEFT_BOTTOM].y = m_WindowSize.y / 3;
	m_WindowPartsPosOffset[CENTER_BOTTOM].x = 0;
	m_WindowPartsPosOffset[CENTER_BOTTOM].y = m_WindowSize.y / 3;
	m_WindowPartsPosOffset[RIGHT_BOTTOM].x = m_WindowSize.x / 3;
	m_WindowPartsPosOffset[RIGHT_BOTTOM].y = m_WindowSize.y / 3;


	m_WindowPartsSize = m_WindowSize;
	m_WindowPartsSize.x /= 3;
	m_WindowPartsSize.y /= 3;

	m_pWindowVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pWindowVertex->Init(&m_WindowPartsSize, m_WindowPartsTexel);


	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\ObjectManager\\UIManager\\UIWindow\\UIWindow.png"),
		&m_TextureIndex);

	m_pWindowVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

UIWindow::~UIWindow()
{
	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);

	m_pWindowVertex->Release();
	delete m_pWindowVertex;
}

void UIWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void UIWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void UIWindow::WindowDraw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		D3DXVECTOR2 DrawPos = m_WindowPos + m_WindowPartsPosOffset[i];
		m_pWindowVertex->Draw(&DrawPos, 1.0f, &D3DXVECTOR3(1.0f, 1.0f, 1.0f), &m_WindowPartsTexelOffset[i]);
	}
}
