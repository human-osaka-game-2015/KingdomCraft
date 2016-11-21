/**
 * @file   Scene.h
 * @brief  Sceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENE_H
#define SCENE_H
#include<Windows.h>

/**
 * シーンクラス
 */
class Scene
{
public:
	/**
	 * シーンのID
	 */
	enum SceneID
	{
		SCENE_LOGO,			//!< ロゴシーンID
		SCENE_OPENING,		//!< オープニングシーンID
		SCENE_TITLE,		//!< タイトルシーンID
		SCENE_GAME,			//!< ゲームシーンID
		SCENE_CONTINUE_GAME,//!< 続きからゲームを始めるときのシーンID
		SCENE_RESULT,		//!< リザルトシーンID
		SCENE_ENDING,		//!< エンディングシーンID
		FIN					//!< シーン終了のID
	};

	/**
	 * Sceneクラスのコンストラクタ
	 * @param[in] _sceneID 作成したSceneのID
	 * @param[in] _hWnd Sceneを動作させるウィンドウのハンドル
	 *
	 */
	Scene(SceneID _sceneID);

	/**
	 * Sceneクラスのデストラクタ
	 */
	virtual ~Scene();

	/**
	 * Sceneの制御関数
	 * @return 遷移先のシーンID
	 */
	virtual SceneID Control() = 0;

	/**
	 * Sceneの描画関数
	 */
	virtual void Draw() = 0;

	/**
	 * Sceneクラスのデストラクタ
	 * @return シーンのID
	 */
	inline SceneID GetSceneID()
	{ 
		return m_SceneID;
	}

protected:
	SceneID m_SceneID;

};

#endif
