/**
 * @file   GameObjectManager.h
 * @brief  GameObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEOBJECTMANAGER_H
#define GAMEOBJECTMANAGER_H

/**
 * ゲーム内のオブジェクトを管理するクラス
 */
class GameObjectManager
{
public:
	/**
	 * GameObjectManagerのコンストラクタ
	 */
	GameObjectManager();

	/**
	 * GameObjectManagerのデストラクタ
	 */
	~GameObjectManager();

	/**
	 * GameObjectManagerの制御関数
	 */
	void Control();

	/**
	 * GameObjectManagerの描画関数
	 */
	void Draw();

private:
	GameObjectManager(const GameObjectManager&);
	void operator=(const GameObjectManager&);

};


#endif
