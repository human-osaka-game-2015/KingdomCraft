/**
 * @file   BuildButtonUI.h
 * @brief  BuildButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef BUILDUI_H
#define BUILDUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\ButtonUI\ButtonUI.h"

/**
 * 建設ボタンクラス
 */
class BuildButtonUI : public ButtonUI
{
public:
	/**
	 * BuildButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	BuildButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * BuildButtonUIクラスのデストラクタ
	 */
	virtual ~BuildButtonUI();

	/**
	 * BuildButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * BuildButtonUIクラスの描画関数
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
