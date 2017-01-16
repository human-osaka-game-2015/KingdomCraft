/**
 * @file   KingdomDataUI.h
 * @brief  KingdomDataUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMDATA_H
#define KINGDOMDATA_H
#include "..\..\TextUI\TextUI.h"

/**
 * 国内のデータUIを管理するクラス
 */
class KingdomDataUI : public TextUI
{
public:
	/**
	 * KingdomDataUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	KingdomDataUI(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * KingdomDataUIクラスのデストラクタ
	 */
	~KingdomDataUI();

	/**
	 * KingdomDataUIクラスの制御関数
	 */
	void Control();

	/**
	 * KingdomDataUIクラスの描画関数
	 */
	void Draw();

private:
	KingdomDataUI(const KingdomDataUI&);
	void operator=(const KingdomDataUI&);

	static const D3DXVECTOR2	m_MoneyTextPos;		//!< お金のテキストの初期座標
	static const D3DXVECTOR2	m_PopulationTextPos;//!< 人口のテキスト位置
	static const D3DXVECTOR2	m_DefaultFontSize;	//!< 表示するテキストのフォント初期サイズ
	D3DXVECTOR2					m_ParentUIPos;		//!< 親UIの座標位置

};


#endif
