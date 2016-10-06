#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H
#include "..//..//..//stdafx.h"
class Scene;

class SceneFactory
{
public:
	static SceneFactory& Instance()
	{
		static SceneFactory instance;
		return instance;
	}
	/// シーンクラスの生成
	/**
	* @param _sceneID 生成するクラスのシーンID
	* @return シーンクラスのインスタンス
	*/
	Scene* CreateScene(SceneID _sceneID);

	~SceneFactory() {}
private:
	SceneFactory(){}
};
#endif