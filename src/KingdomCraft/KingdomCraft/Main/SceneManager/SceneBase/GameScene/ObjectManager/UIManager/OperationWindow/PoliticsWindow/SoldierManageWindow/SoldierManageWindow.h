/**
 * @file   SoldierManageWindow.h
 * @brief  SoldierManageWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERMANAGEWINDOW_H
#define SOLDIERMANAGEWINDOW_H
#include <vector>
#include "..\..\..\WindowUI\WindowUI.h"
#include "..\..\..\ButtonUI\ButtonUI.h"
#include "InputDeviceManager\InputDeviceManager.h"

class PoliticsWindowEventListener;
class SoldierManageWindowEventListener;

/**
 * 兵士の管理ウィンドウクラス
 */
class SoldierManageWindow : public WindowUI
{
public:
	/**
	 * SoldierManageWindowクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親のUI座標
	 */
	SoldierManageWindow(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * SoldierManageWindowクラスのデストラクタ
	 */
	virtual ~SoldierManageWindow();

	/**
	 * SoldierManageWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * SoldierManageWindowクラス描画関数
	 */
	virtual void Draw();

private:
	/**
	 * SoldierManageWindowクラスの状態列挙子
	 */
	enum STATE
	{
		NONE,
		WAIT_STATE,
		START_STATE,
		PROC_STATE,
		END_STATE
	};

	SoldierManageWindow(const SoldierManageWindow&);
	void operator=(const SoldierManageWindow&);

	/**
	 * マウスの状態チェックを行う関数
	 */
	void MouseCheckControl();

	/**
	 * イベントの処理を行う関数
	 */
	void EventMessageControl();

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
	 * 配下にあるボタンの制御を行う関数
	 */
	void ButtonUIControl();

	/**
	 * 配下にあるボタンの描画を行う関数
	 */
	void ButtonUIDraw();

	static const D3DXVECTOR2			m_DefaultPos;
	static const D3DXVECTOR2			m_DefaultSize;
	static const D3DXVECTOR2			m_MovePos;
	static const float					m_MoveSpeed;
	PoliticsWindowEventListener*		m_pParentEventListener;
	SoldierManageWindowEventListener*	m_pEventListener;
	STATE								m_State;
	MouseDevice::MOUSESTATE				m_MouseState;
	D3DXVECTOR2							m_ParentUIPos;
	int									m_TextureIndex;
	std::vector<ButtonUI*>				m_pButtonUI;

};


#endif
