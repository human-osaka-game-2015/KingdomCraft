#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include "..//..//stdafx.h"
class Scene;
class DX11Manager;
class SceneManager
{
public:
	SceneManager(HWND _hwnd);
	~SceneManager();
	bool Run();
	void Control();
	void Draw();

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

	Scene*		 m_pScene;
	SceneState   m_sceneState;
	SceneID		 m_nextSceneID;
	bool		 m_end; //ゲーム終了フラグ
	/// ウィンドウハンドル
	HWND		 m_hWnd;
	DX11Manager* m_pDX11Manager;
};
#endif