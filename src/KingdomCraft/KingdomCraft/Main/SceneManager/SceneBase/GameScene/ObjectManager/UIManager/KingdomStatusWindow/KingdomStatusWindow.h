﻿/**
 * @file   KingdomStatusWindow.h
 * @brief  KingdomStatusWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMSTATUSWINDOW_H
#define KINGDOMSTATUSWINDOW_H
#include "..\WindowUI\WindowUI.h"

class KingdomDataUI;
class KingdomDemandUI;
class KingdomParameterUI;
class KingdomButtonUI;

/**
 * 王国のステータスUI管理クラス
 */
class KingdomStatusWindow : public WindowUI
{
public:
	/**
	 * KingdomStatusWindowクラスのコンストラクタ
	 */
	KingdomStatusWindow();

	/**
	 * KingdomStatusWindowクラスのデストラクタ
	 */
	virtual ~KingdomStatusWindow();

	/**
	 * KingdomStatusWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * KingdomStatusWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	KingdomStatusWindow(const KingdomStatusWindow&);
	void operator=(const KingdomStatusWindow&);

	static const D3DXVECTOR2	m_DefaultPos;	//!< 表示するウィンドウの初期座標
	static const D3DXVECTOR2	m_DefaultSize;	//!< 表示するウィンドウの初期サイズ
	KingdomDataUI*				m_pKingdomDataUI;
	KingdomDemandUI*			m_pKingdomDemandUI;
	KingdomParameterUI*			m_pKingdomParameterUI;
	KingdomButtonUI*			m_pKingdomButtonUI;

};


#endif
