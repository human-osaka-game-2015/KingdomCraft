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
	NormalTimeButtonUI(const D3DXVECTOR2* _pParentUIPos);

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

	static const D3DXVECTOR2	m_ButtonPos;		//!< ボタンの座標
	static const D3DXVECTOR2	m_ButtonSize;		//!< ボタンの矩形サイズ
	static const D3DXVECTOR2	m_ButtonTexel[4];	//!< ボタンのテクスチャ座標
	Vertex2D*					m_pButtonVertex;
	int							m_ButtonTextureIndex;
	D3DXVECTOR2					m_ParentUIPos;

};


#endif
