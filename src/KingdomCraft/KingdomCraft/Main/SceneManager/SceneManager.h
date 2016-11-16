/**
 * @file   SceneManager.h
 * @brief  SceneManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <Windows.h>

class Scene;
class SceneFactory;
enum SceneID;

class SceneManager
{
public:
	/**
	 * SceneManagerのコンストラクタ
	 * @param[in] _hwnd ゲームを動作させるウィンドウのハンドル
	 */
	SceneManager(HWND _hwnd);
	
	/**
	 * SceneManagerのデストラクタ
	 */
	~SceneManager();

	/** 
	 * ゲームの制御関数
	 * @return ゲームが終了したらtrue
	 */
	bool Run();

private:
	enum SceneState
	{
		//! シーンの生成状態
		SCENE_CREATE,

		//! シーンの処理状態
		SCENE_PROC,

		//! シーンの解放状態
		SCENE_RELEASE
	};

	void Control();
	void Draw();

	SceneFactory* m_pSceneFactory;
	Scene*		  m_pScene;
	SceneState    m_sceneState;
	SceneID		  m_nextSceneID;
	HWND		  m_hWnd;
	bool		  m_end;

};
#endif