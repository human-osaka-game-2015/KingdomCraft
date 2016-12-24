/**
 * @file   KingdomButtonUI.h
 * @brief  KingdomButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMBUTTONUI_H
#define KINGDOMBUTTONUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\ButtonUI\ButtonUI.h"

/**
 * 王国パラメータの詳細表示ボタンを管理するクラス
 */
class KingdomButtonUI : public ButtonUI
{
public:
	/** 
	 * KingdomButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	KingdomButtonUI(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * KingdomButtonUIクラスのデストラクタ
	 */
	~KingdomButtonUI();

	/**
	 * KingdomButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	bool Control();

	/**
	 * KingdomButtonUIクラスの描画関数
	 */
	void Draw();

private:
	KingdomButtonUI(const KingdomButtonUI&);
	void operator=(const KingdomButtonUI&);

	static const D3DXVECTOR2	m_ButtonPos;			//!< ボタンを表示する座標
	static const D3DXVECTOR2	m_ButtonSize;			//!< ボタンのサイズ
	static const D3DXVECTOR2	m_ButtonTexel[4];		//!< ボタンのテクスチャ座標
	Vertex2D*					m_pButtonVertex;		//!< ボタンを描画するVertex2Dクラス
	int							m_ButtonTextureIndex;	//!< ボタンのテクスチャインデックス
	D3DXVECTOR2					m_ParentUIPos;			//!< 親UIの座標位置

};


#endif
