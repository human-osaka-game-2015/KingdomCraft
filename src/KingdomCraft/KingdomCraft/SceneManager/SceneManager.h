#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
class Scene;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();

private:
	Scene* m_pScene;
	/// シーン番号
};
#endif