/**
 * @file   KeyDevice.cpp
 * @brief  KeyDeviceクラスの実装
 * @author morimoto
 */
#include "KeyDevice.h"


//----------------------------------------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------------------------------------

KeyDevice::KeyDevice() :
m_pDInput8(NULL),
m_hWnd(NULL),
m_pDInputDevice8(NULL)
{
	for (int i = 0; i < 256; i++)
	{
		m_pDIKeyState[i] = 0;
		m_pOldDIKeyState[i] = 0;
	}
}

KeyDevice::~KeyDevice()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool KeyDevice::Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd)
{
	if (m_pDInput8 != NULL)
	{
		MessageBox(m_hWnd, TEXT("KeyDeviceクラスは既に初期化されています"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_pDInput8 = _pDInput8;
	m_hWnd = _hWnd;

	if (m_pDInput8 == NULL)
	{
		MessageBox(m_hWnd, TEXT("DirectInput8オブジェクトが有効ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInput8->CreateDevice(GUID_SysKeyboard, &m_pDInputDevice8, NULL)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8キーデバイスの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8キーデバイスのデータフォーマットの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
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
		MessageBox(m_hWnd, TEXT("DirectInput8キーデバイスのバッファ設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8キーデバイスの協調レベルの設定に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	m_pDInputDevice8->Acquire();

	OutputDebugString(TEXT("DirectInputのKeyDeviceの初期化に成功した\n"));

	return true;
}

void KeyDevice::Release()
{
	if (m_pDInputDevice8 != NULL)
	{
		m_pDInputDevice8->Release();
		m_pDInputDevice8 = NULL;
		m_pDInput8 = NULL;
		OutputDebugString(TEXT("DirectInputのKeyDeviceを解放しました\n"));
	}
}

void KeyDevice::Update()
{
	HRESULT hr = m_pDInputDevice8->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pDInputDevice8->GetDeviceState(sizeof(m_pDIKeyState), &m_pDIKeyState);
	}
}

void KeyDevice::KeyCheck(int _dik)
{
	if (m_pDIKeyState[_dik] & 0x80)
	{
		if (m_pOldDIKeyState[_dik] == KEY_OFF)
		{
			m_pKeyState[_dik] = KEY_PUSH;
		}
		else
		{
			m_pKeyState[_dik] = KEY_ON;
		}
		m_pOldDIKeyState[_dik] = KEY_ON;
	}
	else
	{
		if (m_pOldDIKeyState[_dik] == KEY_ON)
		{
			m_pKeyState[_dik] = KEY_RELEASE;
		}
		else
		{
			m_pKeyState[_dik] = KEY_OFF;
		}
		m_pOldDIKeyState[_dik] = KEY_OFF;
	}
}

const KeyDevice::KEYSTATE* KeyDevice::GetKeyState() const
{
	return m_pKeyState;
}
