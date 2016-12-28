/**
 * @file   WindowUI.cpp
 * @brief  WindowUIクラスの実装
 * @author morimoto
 */
#include "WindowUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 WindowUI::m_WindowPartsTexel[4] =
{
	D3DXVECTOR2(0,			0),
	D3DXVECTOR2(0.1953125,	0),
	D3DXVECTOR2(0,			0.1953125),
	D3DXVECTOR2(0.1953125,	0.1953125)
};

const D3DXVECTOR2 WindowUI::m_WindowPartsTexelOffset[WindowUI::PARTS_MAX] =
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


WindowUI::WindowUI(const D3DXVECTOR2* _pWindowPos, const D3DXVECTOR2* _pWindowSize, bool _isVisible) :
m_WindowPos(*_pWindowPos),
m_WindowSize(*_pWindowSize),
m_IsVisible(_isVisible),
m_pWindowVertex(NULL),
m_WindowTextureIndex(TextureManager::m_InvalidIndex)
{
	float WindowPartsTop    = -m_WindowSize.y / 3;
	float WindowPartsBottom = m_WindowSize.y / 3;
	float WindowPartsLeft   = -m_WindowSize.x / 3;
	float WindowPartsRight  = m_WindowSize.x / 3;

	m_WindowPartsPosOffset[LEFT_TOP].x = WindowPartsLeft;
	m_WindowPartsPosOffset[LEFT_TOP].y = WindowPartsTop;
	m_WindowPartsPosOffset[CENTER_TOP].x = 0;
	m_WindowPartsPosOffset[CENTER_TOP].y = WindowPartsTop;
	m_WindowPartsPosOffset[RIGHT_TOP].x = WindowPartsRight;
	m_WindowPartsPosOffset[RIGHT_TOP].y = WindowPartsTop;

	m_WindowPartsPosOffset[LEFT].x = WindowPartsLeft;
	m_WindowPartsPosOffset[LEFT].y = 0;
	m_WindowPartsPosOffset[CENTER].x = 0;
	m_WindowPartsPosOffset[CENTER].y = 0;
	m_WindowPartsPosOffset[RIGHT].x = WindowPartsRight;
	m_WindowPartsPosOffset[RIGHT].y = 0;

	m_WindowPartsPosOffset[LEFT_BOTTOM].x = WindowPartsLeft;
	m_WindowPartsPosOffset[LEFT_BOTTOM].y = WindowPartsBottom;
	m_WindowPartsPosOffset[CENTER_BOTTOM].x = 0;
	m_WindowPartsPosOffset[CENTER_BOTTOM].y = WindowPartsBottom;
	m_WindowPartsPosOffset[RIGHT_BOTTOM].x = WindowPartsRight;
	m_WindowPartsPosOffset[RIGHT_BOTTOM].y = WindowPartsBottom;

	m_WindowPartsSize.x = m_WindowSize.x / 3;
	m_WindowPartsSize.y = m_WindowSize.y / 3;


	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\WindowUI.png"),
		&m_WindowTextureIndex);

	m_pWindowVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pWindowVertex->Init(&m_WindowPartsSize, m_WindowPartsTexel);
	m_pWindowVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_WindowTextureIndex));
	m_pWindowVertex->WriteConstantBuffer(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(1.0f, 1.0f));
}

WindowUI::~WindowUI()
{
	m_pWindowVertex->Release();
	delete m_pWindowVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_WindowTextureIndex);
}

void WindowUI::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void WindowUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void WindowUI::WindowDraw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	for (int i = 0; i < PARTS_MAX; i++)
	{
		D3DXVECTOR2 DrawPos = m_WindowPos + m_WindowPartsPosOffset[i];
		m_pWindowVertex->WriteConstantBuffer(&DrawPos, &D3DXVECTOR2(1.0f, 1.0f), &m_WindowPartsTexelOffset[i]);
		m_pWindowVertex->Draw();
	}
}
