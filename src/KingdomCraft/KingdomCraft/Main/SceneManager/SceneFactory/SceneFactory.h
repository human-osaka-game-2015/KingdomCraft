#ifndef SCENEFACTORY_H
#define SCENEFACTORY_H
class Scene;
enum SceneID;
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