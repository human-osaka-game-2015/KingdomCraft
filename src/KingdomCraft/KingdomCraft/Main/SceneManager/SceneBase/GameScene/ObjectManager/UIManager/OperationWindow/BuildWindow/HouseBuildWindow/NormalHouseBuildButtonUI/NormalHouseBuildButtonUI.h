/**
 * @file   NormalHouseBuildButtonUI.h
 * @brief  NormalHouseBuildButtonUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef NORMALHOUSEBUILDBUTTONUI_H
#define NORMALHOUSEBUILDBUTTONUI_H
#include "Vertex2D\Vertex2D.h"
#include "..\..\..\..\ButtonUI\ButtonUI.h"

/**
 * 通常の家建設UIボタン 
 */
class NormalHouseBuildButtonUI : public ButtonUI
{
public:
	/**
	 * NormalHouseBuildButtonUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	NormalHouseBuildButtonUI(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);

	/**
	 * NormalHouseBuildButtonUIクラスのデストラクタ
	 */
	virtual ~NormalHouseBuildButtonUI();

	/**
	 * NormalHouseBuildButtonUIクラスの制御関数
	 * @return ボタンが押されたらtrue
	 */
	virtual bool Control();

	/**
	 * NormalHouseBuildButtonUIクラスの描画関数
	 */
	virtual void Draw();

private:
	NormalHouseBuildButtonUI(const NormalHouseBuildButtonUI&);
	void operator=(const NormalHouseBuildButtonUI&);

	static const D3DXVECTOR2	m_DefaultPos;		//!< ボタンの初期座標
	static const D3DXVECTOR2	m_DefaultSize;		//!< ボタンの初期矩形サイズ
	static const D3DXVECTOR2	m_DefaultTexel[4];	//!< ボタンのテクスチャ初期座標
	Vertex2D*					m_pVertex2D;		//!< ボタンを描画するVertex2D
	int							m_TextureIndex;		//!< ボタンのテクスチャインデックス
	const D3DXVECTOR2*			m_pParentUIPos;		//!< 親UIの座標位置


};


#endif
