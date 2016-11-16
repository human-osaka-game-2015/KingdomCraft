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

/**
 * シーンを管理するクラス
 */
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
	/**
	 * SceneManagerの状態
	 */
	enum SceneState
	{
		SCENE_CREATE,	//!< シーンの生成状態
		SCENE_PROC,		//!< シーンの処理状態		
		SCENE_RELEASE	//!< シーンの解放状態
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