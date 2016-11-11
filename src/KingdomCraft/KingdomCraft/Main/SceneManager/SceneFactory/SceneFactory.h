/**
 * @file   SceneFactory.h
 * @brief  SceneFactoryクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H

class Scene;
enum SceneID;

/**
 * Sceneの生成管理するクラス
 */
class SceneFactory
{
public:
	/**
	 * SceneFactoryのコンストラクタ
	 */
	SceneFactory()
	{
	}
	
	/**
	 * SceneFactoryのデストラクタ
	 */
	~SceneFactory()
	{
	}

	/**
	 * シーンクラスの生成
	 * @param _sceneID 生成するクラスのシーンID
	 * @return シーンクラスのインスタンス
	 */
	Scene* CreateScene(SceneID _sceneID);

};
#endif