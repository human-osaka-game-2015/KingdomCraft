/**
 * @file   GameScene.h
 * @brief  GameSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "..\Scene.h"

/**
 * ゲームシーンを管理するクラス
 */
class GameScene : public Scene
{
public:
	/**
	 * GameSceneのコンストラクタ
	 */
	GameScene();

	/**
	 * GameSceneのデストラクタ
	 */
	virtual ~GameScene();

	/**
	 * GameSceneの制御関数
	 * @return シーンの遷移先ID
	 */
	virtual SceneID Control();

	/**
	 * GameSceneの描画関数
	 */
	virtual void Draw();

private:
	GameScene(const GameScene&);
	void operator=(const GameScene&);

};


#endif
