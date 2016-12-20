/**
 * @file   DecelerateOfTimeButtonUI.h
 * @brief  DecelerateOfTimeButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef DECELERATEOFTIMEBUTTONUI_H
#define DECELERATEOFTIMEBUTTONUI_H
#include "..\..\..\UIButton\UIButton.h"
#include "Vertex2D\Vertex2D.h"

/**
 * 時間の減速ボタンを管理するクラス
 */
class DecelerateOfTimeButtonUI : public UIButton
{
public:
	/**
	 * DecelerateOfTimeButtonUIクラスのコンストラクタ
	 */
	DecelerateOfTimeButtonUI();

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

	static const D3DXVECTOR2	m_ButtonPos;	//!< ボタンの座標
	static const D3DXVECTOR2	m_ButtonSize;	//!< ボタンの矩形サイズ
	static const D3DXVECTOR2	m_ButtonTexel[4];	//!< ボタンのテクスチャ座標

	Vertex2D*					m_pButtonVertex;
	int							m_TextureIndex;

};


#endif
