/**
 * @file   HouseBase.h
 * @brief  HouseBaseクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSEBASE_H
#define HOUSEBASE_H
#include <D3DX11.h>
#include <D3DX10.h>

/**
 * 建物の基底クラス
 */
class HouseBase
{
public:
	/**
	 * HouseBaseクラスのコンストラクタ
	 * @param[in] _pHousePos 建物を描画する座標
	 * @param[in] _houseAngle 建物の角度
	 */
	HouseBase(const D3DXVECTOR3* _pHousePos, float _houseAngle);

	/**
	 * HouseBaseクラスのデストラクタ
	 */
	virtual ~HouseBase();

	/**
	 * HouseBaseクラスの制御関数
	 */
	virtual void Control();

	/**
	 * HouseBaseクラスの描画関数
	 */
	virtual void Draw();

protected:
	D3DXVECTOR3 m_HousePos;
	float		m_Angle;

};


#endif
