/**
 * @file   SelectLeftButtonUI.h
 * @brief  SelectLeftButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SELECTLEFTBUTTONUI_H
#define SELECTLEFTBUTTONUI_H
#include "..\..\..\..\..\ButtonUI\ButtonUI.h"

class SelectLeftButtonUI : public ButtonUI
{
public:
	/**
	 * SelectLeftButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	SelectLeftButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * SelectLeftButtonUIクラスのデストラクタ
	 */
	virtual ~SelectLeftButtonUI();

	/**
	 * SelectLeftButtonUIクラスの制御関数
	 */
	virtual bool Control();

	/**
	 * SelectLeftButtonUIクラス描画関数
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
