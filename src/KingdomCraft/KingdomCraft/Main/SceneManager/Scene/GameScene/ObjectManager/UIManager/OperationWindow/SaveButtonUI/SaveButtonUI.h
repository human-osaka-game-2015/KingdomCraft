/**
 * @file   SaveButtonUI.h
 * @brief  SaveButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SAVEUI_H
#define SAVEUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\UIButton\UIButton.h"

/**
 * セーブボタンクラス
 */
class SaveButtonUI : public UIButton
{
public:
	/**
	 * SaveButtonUIクラスのコンストラクタ
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	SaveButtonUI(int _textureIndex);

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
	static const D3DXVECTOR2	m_ButtonPos;		//!< ボタンの座標
	static const D3DXVECTOR2	m_ButtonSize;		//!< ボタンの矩形サイズ
	static const D3DXVECTOR2	m_ButtonTexel[4];	//!< ボタンのテクスチャ座標
	Vertex2D*					m_pButtonVertex;
	int							m_TextureIndex;

};


#endif
