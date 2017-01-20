/**
 * @file   HouseCreater.cpp
 * @brief  HouseCreaterクラスの実装
 * @author morimoto
 */
#include "HouseCreater.h"
#include "..\HouseBase\NormalHouse\NormalHouse.h"
#include "FbxFileManager\FbxFileManager.h"
#include "ShaderManager\ShaderManager.h"


HouseCreater::HouseCreater()
{
	FbxFileManager::GetInstance()->LoadFbxModel(
		TEXT("Resource\\Fbx\\GameScene\\house_red.fbx"),
		&m_ModelIndex[HouseManager::NORMAL_HOUSE]);

	ShaderManager::GetInstance()->LoadVertexShader(
		TEXT("Resource\\Effect\\GameScene\\NormalHouse.fx"),
		"VS",
		&m_VertexShaderIndex[HouseManager::NORMAL_HOUSE]);

	ShaderManager::GetInstance()->LoadPixelShader(
		TEXT("Resource\\Effect\\GameScene\\NormalHouse.fx"),
		"PS",
		&m_PixelShaderIndex[HouseManager::NORMAL_HOUSE]);
}

HouseCreater::~HouseCreater()
{
	ShaderManager::GetInstance()->ReleasePixelShader(m_PixelShaderIndex[HouseManager::NORMAL_HOUSE]);
	ShaderManager::GetInstance()->ReleaseVertexShader(m_VertexShaderIndex[HouseManager::NORMAL_HOUSE]);
	FbxFileManager::GetInstance()->ReleaseFbxModel(m_ModelIndex[HouseManager::NORMAL_HOUSE]);
}

void HouseCreater::SetHousePos(const D3DXVECTOR3* _pHousePos)
{
	m_HousePos = *_pHousePos;
}

void HouseCreater::SetHouseAngle(float _houseAngle)
{
	m_HouseAngle = _houseAngle;
}

void HouseCreater::SetHouseType(HouseManager::BUILD_TYPE _buildType)
{
	m_BuildType = _buildType;
}

HouseBase* HouseCreater::HouseCreate()
{
	HouseBase* pHouse = NULL;

	switch (m_BuildType)
	{
	case HouseManager::NORMAL_HOUSE:
		pHouse = new NormalHouse(
			&m_HousePos, 
			m_HouseAngle, 
			m_ModelIndex[HouseManager::NORMAL_HOUSE], 
			m_VertexShaderIndex[HouseManager::NORMAL_HOUSE], 
			m_PixelShaderIndex[HouseManager::NORMAL_HOUSE]);
		break;
	}

	return pHouse;
}

