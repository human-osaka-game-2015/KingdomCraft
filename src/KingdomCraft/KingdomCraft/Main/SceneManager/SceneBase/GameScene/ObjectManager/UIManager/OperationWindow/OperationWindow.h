/**
 * @file   OperationWindow.h
 * @brief  OperationWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef OPERATIONWINDOW_H
#define OPERATIONWINDOW_H
#include <vector>
#include "..\WindowUI\WindowUI.h"
#include "EventListener\OperationWindowEventListener\OperationWindowEventListener.h"

class ButtonUI;

/**
 * プレイヤーの操作UIを管理するクラス
 */
class OperationWindow : public WindowUI
{
public:
	/**
	 * OperationWindowクラスのコンストラクタ
	 */
	OperationWindow();

	/**
	 * OperationWindowクラスのデストラクタ
	 */
	virtual ~OperationWindow();

	/**
	 * OperationWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * OperationWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	/**
	 * 操作ウィンドウ内にあるUIの種類 
	 */
	enum  OPERATION_TYPE
	{
		BUILD_TYPE,			//!< 建築UI
		POLITICS_TYPE,		//!< 政治UI
		SAVE_TYPE,			//!< セーブUI
		LOAD_TYPE,			//!< ロードUI
		TITLEBACK_TYPE,		//!< タイトルバックUI
		OPERATION_MAX		//!< OperationWindowのUI数
	};

	OperationWindow(const OperationWindow&);
	void operator=(const OperationWindow&);

	/**
	 * OperationWindowの状態制御関数
	 */
	void StateControl();

	/**
	 * OperationWindowが持つWindowUIクラスの制御関数
	 */
	void WindowUIControl();

	/**
	 * OperationWindowが持つButtonUIクラスの制御関数
	 */
	void ButtonUIControl();

	/**
	 * OperationWindowが持つWindowUIクラスの描画関数
	 */
	void WindowUIDraw();

	/**
	 * OperationWindowが持つButtonUIクラスの描画関数
	 */
	void ButtonUIDraw();

	static const D3DXVECTOR2		m_DefaultPos;
	static const D3DXVECTOR2		m_DefaultSize;
	std::vector<ButtonUI*>			m_pButtonUI;
	std::vector<WindowUI*>			m_pWindowUI;
	int								m_TextureIndex;
	OperationWindowEventListener*	m_pEventListener;
	bool							m_IsButtonActive;

};


#endif
