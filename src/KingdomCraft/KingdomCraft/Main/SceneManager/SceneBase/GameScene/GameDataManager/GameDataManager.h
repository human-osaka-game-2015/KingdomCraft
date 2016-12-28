/**
 * @file GameDataManager.h
 * @brief GameDataManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMEDATAMANAGER_H
#define GAMEDATAMANAGER_H
#include <Windows.h>

/**
 * GameScene内のデータを管理するクラス
 */
class GameDataManager
{
public:
	/**
	 * インスタンスを生成する関数
	 */
	static void Create()
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
	static GameDataManager* GetInstance()
	{
		return m_pGameDataManager;
	}

	/**
	 * インスタンスを破棄する関数
	 */
	static void Delete()
	{
		delete m_pGameDataManager;
		m_pGameDataManager = NULL;
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

};


#endif
