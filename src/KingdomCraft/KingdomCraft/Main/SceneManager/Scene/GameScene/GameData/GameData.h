/**
 * @file GameData.h
 * @brief GameDataクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMEDATA_H
#define GAMEDATA_H
#include <Windows.h>

/**
 * GameScene内のデータを管理するクラス
 */
class GameData
{
public:
	/**
	 * インスタンスを生成する関数
	 */
	static void Create()
	{
		if (m_pGameData == NULL)
		{
			m_pGameData = new GameData();
		}
	}

	/**
	 * インスタンスを取得する関数
	 * @return GameDataクラスのインスタンス
	 */
	static GameData* GetInstance()
	{
		return m_pGameData;
	}

	/**
	 * インスタンスを破棄する関数
	 */
	static void Delete()
	{
		delete m_pGameData;
		m_pGameData = NULL;
	}

private:
	/**
	 * GameDataクラスのコンストラクタ
	 */
	GameData();

	/**
	 * GameDataクラスのデストラクタ
	 */
	~GameData();

	static GameData* m_pGameData;

};


#endif
