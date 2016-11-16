/**
 * @file   MouseDevice.cpp
 * @brief  MouseDeviceクラスの実装
 * @author morimoto
 */
#include "MouseDevice.h"


MouseDevice::MouseDevice() :
m_pDInput8(NULL)
{
	for (int i = 0; i < 4; i++)
	{
		m_DIMouseState.rgbButtons[i] = MOUSEBUTTON_OFF;
		m_OldDIMouseState.rgbButtons[i] = MOUSEBUTTON_OFF;
	}
}

MouseDevice::~MouseDevice()
{
}

bool MouseDevice::Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd)
{
	m_pDInput8 = _pDInput8;
	m_hWnd = _hWnd;

	if (m_pDInput8 == NULL)
	{
		MessageBox(m_hWnd, TEXT("DirectInput8オブジェクトが有効ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInput8->CreateDevice(GUID_SysMouse, &m_pDInputDevice8, NULL))) 
	{
		MessageBox(m_hWnd, TEXT("DirectInput8マウスデバイスの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIMouse))) 
	{
		MessageBox(m_hWnd, TEXT("DirectInput8マウスデバイスのデータフォーマットの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	DIPROPDWORD diprop;
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwObj = 0;
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.dwData = 1000;
	if (FAILED(m_pDInputDevice8->SetProperty(DIPROP_BUFFERSIZE, &diprop.diph))) 
	{
		MessageBox(m_hWnd, TEXT("DirectInput8マウスデバイスのバッファ設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND))) 
	{
		MessageBox(m_hWnd, TEXT("DirectInput8マウスデバイスの協調レベルの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	m_pDInputDevice8->Acquire();

	OutputDebugString(TEXT("DirectInputのMouseDeviceの初期化に成功した\n"));

	return true;
}

void MouseDevice::Release()
{
	m_pDInputDevice8->Release();

	OutputDebugString(TEXT("DirectInputのMouseDeviceを解放しました\n"));
}

void MouseDevice::Update()
{
	HRESULT hr = m_pDInputDevice8->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pDInputDevice8->GetDeviceState(sizeof(m_DIMouseState), &m_DIMouseState);
	}

	m_MouseState.lX = m_DIMouseState.lX;
	m_MouseState.lY = m_DIMouseState.lY;
	m_MouseState.lZ = m_DIMouseState.lZ;
	GetCursorPos(&m_MouseState.CursorPos);

	RECT WindowRect;
	GetWindowRect(m_hWnd, &WindowRect);
	m_MouseState.CursorPos.x -= WindowRect.left;
	m_MouseState.CursorPos.y -= WindowRect.top;

	for (int i = 0; i < 4; i++)
	{
		if (m_DIMouseState.rgbButtons[i])
		{
			if (m_OldDIMouseState.rgbButtons[i] == MOUSEBUTTON_OFF)
			{
				m_MouseState.rgbButtons[i] = MOUSEBUTTON_PUSH;
			}
			else
			{
				m_MouseState.rgbButtons[i] = MOUSEBUTTON_ON;
			}
			m_OldDIMouseState.rgbButtons[i] = MOUSEBUTTON_ON;
		}
		else
		{
			if (m_OldDIMouseState.rgbButtons[i] == MOUSEBUTTON_ON)
			{
				m_MouseState.rgbButtons[i] = MOUSEBUTTON_RELEASE;
			}
			else
			{
				m_MouseState.rgbButtons[i] = MOUSEBUTTON_OFF;
			}
			m_OldDIMouseState.rgbButtons[i] = MOUSEBUTTON_OFF;
		}
	}
}

const MOUSESTATE& MouseDevice::GetMouseState()
{
	return m_MouseState;
}
