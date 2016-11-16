﻿/**
 * @file   TitleScene.h
 * @brief  TitleSceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef TITLESCENE_H
#define TITLESCENE_H
#include "..//Scene.h"

/**
 * @brife　タイトルシーンを管理するクラス
 */
class TitleScene : public Scene
{
public:
	/**
	 * TitleSceneのコンストラクタ
	 */
	TitleScene();

	/**
	 * TitleSceneのデストラクタ
	 */
	virtual ~TitleScene();

	/**
	 * TitleSceneの制御関数
	 * @return 遷移先のシーンID
	 */
	virtual SceneID Control();

	/**
	 * TitleSceneの描画関数
	 */
	virtual void Draw();

};

#endif