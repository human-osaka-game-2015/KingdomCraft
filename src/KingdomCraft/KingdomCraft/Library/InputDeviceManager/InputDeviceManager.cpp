#include "InputDeviceManager.h"
#include "KeyDevice\KeyDevice.h"
#include "MouseDevice\MouseDevice.h"

InputDeviceManager* InputDeviceManager::m_pInputDeviceManager = NULL;

InputDeviceManager::InputDeviceManager() :
m_pKeyDevice(NULL),
m_pMouseDevice(NULL),
m_pDInput8(NULL)
{
}

InputDeviceManager::~InputDeviceManager()
{
}

bool InputDeviceManager::Init(HWND _hWnd)
{
	m_hWnd = _hWnd;

	if (m_pDInput8 != NULL)
	{
		MessageBox(m_hWnd, TEXT("m_pDInputの中身は空ではありません"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(DirectInput8Create(GetModuleHandle(NULL), DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDInput8, NULL)))
	{
		MessageBox(m_hWnd, TEXT("DirectInput8オブジェクトの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	OutputDebugString(TEXT("DirectInput8オブジェクトの生成に成功\n"));

	return true;
}

void InputDeviceManager::Release()
{
	if (m_pKeyDevice != NULL)
	{
		m_pKeyDevice->Release();
		delete m_pKeyDevice;

		OutputDebugString(TEXT("KeyDeviceクラスを破棄しました\n"));
	}

	if (m_pMouseDevice != NULL)
	{
		m_pMouseDevice->Release();
		delete m_pMouseDevice;

		OutputDebugString(TEXT("MouseDeviceクラスを破棄しました\n"));
	}

	m_pDInput8->Release();
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
		MessageBox(m_hWnd, TEXT("キーデバイスの初期化に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		delete m_pKeyDevice;
		m_pKeyDevice = NULL;
		return false;
	}

	OutputDebugString(TEXT("KeyDeviceクラスの生成に成功\n"));

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
		MessageBox(m_hWnd, TEXT("マウスデバイス初期化に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		delete m_pMouseDevice;
		m_pMouseDevice = NULL;
		return false;
	}

	OutputDebugString(TEXT("MouseDeviceクラスの生成に成功\n"));

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

KEYSTATE InputDeviceManager::GetKeyState(int _dik)
{
	return m_pKeyDevice->GetKeyState(_dik);
}

MOUSESTATE InputDeviceManager::GetMouseState()
{
	return m_pMouseDevice->GetMouseState();
}
