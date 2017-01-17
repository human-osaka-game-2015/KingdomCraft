﻿/**
 * @file   PoliticsWindow.h
 * @brief  PoliticsWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef POLITICSWINDOW_H
#define POLITICSWINDOW_H
#include "..\..\WindowUI\WindowUI.h"
#include "EventListener\OperationWindowEventListener\OperationWindowEventListener.h"
#include "InputDeviceManager\InputDeviceManager.h"

/**
 * 政治を管理するWindowクラス
 */
class PoliticsWindow : public WindowUI
{
public:
	/**
	 * PoliticsWindowクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	PoliticsWindow(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * PoliticsWindowクラスのデストラクタ
	 */
	virtual ~PoliticsWindow();

	/**
	 * PoliticsWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * PoliticsWindowクラスの描画関数 
	 */
	virtual void Draw();

private:
	/**
	 * PoliticsWindowクラスの状態列挙子
	 */
	enum STATE
	{
		NONE,			//!< 何もしない状態
		START_STATE,	//!< 開始処理を行う状態
		PROC_STATE,		//!< 通常処理を行う状態
		END_STATE		//!< 終了処理を行う状態
	};

	PoliticsWindow(const PoliticsWindow&);
	void operator=(const PoliticsWindow&);

	/**
	 * マウスの状態チェックを行う関数
	 */
	void MouseCheckControl();

	/**
	 * 状態の制御を行う関数
	 */
	void StateControl();

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


	static const D3DXVECTOR2	m_DefaultPos;
	static const D3DXVECTOR2	m_DefaultSize;
	static const D3DXVECTOR2	m_MovePos;
	static const float			m_MoveSpeed;

	OperationWindowEventListener*	m_pEventListener;
	STATE							m_State;
	MouseDevice::MOUSESTATE			m_MouseState;
	D3DXVECTOR2						m_ParentUIPos;

};


#endif