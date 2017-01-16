/**
 * @file   HouseDestroyButtonUI.h
 * @brief  HouseDestroyButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSEDESTROYBUTTONUI_H
#define HOUSEDESTROYBUTTONUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\..\ButtonUI\ButtonUI.h"

/**
 * 建物の撤去ボタンを管理するUIクラス
 */
class HouseDestroyButtonUI : public ButtonUI
{
public:
	/**
	 * HouseDestroyButtonUIクラスのコンストラクタ	 
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	HouseDestroyButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * HouseDestroyButtonUIクラスのデストラクタ
	 */
	virtual ~HouseDestroyButtonUI();

	/**
	 * HouseDestroyButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * HouseDestroyButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	HouseDestroyButtonUI(const HouseDestroyButtonUI&);
	void operator=(const HouseDestroyButtonUI&);

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ初期座標
	Vertex2D*					m_pVertex2D;		//!< ボタンを描画するVertex2D
	int							m_TextureIndex;		//!< ボタンのテクスチャインデックス
	const D3DXVECTOR2*			m_pParentUIPos;		//!< 親UIの座標位置

};


#endif
