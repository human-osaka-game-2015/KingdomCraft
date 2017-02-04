/**
 * @file   SoldierDispatchButtonUI.h
 * @brief  SoldierDispatchButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERDISPATCHBUTTONUI_H
#define SOLDIERDISPATCHBUTTONUI_H
#include "..\..\..\..\ButtonUI\ButtonUI.h"

/**
 * 兵士の派兵管理ボタンクラス
 */
class SoldierDispatchButtonUI : public ButtonUI
{
public:
	/**
	 * SoldierDispatchButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	SoldierDispatchButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * SoldierDispatchButtonUIクラスのデストラクタ
	 */
	virtual ~SoldierDispatchButtonUI();

	/**
	 * SoldierDispatchButtonUIクラスの制御関数
	 */
	virtual bool Control();

	/**
	 * SoldierDispatchButtonUIクラス描画関数
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
