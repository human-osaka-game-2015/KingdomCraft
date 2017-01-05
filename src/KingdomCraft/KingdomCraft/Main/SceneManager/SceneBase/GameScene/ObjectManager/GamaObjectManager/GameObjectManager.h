/**
 * @file   GameObjectManager.h
 * @brief  GameObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

class MainCamera;
class EnemyManager;
class FieldManager;
class HouseManager;
class HumanManager;
class RoadManager;
class GameTimeManager;

/**
 * ゲーム内のオブジェクトを管理するクラス
 */
class GameObjectManager
{
public:
	/**
	 * GameObjectManagerクラスのコンストラクタ
	 */
	GameObjectManager();

	/**
	 * GameObjectManagerクラスのデストラクタ
	 */
	~GameObjectManager();

	/**
	 * GameObjectManagerクラスの制御関数
	 */
	void Control();

	/**
	 * GameObjectManagerクラスの描画関数
	 */
	void Draw();

private:
	GameObjectManager(const GameObjectManager&);
	void operator=(const GameObjectManager&);

	MainCamera*			m_pMainCamera;
	EnemyManager*		m_pEnemyManager;
	FieldManager*		m_pFieldManager;
	HouseManager*		m_pHouseManager;
	HumanManager*		m_pHumanManager;
	RoadManager*		m_pRoadManager;
	GameTimeManager*	m_pGameTimeManager;

};


#endif
