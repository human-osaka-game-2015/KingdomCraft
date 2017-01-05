/**
 * @file   KingdomDemandUI.h
 * @brief  KingdomDemandUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMDEMAND_H
#define KINGDOMDEMAND_H
#include "Vertex2D\Vertex2D.h"

/**
 * 国内の需要UIを管理するクラス
 */
class KingdomDemandUI
{
public:
	/**
	 * KingdomDemandUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	KingdomDemandUI(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * KingdomDemandUIクラスのデストラクタ
	 */
	~KingdomDemandUI();

	/**
	 * KingdomDemandUIクラスの制御関数
	 */
	void Control();

	/**
	 * KingdomDemandUIクラスの描画関数
	 */
	void Draw();

private:
	KingdomDemandUI(const KingdomDemandUI&);
	void operator=(const KingdomDemandUI&);

	D3DXVECTOR2 m_ParentUIPos;	//!< 親UIの座標位置

};


#endif
