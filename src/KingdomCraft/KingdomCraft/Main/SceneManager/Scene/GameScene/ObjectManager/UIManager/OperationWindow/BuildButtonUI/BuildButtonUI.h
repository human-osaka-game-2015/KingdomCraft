/**
 * @file   BuildButtonUI.h
 * @brief  BuildButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef BUILDUI_H
#define BUILDUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\UIButton\UIButton.h"

/**
 * 建設ボタンクラス
 */
class BuildButtonUI : public UIButton
{
public:
	/**
	 * BuildButtonUIクラスのコンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	BuildButtonUI(int _textureIndex);

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
	static const D3DXVECTOR2	m_ButtonPos;		//!< ボタンの座標
	static const D3DXVECTOR2	m_ButtonSize;		//!< ボタンの矩形サイズ
	static const D3DXVECTOR2	m_ButtonTexel[4];	//!< ボタンのテクスチャ座標
	Vertex2D*					m_pButtonVertex;
	int							m_TextureIndex;

};


#endif
