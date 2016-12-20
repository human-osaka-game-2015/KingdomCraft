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
m_pButtonVertex(NULL),
m_IsMouseOver(false),
m_IsVisible(false),
m_ButtonTextureIndex(TextureManager::m_InvalidIndex)
{
	TextureManager::GetInstance()->LoadTexture(_pTextureName, &m_ButtonTextureIndex);

	m_pButtonVertex = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pButtonVertex->Init(&m_ButtonSize, m_ButtonTexel);
	m_pButtonVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_ButtonTextureIndex));
	m_pButtonVertex->WriteConstantBuffer(&m_ButtonPos);
}

TitleMenuButton::~TitleMenuButton()
{
	m_pButtonVertex->Release();
	delete m_pButtonVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_ButtonTextureIndex);
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
		m_pButtonVertex->WriteConstantBuffer(&m_ButtonPos, &D3DXVECTOR2(1.1f, 1.1f));
		m_pButtonVertex->Draw();
	}
	else
	{
		m_pButtonVertex->WriteConstantBuffer(&m_ButtonPos, &D3DXVECTOR2(1.0f, 1.0f));
		m_pButtonVertex->Draw();
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(true);
}

bool TitleMenuButton::IsClicked()
{
	bool IsClick = false;
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
			IsClick = true;
		}
	}
	else
	{
		m_IsMouseOver = false;
	}

	return IsClick;
}
