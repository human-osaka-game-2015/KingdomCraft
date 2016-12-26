/**
 * @file   KingdomParameterUI.h
 * @brief  KingdomParameterUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMPARAMETER_H
#define KINGDOMPARAMETER_H
#include "Vertex\Vertex.h"

/**
 * 国のパラメータUIを管理するクラス
 */
class KingdomParameterUI
{
public:
	/**
	 * 国のパラメータ構造体
	 */
	struct KINGDOM_PARAMETER
	{
		KINGDOM_PARAMETER() :
			Politics(0),
			CombatPower(0),
			MagicPower(0),
			Industry(0)
		{
		}

		KINGDOM_PARAMETER(int _politics, int _industry, int _combatPower, int _magicPower) :
			Politics(_politics),
			CombatPower(_combatPower),
			MagicPower(_magicPower),
			Industry(_industry)
		{
		}

		int Politics;
		int CombatPower;
		int MagicPower;
		int Industry;
	};

	/**
	 * KingdomParameterUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	KingdomParameterUI(const D3DXVECTOR2* _pParentUIPos);

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

	static const D3DXVECTOR2	m_ParameterUIPos;			//!< パラメータUIを表示する座標
	static const Vertex::VERTEX	m_ParameterUIVertexData[4];	//!< パラメータUIの頂点データの初期値

	Vertex*						m_pParameterUIVertex;
	int							m_ParameterUITextureIndex;
	D3DXVECTOR2					m_ParentUIPos;
	KINGDOM_PARAMETER			m_Parameter;

};


#endif
