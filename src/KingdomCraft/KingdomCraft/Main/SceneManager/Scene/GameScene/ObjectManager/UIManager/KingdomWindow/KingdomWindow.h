/**
 * @file   KingdomWindow.h
 * @brief  KingdomWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMWINDOW_H
#define KINGDOMWINDOW_H
#include "..\UIWindow\UIWindow.h"

class KingdomDataUI;
class KingdomDemandUI;
class KingdomParameterUI;
class KingdomButtonUI;

/**
 * 王国のステータスUI管理クラス
 */
class KingdomWindow : public UIWindow
{
public:
	/**
	 * KingdomWindowクラスのコンストラクタ
	 */
	KingdomWindow();

	/**
	 * KingdomWindowクラスのデストラクタ
	 */
	virtual ~KingdomWindow();

	/**
	 * KingdomWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * KingdomWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	KingdomWindow(const KingdomWindow&);
	void operator=(const KingdomWindow&);

	static const D3DXVECTOR2	m_KingdomWindowPos;		//!< 表示するウィンドウの座標
	static const D3DXVECTOR2	m_KingdomWindowSize;	//!< 表示するウィンドウのサイズ

	KingdomDataUI*		m_pKingdomDataUI;
	KingdomDemandUI*	m_pKingdomDemandUI;
	KingdomParameterUI*	m_pKingdomParameterUI;
	KingdomButtonUI*	m_pKingdomButtonUI;
};


#endif
