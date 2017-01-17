﻿/**
 * @file   BuildWindow.h
 * @brief  BuildWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef BUILDWINDOW_H
#define BUILDWINDOW_H
#include <vector>
#include "..\..\WindowUI\WindowUI.h"
#include "..\..\ButtonUI\ButtonUI.h"
#include "EventListener\OperationWindowEventListener\OperationWindowEventListener.h"
#include "EventListener\BuildWindowEventListener\BuildWindowEventListener.h"
#include "InputDeviceManager\InputDeviceManager.h"

/**
 * 建設を管理するWindowクラス
 */
class BuildWindow : public WindowUI
{
public:
	/**
	 * BuildWindowクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	BuildWindow(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * BuildWindowクラスのデストラクタ
	 */
	virtual ~BuildWindow();

	/**
	 * BuildWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * BuildWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	/**
	 * BuildWindowクラスの状態列挙子
	 */
	enum STATE
	{
		NONE,			//!< 何もしない状態
		WAIT_STATE,		//!< 子からの処理を待つ状態
		START_STATE,	//!< 開始処理を行う状態
		PROC_STATE,		//!< 通常処理を行う状態
		END_STATE		//!< 終了処理を行う状態
	};

	BuildWindow(const BuildWindow&);
	void operator=(const BuildWindow&);

	/**
	 * マウスの状態チェックを行う関数
	 */
	void MouseCheckControl();

	/**
	 * 状態の制御を行う関数
	 */
	void StateControl();

	/**
	 * 待機時の処理を行う関数
	 */
	void WaitControl();

	/**
	 * 開始処理を行う関数
	 */
	void StartControl();

	/**
	 * 通常処理を行う関数
	 */
	void ProcControl();

	/**
	 * 終了処理を行う関数
	 */
	void EndControl();

	/**
	 * BuildWindowが持つButtonUIの制御を行う関数
	 */
	void ButtonUIControl();

	/**
	 * BuildWindowが持つWindowUIの制御を行う関数
	 */
	void WindowUIControl();

	/**
	 * BuildWindowが持つButtonUIの描画を行う関数
	 */
	void ButtonUIDraw();

	/**
	 * BuildWindowが持つWindowUIの制御を行う関数
	 */
	void WindowUIDraw();

	static const D3DXVECTOR2	m_DefaultPos;
	static const D3DXVECTOR2	m_DefaultSize;
	static const D3DXVECTOR2	m_MovePos;
	static const float			m_MoveSpeed;

	std::vector<ButtonUI*>			m_pButtonUI;
	std::vector<WindowUI*>			m_pWindowUI;
	OperationWindowEventListener*	m_pParentEventListener;
	BuildWindowEventListener*		m_pEventListener;
	STATE							m_State;
	MouseDevice::MOUSESTATE			m_MouseState;
	D3DXVECTOR2						m_ParentUIPos;
	int								m_TextureIndex;

};


#endif