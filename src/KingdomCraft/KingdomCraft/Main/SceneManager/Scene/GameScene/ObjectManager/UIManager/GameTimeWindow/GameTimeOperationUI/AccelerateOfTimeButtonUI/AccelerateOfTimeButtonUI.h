/**
 * @file   AccelerateOfTimeButtonUI.h
 * @brief  AccelerateOfTimeButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef ACCELERATEOFTIMEBUTTONUI_H
#define ACCELERATEOFTIMEBUTTONUI_H
#include "..\..\..\UIButton\UIButton.h"

/**
 * 時間の加速ボタンを管理するクラス
 */
class AccelerateOfTimeButtonUI : public UIButton
{
public:
	/**
	 * AccelerateOfTimeButtonUIクラスのコンストラクタ
	 */
	AccelerateOfTimeButtonUI();

	/**
	 * AccelerateOfTimeButtonUIクラスのデストラクタ
	 */
	virtual ~AccelerateOfTimeButtonUI();

	/**
	 * AccelerateOfTimeButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * AccelerateOfTimeButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	AccelerateOfTimeButtonUI(const AccelerateOfTimeButtonUI&);
	void operator=(const AccelerateOfTimeButtonUI&);

	static const D3DXVECTOR2	m_ButtonPos;		//!< ボタンの座標
	static const D3DXVECTOR2	m_ButtonSize;		//!< ボタンの矩形サイズ
	static const D3DXVECTOR2	m_ButtonTexel[4];	//!< ボタンのテクスチャ座標

	Vertex2D*					m_pButtonVertex;
	int							m_TextureIndex;

};


#endif
