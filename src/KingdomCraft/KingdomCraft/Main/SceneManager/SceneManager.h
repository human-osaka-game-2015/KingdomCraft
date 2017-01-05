/**
 * @file   SceneManager.h
 * @brief  SceneManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H
#include <Windows.h>
#include "SceneBase\SceneBase.h"

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
	enum State
	{
		SCENE_CREATE,	//!< シーンの生成状態
		SCENE_PROC,		//!< シーンの処理状態		
		SCENE_RELEASE	//!< シーンの解放状態
	};

	/**
	 * SceneManagerクラスの制御関数
	 */
	void Control();

	/**
	 * SceneManagerクラスの描画関数
	 */
	void Draw();

	SceneBase*			m_pScene;
	State			m_State;
	SceneBase::SceneID	m_NextSceneID;
	HWND			m_hWnd;
	bool			m_IsGameEnd;

};


#endif
