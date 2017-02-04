/**
 * @file   SoldierManageButtonUI.h
 * @brief  SoldierManageButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERMANAGEBUTTONUI_H
#define SOLDIERMANAGEBUTTONUI_H
#include "..\..\..\ButtonUI\ButtonUI.h"

/**
 * 兵士の管理ボタンクラス
 */
class SoldierManageButtonUI : public ButtonUI
{
public:
	/**
	 * SoldierManageButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親のUI座標
	 * @param[in] _textureIndex テクスチャインデックス
	 */
	SoldierManageButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * SoldierManageButtonUIクラスのデストラクタ
	 */
	virtual ~SoldierManageButtonUI();

	/**
	 * SoldierManageButtonUIクラスの制御関数
	 */
	virtual bool Control();

	/**
	 * SoldierManageButtonUIクラス描画関数
	 */
	virtual void Draw();

private:
	SoldierManageButtonUI(const SoldierManageButtonUI&);
	void operator=(const SoldierManageButtonUI&);

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ座標
	Vertex2D*					m_pVertex2D;		//!< ボタンを描画するVertex2Dクラス
	int							m_TextureIndex;		//!< ボタンのテクスチャインデックス
	const D3DXVECTOR2*			m_pParentUIPos;		//!< 親UIの座標

};


#endif
