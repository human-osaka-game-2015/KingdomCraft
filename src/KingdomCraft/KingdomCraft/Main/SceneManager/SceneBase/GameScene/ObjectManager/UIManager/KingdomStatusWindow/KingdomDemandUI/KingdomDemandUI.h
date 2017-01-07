/**
 * @file   KingdomDemandUI.h
 * @brief  KingdomDemandUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMDEMAND_H
#define KINGDOMDEMAND_H
#include "Vertex\Vertex.h"

/**
 * 国内の需要UIを管理するクラス
 */
class KingdomDemandUI
{
public:
	/**
	 * 国の需要構造体
	 */
	struct KINGDOMDEMAND
	{
		KINGDOMDEMAND(float _house, float _commerce, float _industry) :
			House(_house),
			Commerce(_commerce),
			Industry(_industry)
		{
		}

		KINGDOMDEMAND() :
			House(0),
			Commerce(0),
			Industry(0)
		{
		}

		float House;		//!< 住宅の需要
		float Commerce;		//!< 商業の需要
		float Industry;		//!< 工業の需要
	};

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

	/**
	 * 需要UIのタイトル描画関数
	 */
	void TitleDraw();

	/**
	 * 需要UIのゲージ描画関数
	 */
	void GaugeDraw();

	/**
	 * 需要UIの住宅ゲージの描画関数
	 */
	void HouseGaugeDraw();

	/**
	 * 需要UIの商業ゲージの描画関数
	 */
	void CommerceGaugeDraw();

	/**
	 * 需要UIの工業ゲージの描画関数
	 */
	void IndustryGaugeDraw();


	static const D3DXVECTOR2	m_DefaultTitlePos;				//!< 需要UIのタイトルを表示する初期座標
	static const Vertex::VERTEX	m_DefaultTitleVertexData[4];	//!< 需要UIのタイトルの頂点情報
	static const D3DXVECTOR2	m_DefaultHousePos;				//!< 住宅需要ゲージの初期座標
	static const D3DXVECTOR2	m_DefaultCommercePos;			//!< 商業需要ゲージの初期座標
	static const D3DXVECTOR2	m_DefaultIndustryPos;			//!< 工業需要ゲージの初期座標
	static const Vertex::VERTEX m_DefaultGaugeVertexData[4];	//!< 需要UIのゲージの頂点情報
	static const D3DXCOLOR		m_PlusColor;					//!< 需要がプラス時のゲージ色
	static const D3DXCOLOR		m_MinusColor;					//!< 需要がマイナス時のゲージ色

	Vertex*			m_pTitleVertex;
	Vertex*			m_pGaugeVertex;
	int				m_TitleTextureIndex;
	int				m_GaugeTextureIndex;
	D3DXVECTOR2		m_ParentUIPos;
	KINGDOMDEMAND	m_KingdomDemand;

};


#endif
