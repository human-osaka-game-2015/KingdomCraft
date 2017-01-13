/**
 * @file   HouseDestroyButtonUI.h
 * @brief  HouseDestroyButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSEDESTROYBUTTONUI_H
#define HOUSEDESTROYBUTTONUI_H
#include "..\..\..\ButtonUI\ButtonUI.h"

/**
 * 建物の撤去ボタンを管理するUIクラス
 */
class HouseDestroyButtonUI : public ButtonUI
{
public:
	/**
	 * HouseDestroyButtonUIクラスのコンストラクタ
	 */
	HouseDestroyButtonUI();

	/**
	 * HouseDestroyButtonUIクラスのデストラクタ
	 */
	virtual ~HouseDestroyButtonUI();

	/**
	* HouseDestroyButtonUIクラスの制御関数
	* @return ボタンが押されたらtrue
	*/
	virtual bool Control();

	/**
	* HouseDestroyButtonUIクラスの描画関数
	*/
	virtual void Draw();

private:
	HouseDestroyButtonUI(const HouseDestroyButtonUI&);
	void operator=(const HouseDestroyButtonUI&);

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ

};


#endif
