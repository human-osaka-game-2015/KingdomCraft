#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <Windows.h>

enum SceneID;
class Scene;
class SceneFactory;

class SceneManager
{
public:
	SceneManager(HWND _hwnd);
	~SceneManager();
	bool Run();

private:
	enum SceneState
	{
		/// 生成
		SCENE_CREATE,
		/// 処理中
		SCENE_PROC,
		/// 解放
		SCENE_RELEASE
	};

	void		  Control();
	void		  Draw();
	SceneFactory* m_pSceneFactory;
	Scene*		  m_pScene;
	SceneState    m_sceneState;
	SceneID		  m_nextSceneID;
	bool		  m_end;
	HWND		  m_hWnd;

};
#endif