/**
 * @file TitleStartButton.cpp
 * @brief TitleStartButtonクラス実装
 * @author morimoto
 */
#include "TitleStartButton.h"
#include "DX11Manager\DX11Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 TitleStartButton::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0,			0),
	D3DXVECTOR2(0.83984375, 0),
	D3DXVECTOR2(0,			0.15625),
	D3DXVECTOR2(0.83984375, 0.15625)
};

//430
//80

TitleStartButton::TitleStartButton(const D3DXVECTOR2* _pButtonPos, const D3DXVECTOR2* _pButtonSize, int _textureIndex) :
m_Pos(*_pButtonPos),
m_Size(*_pButtonSize),
m_pVertex2D(NULL),
m_IsMouseOver(false),
m_IsVisible(false),
m_TextureIndex(_textureIndex)
{
	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_Size, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&m_Pos);
}

TitleStartButton::~TitleStartButton()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

bool TitleStartButton::Control()
{
	if (!m_IsVisible)
	{
		return false;
	}

	return IsClicked();
}

void TitleStartButton::Draw()
{
	if (!m_IsVisible)
	{
		return;
	}

	ButtonDraw();
}

void TitleStartButton::ButtonDraw()
{
	D3DXVECTOR2 ButtonScale(1.0f, 1.0f);

	if (m_IsMouseOver)
	{
		ButtonScale = D3DXVECTOR2(1.1f, 1.1f);
	}

	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex2D->WriteConstantBuffer(&m_Pos, &ButtonScale);
	m_pVertex2D->Draw();
}

bool TitleStartButton::IsClicked()
{
	bool IsClick = false;
	MouseDevice::MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	// マウス座標が矩形内にあるか判定
	if (MouseState.CursorPos.x > (m_Pos.x - m_Size.x / 2) &&
		MouseState.CursorPos.x < (m_Pos.x + m_Size.x / 2) &&
		MouseState.CursorPos.y >(m_Pos.y - m_Size.y / 2) &&
		MouseState.CursorPos.y < (m_Pos.y + m_Size.y / 2))
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

