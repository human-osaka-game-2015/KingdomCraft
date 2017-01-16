/**
 * @file   SaveButtonUI.h
 * @brief  SaveButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SAVEUI_H
#define SAVEUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\ButtonUI\ButtonUI.h"

/**
 * セーブボタンクラス
 */
class SaveButtonUI : public ButtonUI
{
public:
	/**
	 * SaveButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	SaveButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * SaveButtonUIクラスのデストラクタ
	 */
	virtual ~SaveButtonUI();

	/**
	 * SaveButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * SaveButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	SaveButtonUI(const SaveButtonUI&);
	void operator=(const SaveButtonUI&);

	/**
	 * マウスオーバー時のボタン描画関数
	 */
	void MouseOverButtonDraw();

	/**
	 * ボタンの描画関数
	 */
	void ButtonDraw();

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ初期座標
	static const D3DXVECTOR2	m_MouseOverTexelOffset;//!< マウスオーバー時のテクセルオフセット値
	Vertex2D*					m_pVertex2D;		//!< ボタンを描画するVertex2D
	int							m_TextureIndex;		//!< ボタンのテクスチャインデックス
	D3DXVECTOR2					m_ParentUIPos;		//!< 親UIの座標位置

};


#endif
