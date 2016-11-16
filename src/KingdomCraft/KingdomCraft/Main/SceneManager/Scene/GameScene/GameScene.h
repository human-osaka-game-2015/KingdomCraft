/**
 * @file   GameScene.h
 * @brief  GameSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMESCENE_H
#define GAMESCENE_H
#include "..//Scene.h"

class GameScene : public Scene
{
public:
	/**
	 * GameSceneのコンストラクタ
	 */
	GameScene();

	/**
	 * GameSceneのコンストラクタ
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

};

#endif