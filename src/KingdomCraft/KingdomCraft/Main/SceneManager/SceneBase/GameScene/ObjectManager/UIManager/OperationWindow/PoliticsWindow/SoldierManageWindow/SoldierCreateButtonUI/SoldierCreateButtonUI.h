/**
 * @file   SoldierCreateButtonUI.h
 * @brief  SoldierCreateButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERCREATEBUTTONUI_H
#define SOLDIERCREATEBUTTONUI_H
#include "..\..\..\..\ButtonUI\ButtonUI.h"

/**
 * 兵士の新設管理ボタンクラス
 */
class SoldierCreateButtonUI : public ButtonUI
{
public:
	/**
	 * SoldierCreateButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	SoldierCreateButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * SoldierCreateButtonUIクラスのデストラクタ
	 */
	virtual ~SoldierCreateButtonUI();

	/**
	 * SoldierCreateButtonUIクラスの制御関数
	 */
	virtual bool Control();

	/**
	 * SoldierCreateButtonUIクラス描画関数
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
