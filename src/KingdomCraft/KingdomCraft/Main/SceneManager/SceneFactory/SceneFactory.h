/**
 * @file   SceneFactory.h
 * @brief  SceneFactoryクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H
#include "..\Scene\Scene.h"

/**
 * Sceneの生成管理するクラス
 */
class SceneFactory
{
public:
	/**
	 * シーンクラスの生成
	 * @param _sceneID 生成するクラスのシーンID
	 * @return シーンクラスのインスタンス
	 */
	static Scene* CreateScene(Scene::SceneID _sceneID);

private:
	/**
	 * SceneFactoryのコンストラクタ
	 */
	SceneFactory();

	/**
	 * SceneFactoryのデストラクタ
	 */
	~SceneFactory();

};

#endif
