/**
 * @file GameDataManager.h
 * @brief GameDataManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H
#include <Windows.h>
#include "..\ObjectManager\GamaObjectManager\GameTimeManager\GameTimeManager.h"
#include "..\ObjectManager\GamaObjectManager\Kingdom\Kingdom.h"

/**
 * GameScene内のデータを管理するクラス
 */
class GameDataManager
{
public:
	/**
	 * インスタンスを生成する関数
	 */
	inline static void Create()
	{
		if (m_pGameDataManager == NULL)
		{
			m_pGameDataManager = new GameDataManager();
		}
	}

	/**
	 * インスタンスを取得する関数
	 * @return GameDataManagerクラスのインスタンス
	 */
	inline static GameDataManager* GetInstance()
	{
		return m_pGameDataManager;
	}

	/**
	 * インスタンスを破棄する関数
	 */
	inline static void Delete()
	{
		delete m_pGameDataManager;
		m_pGameDataManager = NULL;
	}

	/**
	 * ゲーム内時間を取得する関数
	 * @return ゲーム内時間が格納された構造体
	 */
	inline GameTimeManager::GAMETIME GetGameTime()
	{
		return m_GameTime;
	}

	/**
	 * ゲーム内時間をセットする関数
	 * @param[in] _gameTime 設定するゲーム内時間
	 */
	inline void SetGameTime(GameTimeManager::GAMETIME _gameTime)
	{
		m_GameTime = _gameTime;
	}

	/**
	 * ゲーム内時間の速度を取得する関数
	 * @return ゲーム内時間の速度
	 */
	inline GameTimeManager::SPEED_STATE GetSpeedState()
	{
		return m_SpeedState;
	}
	
	/**
	 * ゲーム内時間の速度をセットする関数
	 * @param[in] _speedState ゲーム内時間の速度
	 */
	inline void SetSpeedState(GameTimeManager::SPEED_STATE _speedState)
	{
		m_SpeedState = _speedState;
	}

	/**
	 * 王国のデータを取得する関数
	 * @return 王国のデータ
	 */
	inline Kingdom::KINGDOMDATA GetKingdomData()
	{
		return m_KingdomData;
	}

	/**
	 * 王国のデータをセットする関数
	 * @param[in] _kingdomData 王国のデータ
	 */
	inline void SetKingdomData(Kingdom::KINGDOMDATA _kingdomData)
	{
		m_KingdomData = _kingdomData;
	}

private:
	/**
	 * GameDataManagerクラスのコンストラクタ
	 */
	GameDataManager();

	/**
	 * GameDataManagerクラスのデストラクタ
	 */
	~GameDataManager();

	static GameDataManager* m_pGameDataManager;

	GameTimeManager::GAMETIME		m_GameTime;		//!< ゲーム内時間を格納する変数
	GameTimeManager::SPEED_STATE	m_SpeedState;	//!< ゲーム内時間の速度
	Kingdom::KINGDOMDATA			m_KingdomData;	//!< 王国のデータ

};


#endif
