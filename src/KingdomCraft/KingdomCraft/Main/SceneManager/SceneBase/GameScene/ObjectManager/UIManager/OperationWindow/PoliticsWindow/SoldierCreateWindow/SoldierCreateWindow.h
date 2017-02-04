/**
 * @file   SoldierCreateWindow.h
 * @brief  SoldierCreateWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERCREATEWINDOW_H
#define SOLDIERCREATEWINDOW_H
#include "..\..\..\WindowUI\WindowUI.h"
#include "InputDeviceManager\InputDeviceManager.h"

class SoldierManageWindowEventListener;
class SoldierNumSelect;
class SoldierTypeSelect;

/**
 * 兵士の作成管理ウィンドウクラス
 */
class SoldierCreateWindow : public WindowUI
{
public:
	/**
	 * SoldierCreateWindowクラスのコンストラクタ
	 */
	SoldierCreateWindow();

	/**
	 * SoldierCreateWindowクラスのデストラクタ
	 */
	virtual ~SoldierCreateWindow();

	/**
	 * SoldierCreateWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * SoldierCreateWindowクラス描画関数
	 */
	virtual void Draw();

private:
	/**
	 * SoldierCreateWindowクラスの状態列挙子
	 */
	enum STATE
	{
		NONE,
		START_STATE,
		PROC_STATE,
		END_STATE
	};

	SoldierCreateWindow(const SoldierCreateWindow&);
	void operator=(const SoldierCreateWindow&);

	/**
	 * マウスの状態チェックを行う関数
	 */
	void MouseCheckControl();

	/**
	 * イベントの処理を行う関数
	 */
	void EventMessageControl();

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

	static const D3DXVECTOR2			m_DefaultPos;
	static const D3DXVECTOR2			m_DefaultSize;
	static const D3DXVECTOR2			m_MovePos;
	static const float					m_MoveSpeed;
	STATE								m_State;
	MouseDevice::MOUSESTATE				m_MouseState;
	SoldierManageWindowEventListener*	m_pEventListener;
	SoldierNumSelect*					m_pSoldierNumSelect;
	SoldierTypeSelect*					m_pSoldierTypeSelect;
	int									m_TextureIndex;

};


#endif
