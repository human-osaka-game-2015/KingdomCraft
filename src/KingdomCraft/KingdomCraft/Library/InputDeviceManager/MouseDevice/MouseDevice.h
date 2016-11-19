/**
 * @file   MouseDevice.h
 * @brief  MouseDeviceクラスのヘッダー
 * @author morimoto
 */
#ifndef MOUSEDEVICE_H
#define MOUSEDEVICE_H
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>	
#include <Windows.h>


/**
 * マウスの状態を表したenum
 */
enum MOUSEBUTTONSTATE	///@todo タイトルシーン側で使ってしまってるので仮置き
{
	MOUSEBUTTON_PUSH,	//!< マウスのボタンが押された瞬間の状態
	MOUSEBUTTON_RELEASE,//!< マウスのボタンが離された瞬間の状態
	MOUSEBUTTON_ON,		//!< マウスのボタンが押され続けている状態
	MOUSEBUTTON_OFF		//!< マウスのボタンが離されている状態
};

/**
 * マウスの状態を格納する構造体
 */
struct MOUSESTATE		///@todo タイトルシーン側で使ってしまってるので仮置き
{
	LONG    lX;						//!< マウスのX方向の移動量
	LONG    lY;						//!< マウスのY方向の移動量
	LONG    lZ;						//!< マウスのZ方向の移動量
	MOUSEBUTTONSTATE rgbButtons[4];	//!< マウスのボタンの状態
	POINT	CursorPos;				//!< ウィンドウ内のカーソル位置
};

/**
 * マウスデバイスの管理クラス
 */
class MouseDevice
{
public:
	/**
	 * MouseDeviceクラスのコンストラクタ
	 */
	MouseDevice();

	/**
	 * MouseDeviceクラスのデストラクタ
	 */
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
	const MOUSESTATE& GetMouseState() const;

private:
	LPDIRECTINPUT8			m_pDInput8;
	HWND					m_hWnd;
	LPDIRECTINPUTDEVICE8	m_pDInputDevice8;
	MOUSESTATE				m_MouseState;
	DIMOUSESTATE			m_DIMouseState;
	DIMOUSESTATE			m_OldDIMouseState;

};

#endif
