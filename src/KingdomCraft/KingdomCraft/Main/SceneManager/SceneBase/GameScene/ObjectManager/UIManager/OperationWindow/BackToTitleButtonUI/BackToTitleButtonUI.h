/**
 * @file   BackToTitleButtonUI.h
 * @brief  BackToTitleButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLEBACKUI_H
#define TITLEBACKUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\ButtonUI\ButtonUI.h"

/**
 * タイトルバックボタンクラス
 */
class BackToTitleButtonUI : public ButtonUI
{
public:
	/**
	 * BackToTitleButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	BackToTitleButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * BackToTitleButtonUIクラスのデストラクタ
	 */
	virtual ~BackToTitleButtonUI();

	/**
	 * BackToTitleButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * BackToTitleButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ初期座標
	Vertex2D*					m_pVertex2D;		//!< ボタンを描画するVertex2Dクラス
	int							m_TextureIndex;		//!< ボタンのテクスチャインデックス
	D3DXVECTOR2					m_ParentUIPos;		//!< 親UIの座標位置

};


#endif
