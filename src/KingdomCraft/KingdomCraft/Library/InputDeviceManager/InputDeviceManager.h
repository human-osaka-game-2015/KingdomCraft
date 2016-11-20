/**
 * @file   InputDeviceManager.h
 * @brief  InputDeviceManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef INPUTDEVICEMANAGER_H
#define INPUTDEVICEMANAGER_H
#define DIRECTINPUT_VERSION 0x0800
#include "KeyDevice\KeyDevice.h"
#include "MouseDevice\MouseDevice.h"

/**
 * 入力デバイスを管理するクラス
 */
class InputDeviceManager
{
public:
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
	 * KeyDeviceの状態を更新する
	 */
	void KeyUpdate();

	/**
	 * MouseDeviceの状態を更新する
	 */
	void MouseUpdate();

	/**
	 * キーの状態を更新する
	 * @param[in] 更新したいキーのDIK
	 */
	void KeyCheck(int _dik);

	/**
	 * キーの状態が格納されている配列を取得する
	 * @return キーの状態が格納されている配列
	 */
	const KeyDevice::KEYSTATE* GetKeyState() const;

	/**
	 * マウスの状態を取得する
	 * @return マウスの状態が格納されている構造体
	 */
	const MOUSESTATE GetMouseState() const;

private:
	/**
	 * InputDeviceManagerクラスのコンストラクタ
	 */
	InputDeviceManager();

	/**
	 * InputDeviceManagerクラスのデストラクタ
	 */
	~InputDeviceManager();

	static InputDeviceManager*	m_pInputDeviceManager;

	KeyDevice*		m_pKeyDevice;
	MouseDevice*	m_pMouseDevice;
	LPDIRECTINPUT8	m_pDInput8;
	HWND			m_hWnd;

};

#endif
