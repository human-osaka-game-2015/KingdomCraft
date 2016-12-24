/**
 * @file   KingdomParameterUI.h
 * @brief  KingdomParameterUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMPARAMETER_H
#define KINGDOMPARAMETER_H
#include "Vertex2D\Vertex2D.h"

/**
 * 国のパラメータUIを管理するクラス
 */
class KingdomParameterUI
{
public:
	/**
	 * KingdomParameterUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	KingdomParameterUI(const D3DXVECTOR2* _pParentPos);

	/**
	 * KingdomParameterUIクラスのデストラクタ
	 */
	~KingdomParameterUI();

	/**
	 * KingdomParameterUIクラスの制御関数
	 */
	void Control();

	/**
	 * KingdomParameterUIクラスの描画関数
	 */
	void Draw();

private:
	KingdomParameterUI(const KingdomParameterUI&);
	void operator=(const KingdomParameterUI&);

	static const D3DXVECTOR2	m_ParameterPos;				//!< パラメータUIを表示する座標
	static const D3DXVECTOR2	m_ParameterSize;			//!< パラメータUIのサイズ
	static const D3DXVECTOR2	m_ParameterTexel[4];		//!< パラメータUIのテクスチャ座標
	Vertex2D*					m_pParameterVertex;			//!< パラメータを表示するVertex2Dクラス
	int							m_ParameterTextureIndex;	//!< パラメータのテクスチャインデックス
	D3DXVECTOR2					m_ParentUIPos;				//!< 親UIの座標位置

};


#endif
