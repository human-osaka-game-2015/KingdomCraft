/**
 * @file   HouseCreater.h
 * @brief  HouseCreaterクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSECREATER_H
#define HOUSECREATER_H
#include <D3DX11.h>
#include <D3DX10.h>
#include "..\HouseManager.h"

class HouseBase;

class HouseCreater
{
public:
	/**
	 * HouseCreaterクラスのコンストラクタ
	 */
	HouseCreater();

	/**
	 * HouseCreaterクラスのデストラクタ
	 */
	~HouseCreater();

	/**
	 * 生成する建物の座標を設定する関数
	 * @param[in] _pHousePos 生成する建物の座標
	 */
	void SetHousePos(const D3DXVECTOR3* _pHousePos);

	/**
	 * 生成する建物の角度を設定する関数
	 * @param[in] _houseAngle 生成する建物の角度
	 */
	void SetHouseAngle(float _houseAngle);

	/**
	 * 生成する建物の種類を設定する関数
	 * @param[in] _buildType 生成する建物の種類
	 */
	void SetHouseType(HouseManager::BUILD_TYPE _buildType);

	/**
	 * 建物を生成する関数
	 * @return 生成したHouseBaseクラスのポインタ
	 */
	HouseBase* HouseCreate();

private:
	D3DXVECTOR3					m_HousePos;		//!< 生成する建物の座標
	float						m_HouseAngle;	//!< 生成する建物の角度 
	HouseManager::BUILD_TYPE	m_BuildType;	//!< 生成する建物の種類

	int		m_ModelIndex[HouseManager::BUILD_TYPE_MAX];		//!< 建物のモデルインデックス
	int		m_VertexShaderIndex[HouseManager::BUILD_TYPE_MAX];	//!< 建物の頂点シェーダーインデックス
	int		m_PixelShaderIndex[HouseManager::BUILD_TYPE_MAX];	//!< 建物のピクセルシェーダーインデックス

};


#endif
