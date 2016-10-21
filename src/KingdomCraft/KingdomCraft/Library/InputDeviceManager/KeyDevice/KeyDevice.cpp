#include "KeyDevice.h"


KeyDevice::KeyDevice() :
m_pDInput8(NULL)
{
	for (int i = 0; i < 256; i++)
	{
		m_KeyState[i] = KEY_OFF;
		m_OldKeyState[i] = KEY_OFF;
	}
}

KeyDevice::~KeyDevice()
{
}

bool KeyDevice::Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd)
{
	m_pDInput8 = _pDInput8;
	m_hWnd = _hWnd;

	if (m_pDInput8 == NULL)
	{
		MessageBox(m_hWnd, "DirectInput8�I�u�W�F�N�g���L���ł͂���܂���", "�G���[", MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInput8->CreateDevice(GUID_SysKeyboard, &m_pDInputDevice8, NULL)))
	{
		MessageBox(m_hWnd, "DirectInput8�L�[�f�o�C�X�̐����Ɏ��s���܂���", "�G���[", MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetDataFormat(&c_dfDIKeyboard)))
	{
		MessageBox(m_hWnd, "DirectInput8�L�[�f�o�C�X�̃f�[�^�t�H�[�}�b�g�̐ݒ�Ɏ��s���܂���", "�G���[", MB_ICONSTOP);
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
		MessageBox(m_hWnd, "DirectInput8�L�[�f�o�C�X�̃o�b�t�@�ݒ�Ɏ��s���܂���", "�G���[", MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	if (FAILED(m_pDInputDevice8->SetCooperativeLevel(m_hWnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND)))
	{
		MessageBox(m_hWnd, "DirectInput8�L�[�f�o�C�X�̋������x���̐ݒ�Ɏ��s���܂���", "�G���[", MB_ICONSTOP);
		m_pDInputDevice8->Release();
		return false;
	}

	m_pDInputDevice8->Acquire();

	OutputDebugString("DirectInput��KeyDevice�̏������ɐ�������\n");

	return true;
}

void KeyDevice::Release()
{
	m_pDInputDevice8->Release();

	OutputDebugString("DirectInput��KeyDevice��������܂���\n");
}

void KeyDevice::Update()
{
	HRESULT hr = m_pDInputDevice8->Acquire();
	if ((hr == DI_OK) || (hr == S_FALSE))
	{
		m_pDInputDevice8->GetDeviceState(sizeof(m_KeyState), &m_KeyState);
	}
}

KEYSTATE KeyDevice::GetKeyState(int _dik)
{
	KEYSTATE KeyState;

	if (m_KeyState[_dik] & 0x80)
	{
		if (m_OldKeyState[_dik] == KEY_OFF)
		{
			KeyState = KEY_PUSH;
		}
		else
		{
			KeyState = KEY_ON;
		}
		m_OldKeyState[_dik] = KEY_ON;
	}
	else
	{
		if (m_OldKeyState[_dik] == KEY_ON)
		{
			KeyState = KEY_RELEASE;
		}
		else
		{
			KeyState = KEY_OFF;
		}
		m_OldKeyState[_dik] = KEY_OFF;
	}

	return KeyState;
}