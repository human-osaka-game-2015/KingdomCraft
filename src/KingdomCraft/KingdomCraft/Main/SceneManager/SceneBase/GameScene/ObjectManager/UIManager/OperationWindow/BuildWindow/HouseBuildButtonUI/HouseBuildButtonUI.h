/**
 * @file   HouseBuildButtonUI.h
 * @brief  HouseBuildButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSEBUILDBUTTONUI_H
#define HOUSEBUILDBUTTONUI_H
#include "..\..\..\ButtonUI\ButtonUI.h"

/**
 * 建物の建設ボタンを管理するUIクラス
 */
class HouseBuildButtonUI : public ButtonUI
{
public:
	/**
	 * HouseBuildButtonUIクラスのコンストラクタ
	 */
	HouseBuildButtonUI();

	/**
	 * HouseBuildButtonUIクラスのデストラクタ
	 */
	~HouseBuildButtonUI();

	/**
	 * HouseBuildButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * HouseBuildButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	HouseBuildButtonUI(const HouseBuildButtonUI&);
	void operator=(const HouseBuildButtonUI&);

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ

};


#endif
