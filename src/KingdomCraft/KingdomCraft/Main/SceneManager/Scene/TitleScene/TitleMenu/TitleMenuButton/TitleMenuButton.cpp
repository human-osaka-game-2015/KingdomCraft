/**
 * @file TitleButton.cpp
 * @brief TitleButtonクラス実装
 * @author morimoto
 */
#include "TitleMenuButton.h"
#include "DX11Manager\DX11Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "TextureManager\TextureManager.h"


TitleMenuButton::TitleMenuButton(const D3DXVECTOR2* const _pButtonPos, const D3DXVECTOR2* const _pButtonVertex, LPCTSTR const _pTextureName) :
m_ButtonPos(*_pButtonPos),
m_ButtonVertex(*_pButtonVertex),
m_IsMouseOver(false),
m_IsVisible(false),
m_TextureIndex(TextureManager::m_InvalidIndex)
{
	D3DXVECTOR2 UV[4];
	UV[0] = D3DXVECTOR2(0, 0);
	UV[1] = D3DXVECTOR2(1, 0);
	UV[2] = D3DXVECTOR2(0, 1);
	UV[3] = D3DXVECTOR2(1, 1);


	m_pVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init(&m_ButtonVertex, UV);


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

	return IsClicked();
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
	if (MouseState.CursorPos.x > (m_ButtonPos.x - m_ButtonVertex.x / 2) &&
		MouseState.CursorPos.x < (m_ButtonPos.x + m_ButtonVertex.x / 2) &&
		MouseState.CursorPos.y > (m_ButtonPos.y - m_ButtonVertex.y / 2) &&
		MouseState.CursorPos.y < (m_ButtonPos.y + m_ButtonVertex.y / 2))
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
