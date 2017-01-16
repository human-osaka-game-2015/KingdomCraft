/**
 * @file   DecelerateOfTimeButtonUI.h
 * @brief  DecelerateOfTimeButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef DECELERATEOFTIMEBUTTONUI_H
#define DECELERATEOFTIMEBUTTONUI_H
#include "..\..\..\ButtonUI\ButtonUI.h"
#include "Vertex2D\Vertex2D.h"

/**
 * 時間の減速ボタンを管理するクラス
 */
class DecelerateOfTimeButtonUI : public ButtonUI
{
public:
	/**
	 * DecelerateOfTimeButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	DecelerateOfTimeButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * DecelerateOfTimeButtonUIクラスのデストラクタ
	 */
	virtual ~DecelerateOfTimeButtonUI();

	/**
	 * DecelerateOfTimeButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * DecelerateOfTimeButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	DecelerateOfTimeButtonUI(const DecelerateOfTimeButtonUI&);
	void operator=(const DecelerateOfTimeButtonUI&);

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
