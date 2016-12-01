/**
 * @file   ObjectManager.h
 * @brief  ObjectManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef OBJECTMANAGER_H
#define OBJECTMANAGER_H

class UIManager;
class GameObjectManager;

/**
 * ゲームのオブジェクトを管理するクラス
 */
class ObjectManager
{
public:
	/**
	 * ObjectManagerのコンストラクタ
	 */
	ObjectManager();

	/**
	 * ObjectManagerのデストラクタ
	 */
	~ObjectManager();

	/**
	 * ObjectManagerの制御関数
	 */
	void Control();

	/**
	 * ObjectManagerの描画関数
	 */
	void Draw();

private:
	ObjectManager(const ObjectManager&);
	void operator=(const ObjectManager&);

	GameObjectManager* m_pGameObjectManager;
	UIManager*		   m_pUIManager;

};


#endif
