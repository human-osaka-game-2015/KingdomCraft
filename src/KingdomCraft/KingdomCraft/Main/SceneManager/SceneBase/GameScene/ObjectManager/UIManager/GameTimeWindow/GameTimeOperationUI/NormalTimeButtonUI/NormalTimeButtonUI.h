/**
 * @file   NormalTimeButtonUI.h
 * @brief  NormalTimeButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef NORMALTIMEBUTTONUI_H
#define NORMALTIMEBUTTONUI_H
#include "..\..\..\ButtonUI\ButtonUI.h"
#include "Vertex2D\Vertex2D.h"

/**
 * 時間の通常化ボタンを管理するクラス
 */
class NormalTimeButtonUI : public ButtonUI
{
public:
	/**
	 * NormalTimeButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	NormalTimeButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * NormalTimeButtonUIクラスのデストラクタ
	 */
	virtual ~NormalTimeButtonUI();

	/**
	 * NormalTimeButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * NormalTimeButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	NormalTimeButtonUI(const NormalTimeButtonUI&);
	void operator=(const NormalTimeButtonUI&);

	/**
	 * マウスオーバー時のボタン描画関数
	 */
	void MouseOverButtonDraw();

	/**
	 * ボタンの描画関数
	 */
	void ButtonDraw();

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの矩形初期サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ初期座標
	static const D3DXVECTOR2	m_MouseOverTexelOffset;//!< マウスオーバー時のテクセルオフセット値
	Vertex2D*					m_pVertex2D;
	int							m_TextureIndex;
	D3DXVECTOR2					m_ParentUIPos;

};


#endif
