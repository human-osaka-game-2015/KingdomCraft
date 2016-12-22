/**
 * @file   InputDeviceManager.cpp
 * @brief  InputDeviceManagerクラスの実装
 * @author morimoto
 */
#include "InputDeviceManager.h"
#include "KeyDevice\KeyDevice.h"
#include "MouseDevice\MouseDevice.h"


//----------------------------------------------------------------------------------------------------
// Static Private Variables
//----------------------------------------------------------------------------------------------------

InputDeviceManager* InputDeviceManager::m_pInputDeviceManager = NULL;


//----------------------------------------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------------------------------------

InputDeviceManager::InputDeviceManager() :
m_pKeyDevice(NULL),
m_pMouseDevice(NULL),
m_pDInput8(NULL),
m_hWnd(NULL)
{
}

InputDeviceManager::~InputDeviceManager()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool InputDeviceManager::Init(HWND _hWnd)
{
	if (m_pDInput8 != NULL)
	{
		MessageBox(_hWnd, TEXT("m_pDInput8の中身は空ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(DirectInput8Create(
		GetModuleHandle(NULL), 
		DIRECTINPUT_VERSION, 
		IID_IDirectInput8, 
		reinterpret_cast<void**>(&m_pDInput8), 
		NULL)))
	{
		MessageBox(_hWnd, TEXT("DirectInput8オブジェクトの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_hWnd = _hWnd;

	OutputDebugString(TEXT("DirectInput8オブジェクトの生成に成功\n"));

	return true;
}

void InputDeviceManager::Release()
{
	if (m_pKeyDevice != NULL)
	{
		m_pKeyDevice->Release();
		delete m_pKeyDevice;
		m_pKeyDevice = NULL;
	}

	if (m_pMouseDevice != NULL)
	{
		m_pMouseDevice->Release();
		delete m_pMouseDevice;
		m_pMouseDevice = NULL;
	}

	if (m_pDInput8 != NULL)
	{
		m_pDInput8->Release();
		m_pDInput8 = NULL;
	}
}

bool InputDeviceManager::CreateKeyDevice()
{
	if (m_pKeyDevice != NULL)
	{
		MessageBox(m_hWnd, TEXT("m_pKeyDeviceの中身は空ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_pKeyDevice = new KeyDevice();

	if (!m_pKeyDevice->Init(m_pDInput8, m_hWnd))
	{
		MessageBox(m_hWnd, TEXT("m_pKeyDevice初期化に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		delete m_pKeyDevice;
		m_pKeyDevice = NULL;
		return false;
	}

	OutputDebugString(TEXT("m_pKeyDeviceの初期化に成功\n"));

	return true;
}

bool InputDeviceManager::CreateMouseDevice()
{
	if (m_pMouseDevice != NULL)
	{
		MessageBox(m_hWnd, TEXT("m_pMouseDeviceの中身は空ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	m_pMouseDevice = new MouseDevice();

	if (!m_pMouseDevice->Init(m_pDInput8, m_hWnd))
	{
		MessageBox(m_hWnd, TEXT("m_pMouseDeviceの初期化に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		delete m_pMouseDevice;
		m_pMouseDevice = NULL;
		return false;
	}

	OutputDebugString(TEXT("m_pMouseDeviceの初期化に成功\n"));

	return true;
}

void InputDeviceManager::KeyUpdate()
{
	m_pKeyDevice->Update();
}

void InputDeviceManager::MouseUpdate()
{
	m_pMouseDevice->Update();
}

void InputDeviceManager::KeyCheck(int _dik)
{
	m_pKeyDevice->KeyCheck(_dik);
}

const KeyDevice::KEYSTATE* InputDeviceManager::GetKeyState() const
{
	return m_pKeyDevice->GetKeyState();
}

const MouseDevice::MOUSESTATE InputDeviceManager::GetMouseState() const
{
	return m_pMouseDevice->GetMouseState();
}
