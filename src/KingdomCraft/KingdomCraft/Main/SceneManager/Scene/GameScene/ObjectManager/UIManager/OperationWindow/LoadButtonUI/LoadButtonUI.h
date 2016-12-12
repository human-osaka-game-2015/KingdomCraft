/**
 * @file   LoadButtonUI.h
 * @brief  LoadButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef LOADUI_H
#define LOADUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\UIButton\UIButton.h"

/**
 * ロードボタンクラス
 */
class LoadButtonUI : public UIButton
{
public:
	/**
	 *LoadButtonUIクラスのコンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	LoadButtonUI(int _textureIndex);

	/**
	 * LoadButtonUIクラスのデストラクタ
	 */
	virtual ~LoadButtonUI();

	/**
	 * LoadButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * LoadButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	static const D3DXVECTOR2	m_ButtonPos;		//!< ボタンの座標
	static const D3DXVECTOR2	m_ButtonSize;		//!< ボタンの矩形サイズ
	static const D3DXVECTOR2	m_ButtonTexel[4];	//!< ボタンのテクスチャ座標
	Vertex2D*					m_pButtonVertex;
	int							m_TextureIndex;

};


#endif
