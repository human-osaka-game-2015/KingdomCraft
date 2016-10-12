#ifndef INPUTDEVICEMANAGER_H
#define INPUTDEVICEMANAGER_H

#define DIRECTINPUT_VERSION 0x0800

#include "KeyDevice\KeyDevice.h"
#include "MouseDevice\MouseDevice.h"

class InputDeviceManager
{
public:
	~InputDeviceManager();

	/**
	 * InputDeviceManagerのインスタンスを生成する
	 */
	static void Create()
	{
		if (m_pInputDeviceManager == NULL)
		{
			m_pInputDeviceManager = new InputDeviceManager();
		}
	}

	/**
	 * InputDeviceManagerのインスタンスを取得する
	 * @return InputDeviceManagerのインスタンス
	 */
	static InputDeviceManager* GetInstance()
	{
		return m_pInputDeviceManager;
	}

	/**
	 * InputDeviceManagerのインスタンスを破棄する
	 */
	static void Delete()
	{
		delete m_pInputDeviceManager;
		m_pInputDeviceManager = NULL;
	}

	/**
	 * InputDeviceManagerの初期化関数
	 * InputDeviceManagerを生成した後に必ず呼ばないといけない
	 * @param[in] _hWnd 入力デバイスに対応させるウィンドウハンドル
	 */
	bool Init(HWND _hWnd);

	/**
	 * InputDeviceManagerの解放関数
	 * InputDeviceManagerを破棄する前に必ず呼ばないといけない
	 */
	void Release();

	/**
	 * KeyDeviceの生成関数
	 */
	bool CreateKeyDevice();

	/**
	 * MouseDeviceの生成関数
	 */
	bool CreateMouseDevice();

	/**
	 * キーの状態を更新する
	 */
	void KeyUpdate();

	/**
	 * マウスの状態を更新する
	 */
	void MouseUpdate();

	/**
	 * キーの状態を取得する
	 * @param[in] 状態を取得したいキーのDIK
	 * @return キーの状態
	 */
	KEYSTATE GetKeyState(int _DIK);

	/**
	 * マウスの状態を取得する
	 * @return マウスの状態が格納されている構造体
	 */
	MOUSESTATE GetMouseState();

private:
	InputDeviceManager();

	static InputDeviceManager*		m_pInputDeviceManager;

	KeyDevice*		m_pKeyDevice;
	MouseDevice*	m_pMouseDevice;
	LPDIRECTINPUT8	m_pDInput8;
	HWND			m_hWnd;

};

#endif