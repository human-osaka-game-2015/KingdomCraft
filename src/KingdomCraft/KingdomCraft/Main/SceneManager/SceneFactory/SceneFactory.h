/**
 * @file   SceneFactory.h
 * @brief  SceneFactoryクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H
#include "..\SceneBase\SceneBase.h"

/**
 * SceneBaseの生成管理するクラス
 */
class SceneFactory
{
public:
	/**
	 * シーンクラスの生成
	 * @param _sceneID 生成するクラスのシーンID
	 * @return シーンクラスのインスタンス
	 */
	static SceneBase* CreateScene(SceneBase::SceneID _sceneID);

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
