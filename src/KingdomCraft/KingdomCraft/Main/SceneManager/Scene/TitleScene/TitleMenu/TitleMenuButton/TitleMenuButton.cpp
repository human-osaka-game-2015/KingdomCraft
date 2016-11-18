/**
 * @file TitleButton.cpp
 * @brief TitleButtonクラス実装
 * @author morimoto
 */
#include "TitleMenuButton.h"
#include "DX11Manager\DX11Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "TextureManager\TextureManager.h"


TitleMenuButton::TitleMenuButton(const D3DXVECTOR2* const _pDrawPos, const D3DXVECTOR2* const _pDrawSize, LPCTSTR const _pTextureName) :
m_DrawPos(*_pDrawPos),
m_DrawSize(*_pDrawSize),
m_IsMouseOver(false),
m_IsVisible(false),
m_TextureIndex(-1)	/// @todo TextureManagerクラスの定数を作るまで-1は仮置きしとく
{
	RECT VertexRect;
	VertexRect.left = 0;
	VertexRect.right = m_DrawSize.x;
	VertexRect.top = 0;
	VertexRect.bottom = m_DrawSize.y;

	D3DXVECTOR2 UV[4];
	UV[0] = D3DXVECTOR2(0, 0);
	UV[1] = D3DXVECTOR2(1, 0);
	UV[2] = D3DXVECTOR2(0, 1);
	UV[3] = D3DXVECTOR2(1, 1);


	m_pVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init(&VertexRect, UV);


	TextureManager::GetInstance()->LoadTexture(_pTextureName, &m_TextureIndex);
	m_pVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

TitleMenuButton::~TitleMenuButton()
{
	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
	m_pVertex->Release();
	delete m_pVertex;
}

bool TitleMenuButton::Control()
{
	if (!m_IsVisible)
	{
		return false;
	}

	return OnClick();
}

void TitleMenuButton::Draw()
{
	if (!m_IsVisible)
	{
		return;
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(false);

	if (m_IsMouseOver)
	{
		m_pVertex->Draw(&m_DrawPos, 1.0f, &D3DXVECTOR3(1.1, 1.1, 1));
	}
	else
	{
		m_pVertex->Draw(&m_DrawPos, 1.0f, &D3DXVECTOR3(1, 1, 1));
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}

bool TitleMenuButton::OnClick()
{
	bool isClick = false;
	MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	// マウス座標が矩形内にあるか判定
	if (MouseState.CursorPos.x > (m_DrawPos.x - m_DrawSize.x / 2) &&
		MouseState.CursorPos.x < (m_DrawPos.x + m_DrawSize.x / 2) &&
		MouseState.CursorPos.y > (m_DrawPos.y - m_DrawSize.y / 2) &&
		MouseState.CursorPos.y < (m_DrawPos.y + m_DrawSize.y / 2))
	{
		m_IsMouseOver = true;

		if (MouseState.rgbButtons[0] == MOUSEBUTTON_PUSH)
		{
			isClick = true;
		}
	}
	else
	{
		m_IsMouseOver = false;
	}

	return isClick;
}
