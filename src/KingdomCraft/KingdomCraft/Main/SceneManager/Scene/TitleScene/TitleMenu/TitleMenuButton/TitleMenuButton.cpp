/**
 * @file TitleButton.cpp
 * @brief TitleButtonクラス実装
 * @author morimoto
 */
#include "TitleMenuButton.h"
#include "DX11Manager\DX11Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 TitleMenuButton::m_ButtonTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


TitleMenuButton::TitleMenuButton(const D3DXVECTOR2* _pButtonPos, const D3DXVECTOR2* _pButtonSize, LPCTSTR _pTextureName) :
m_ButtonPos(*_pButtonPos),
m_ButtonSize(*_pButtonSize),
m_IsMouseOver(false),
m_IsVisible(false),
m_TextureIndex(TextureManager::m_InvalidIndex)
{
	TextureManager::GetInstance()->LoadTexture(_pTextureName, &m_TextureIndex);

	m_pVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init(&m_ButtonSize, m_ButtonTexel);
	m_pVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
}

TitleMenuButton::~TitleMenuButton()
{
	m_pVertex->Release();
	delete m_pVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

bool TitleMenuButton::Control()
{
	if (!m_IsVisible)
	{
		return false;
	}

	return IsClicked();
}

void TitleMenuButton::Draw()
{
	if (!m_IsVisible)
	{
		return;
	}

	ButtonDraw();
}

void TitleMenuButton::ButtonDraw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);

	if (m_IsMouseOver)
	{
		m_pVertex->Draw(&m_ButtonPos, 1.0f, &D3DXVECTOR3(1.1f, 1.1f, 1.f));
	}
	else
	{
		m_pVertex->Draw(&m_ButtonPos, 1.0f, &D3DXVECTOR3(1.f, 1.f, 1.f));
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}

bool TitleMenuButton::IsClicked()
{
	bool isClick = false;
	MouseDevice::MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	// マウス座標が矩形内にあるか判定
	if (MouseState.CursorPos.x > (m_ButtonPos.x - m_ButtonSize.x / 2) &&
		MouseState.CursorPos.x < (m_ButtonPos.x + m_ButtonSize.x / 2) &&
		MouseState.CursorPos.y > (m_ButtonPos.y - m_ButtonSize.y / 2) &&
		MouseState.CursorPos.y < (m_ButtonPos.y + m_ButtonSize.y / 2))
	{
		m_IsMouseOver = true;

		if (MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_PUSH)
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
