﻿/**
 * @file   SoldierDestroyButtonUI.h
 * @brief  SoldierDestroyButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERDESTROYBUTTONUI_H
#define SOLDIERDESTROYBUTTONUI_H
#include "..\..\..\..\ButtonUI\ButtonUI.h"

/**
 * 兵士の破棄管理ボタンクラス
 */
class SoldierDestroyButtonUI : public ButtonUI
{
public:
	/**
	 * SoldierDestroyButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	SoldierDestroyButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * SoldierDestroyButtonUIクラスのデストラクタ
	 */
	virtual ~SoldierDestroyButtonUI();

	/**
	 * SoldierDestroyButtonUIクラスの制御関数
	 */
	virtual bool Control();

	/**
	 * SoldierDestroyButtonUIクラス描画関数
	 */
	virtual void Draw();

private:
	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ座標
	Vertex2D*					m_pVertex2D;		//!< ボタンを描画するVertex2Dクラス
	int							m_TextureIndex;		//!< ボタンのテクスチャインデックス
	const D3DXVECTOR2*			m_pParentUIPos;

};


#endif
