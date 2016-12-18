﻿/**
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
	 */
	KingdomDataUI();

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

	static const D3DXVECTOR2 m_TextPos;		//!< 表示するテキストの座標
	static const D3DXVECTOR2 m_FontSize;	//!< 表示するテキストのフォントサイズ

};


#endif
