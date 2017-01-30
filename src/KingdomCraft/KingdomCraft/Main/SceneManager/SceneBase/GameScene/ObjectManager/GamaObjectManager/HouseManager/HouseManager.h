/**
 * @file   HouseManager.h
 * @brief  HouseManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H
#include <vector>
#include "InputDeviceManager\InputDeviceManager.h"

class HouseCreater;
class HouseBuildWindowEventListener;
class HouseBase;

/**
 * 建物を管理するクラス
 */
class HouseManager
{
public:
	/**
	 * 建設する建物の種類
	 */
	enum BUILD_TYPE
	{
		NORMAL_HOUSE,
		BUILD_TYPE_MAX
	};

	/**
	 * HouseManagerクラスのコンストラクタ
	 */
	HouseManager();

	/**
	 * HouseManagerクラスのデストラクタ
	 */
	~HouseManager();
	
	/**
	 * HouseManagerクラスの制御関数
	 */
	void Control();
	
	/**
	 * HouseManagerクラスの描画関数
	 */
	void Draw();

private:
	/**
	 * HouseManagerの状態列挙子
	 */
	enum STATE
	{
		NONE,
		BUILD_STATE,
		STATE_MAX
	};

	HouseManager(const HouseManager&);
	void operator=(const HouseManager&);

	/**
	 * マウスの状態をチェックする関数
	 */
	void MouseCheck();

	/**
	 * 状態の制御関数
	 */
	void StateControl();

	/**
	 * 建物建設の制御関数
	 */
	void BuildControl();

	HouseCreater*					m_pHouseCreater;
	HouseBuildWindowEventListener*	m_pEventListener;
	STATE							m_State;
	BUILD_TYPE						m_BuildType;
	MouseDevice::MOUSESTATE			m_MouseState;
	std::vector<HouseBase*>			m_pHouse;

};


#endif
