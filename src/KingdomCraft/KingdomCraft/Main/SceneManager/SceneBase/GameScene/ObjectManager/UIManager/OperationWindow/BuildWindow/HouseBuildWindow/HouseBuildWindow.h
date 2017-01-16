/**
 * @file   HouseBuildWindow.h
 * @brief  HouseBuildWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSEBUILDWINDOW_H
#define HOUSEBUILDWINDOW_H
#include <vector>
#include "..\..\..\WindowUI\WindowUI.h"
#include "..\..\..\ButtonUI\ButtonUI.h"
#include "EventListener\BuildWindowEventListener\BuildWindowEventListener.h"
#include "InputDeviceManager\InputDeviceManager.h"

/**
 * 建物建設ウィンドウ
 */
class HouseBuildWindow : public WindowUI
{
public:
	/**
	 * HouseBuildWindowクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	HouseBuildWindow(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * HouseBuildWindowクラスのデストラクタ
	 */
	virtual ~HouseBuildWindow();

	/**
	 * HouseBuildWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * HouseBuildWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	/**
	 * HouseBuildWindowクラスの状態列挙子
	 */
	enum STATE
	{
		NONE,			//!< 何もしない状態
		START_STATE,	//!< 開始処理を行う状態
		PROC_STATE,		//!< 通常処理を行う状態
		END_STATE		//!< 終了処理を行う状態
	};

	HouseBuildWindow(const HouseBuildWindow&);
	void operator=(const HouseBuildWindow&);

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

	/**
	 * HouseuildWindowが持つButtonUI描画関数
	 */
	void ButtonUIDraw();

	/**
	 * HouseuildWindowが持つButtonUI制御関数
	 */
	void ButtonUIControl();

	static const D3DXVECTOR2	m_DefaultPos;
	static const D3DXVECTOR2	m_DefaultSize;
	static const D3DXVECTOR2	m_MovePos;
	static const float			m_MoveSpeed;

	std::vector<ButtonUI*>		m_pButtonUI;
	BuildWindowEventListener*	m_pEventListener;
	STATE						m_State;
	MouseDevice::MOUSESTATE		m_MouseState;
	D3DXVECTOR2					m_ParentUIPos;
	int							m_TextureIndex;

};


#endif
