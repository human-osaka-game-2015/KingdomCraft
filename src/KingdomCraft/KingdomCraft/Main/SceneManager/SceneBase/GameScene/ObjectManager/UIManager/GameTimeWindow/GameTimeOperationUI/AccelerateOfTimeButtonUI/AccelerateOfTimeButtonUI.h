/**
 * @file   AccelerateOfTimeButtonUI.h
 * @brief  AccelerateOfTimeButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef ACCELERATEOFTIMEBUTTONUI_H
#define ACCELERATEOFTIMEBUTTONUI_H
#include "..\..\..\ButtonUI\ButtonUI.h"

/**
 * 時間の加速ボタンを管理するクラス
 */
class AccelerateOfTimeButtonUI : public ButtonUI
{
public:
	/**
	 * AccelerateOfTimeButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	AccelerateOfTimeButtonUI(const D3DXVECTOR2* _pParentUIPos);

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

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの矩形初期サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ初期座標
	Vertex2D*					m_pVertex2D;
	int							m_TextureIndex;
	D3DXVECTOR2					m_ParentUIPos;

};


#endif
