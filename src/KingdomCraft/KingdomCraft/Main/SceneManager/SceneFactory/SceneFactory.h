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
	/// �V�[���N���X�̐���
	/**
	* @param _sceneID ��������N���X�̃V�[��ID
	* @return �V�[���N���X�̃C���X�^���X
	*/
	Scene* CreateScene(SceneID _sceneID);

	~SceneFactory() {}
private:
	SceneFactory(){}
};
#endif