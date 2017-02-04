/**
 * @file   SelectRightButtonUI.h
 * @brief  SelectRightButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SELECTRIGHTBUTTONUI_H
#define SELECTRIGHTBUTTONUI_H
#include "..\..\..\..\..\ButtonUI\ButtonUI.h"

class SelectRightButtonUI : public ButtonUI
{
public:
	/**
	 * SelectRightButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	SelectRightButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * SelectRightButtonUIクラスのデストラクタ
	 */
	virtual ~SelectRightButtonUI();

	/**
	 * SelectRightButtonUIクラスの制御関数
	 */
	virtual bool Control();

	/**
	 * SelectRightButtonUIクラス描画関数
	 */
	virtual void Draw();

private:
	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ座標
	Vertex2D*					m_pVertex2D;		//!< ボタンを描画するVertex2Dクラス
	int							m_TextureIndex;		//!< ボタンのテクスチャインデックス
	const D3DXVECTOR2*			m_pParentUIPos;

};


#endif