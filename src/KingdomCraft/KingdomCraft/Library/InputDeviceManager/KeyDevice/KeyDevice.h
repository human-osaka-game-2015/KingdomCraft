#ifndef KEYDEVICE_H
#define KEYDEVICE_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include <Windows.h>


enum KEYSTATE
{
	//! キーが押された瞬間の状態
	KEY_PUSH,

	//! キーが離された瞬間の状態
	KEY_RELEASE,

	//! キーが押され続けている状態
	KEY_ON,

	//! キーが押されていない状態
	KEY_OFF
};

class KeyDevice
{
public:
	KeyDevice();
	~KeyDevice();

	/**
	 * KeyDeviceの初期化関数
	 * @param[in] _pDInput8 DirectInputオブジェクト
	 * @param[in] _hWnd KeyDeviceに対応させるウィンドウハンドル
	 * @return デバイスの初期化に成功したらtrueが返る
	 */
	bool Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd);

	/**
	 * KeyDeviceの解放関数
	 */
	void Release();

	/**
	 * キーの状態を更新する
	 */
	void Update();

	/**
	 * キーの状態を取得する
	 * @param[in] 状態を取得したいキーのDIK
	 * @return キーの状態
	 */
	KEYSTATE GetKeyState(int _dik);

private:
	LPDIRECTINPUT8			m_pDInput8;
	HWND					m_hWnd;
	LPDIRECTINPUTDEVICE8	m_pDInputDevice8;
	BYTE					m_KeyState[256];
	BYTE					m_OldKeyState[256];

};

#endif