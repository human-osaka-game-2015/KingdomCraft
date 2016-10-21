#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H
class Scene;
enum SceneID;
class SceneFactory
{
public:
	SceneFactory(){}
	~SceneFactory(){}

	/**
	* シーンクラスの生成
	* @param _sceneID 生成するクラスのシーンID
	* @return シーンクラスのインスタンス
	*/
	Scene* CreateScene(SceneID _sceneID);
};
#endif