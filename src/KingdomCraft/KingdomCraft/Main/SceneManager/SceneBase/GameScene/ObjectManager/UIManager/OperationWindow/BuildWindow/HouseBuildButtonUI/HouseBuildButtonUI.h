/**
 * @file   HouseBuildButtonUI.h
 * @brief  HouseBuildButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSEBUILDBUTTONUI_H
#define HOUSEBUILDBUTTONUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\..\ButtonUI\ButtonUI.h"

/**
 * 建物の建設ボタンを管理するUIクラス
 */
class HouseBuildButtonUI : public ButtonUI
{
public:
	/**
	 * HouseBuildButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	HouseBuildButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * HouseBuildButtonUIクラスのデストラクタ
	 */
	~HouseBuildButtonUI();

	/**
	 * HouseBuildButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * HouseBuildButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	HouseBuildButtonUI(const HouseBuildButtonUI&);
	void operator=(const HouseBuildButtonUI&);

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ初期座標
	Vertex2D*					m_pVertex2D;		//!< ボタンを描画するVertex2D
	int							m_TextureIndex;		//!< ボタンのテクスチャインデックス
	const D3DXVECTOR2*			m_pParentUIPos;		//!< 親UIの座標位置

};


#endif
