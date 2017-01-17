/**
 * @file   KingdomWindow.h
 * @brief  KingdomWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMWINDOW_H
#define KINGDOMWINDOW_H
#include "..\WindowUI\WindowUI.h"
#include "InputDeviceManager\InputDeviceManager.h"

class KingdomWindowEventListener;

/**
 * 王国の詳細情報を表示するUIクラス
 */
class KingdomWindow : public WindowUI
{
public:
	/**
	 * KingdomWindowクラスのコンストラクタ
	 */
	KingdomWindow();

	/**
	 * KingdomWindowクラスのデストラクタ
	 */
	~KingdomWindow();

	/**
	 * KingdomWindowクラスの制御関数
	 */
	void Control();

	/**
	 * KingdomWindowクラスの描画関数
	 */
	void Draw();

private:
	/**
	 * KingdomWindowクラスの状態列挙子
	 */
	enum STATE
	{
		NONE,
		WAIT_STATE,	//!< 子からの処理を待つ状態
		PROC_STATE,	//!< 通常処理を行う状態
		STATE_MAX
	};

	/**
	 * 状態の制御を行う関数
	 */
	void StateControl();

	/**
	 * マウスの状態をチェックする関数
	 */
	void MouseCheckControl();

	/**
	 * 通常処理を行う関数
	 */
	void ProcControl();


	static const D3DXVECTOR2	m_DefaultWindowPos;
	static const D3DXVECTOR2	m_DefaultWindowSize;

	KingdomWindowEventListener*	m_pEventListener;
	STATE						m_State;
	MouseDevice::MOUSESTATE		m_MouseState;

};


#endif
