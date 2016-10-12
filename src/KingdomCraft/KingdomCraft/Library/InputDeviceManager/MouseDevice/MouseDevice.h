#ifndef MOUSEDEVICE_H
#define MOUSEDEVICE_H

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include <Windows.h>

enum MOUSEBUTTONSTATE
{
	//! マウスのボタンが押された瞬間の状態
	MOUSEBUTTON_PUSH,

	//! マウスのボタンが離された瞬間の状態
	MOUSEBUTTON_RELEASE,

	//! マウスのボタンが押され続けている状態
	MOUSEBUTTON_ON,

	//! マウスのボタンが離されている状態
	MOUSEBUTTON_OFF
};

struct MOUSESTATE
{
	LONG    lX;						// マウスのX方向の移動量
	LONG    lY;						// マウスのY方向の移動量
	LONG    lZ;						// マウスのZ方向の移動量
	MOUSEBUTTONSTATE rgbButtons[4];	// マウスのボタンの状態
	POINT	CursorPos;				// ウィンドウ内のカーソル位置
};

class MouseDevice
{
public:
	MouseDevice();
	~MouseDevice();

	/**
	 * MouseDeviceの初期化関数
	 * @param[in] _pDInput8 DirectInputオブジェクト
	 * @param[in] _hWnd KeyDeviceに対応させるウィンドウハンドル
	 * @return デバイスの初期化に成功したらtrueが返る
	 */
	bool Init(LPDIRECTINPUT8 _pDInput8, HWND _hWnd);

	/**
	 * MouseDeviceの解放関数
	 */
	void Release();

	/**
	 * マウスの状態を更新する
	 */
	void Update();

	/**
	 * マウスの状態を取得する
	 * @return マウスの状態が格納されている構造体
	 */
	MOUSESTATE GetMouseState();

private:
	LPDIRECTINPUT8			m_pDInput8;
	HWND					m_hWnd;
	LPDIRECTINPUTDEVICE8	m_pDInputDevice8;
	DIMOUSESTATE			m_MouseState;
	DIMOUSESTATE			m_OldMouseState;

};

#endif