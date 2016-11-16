/**
 * @file   Scene.h
 * @brief  Sceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENE_H
#define SCENE_H

enum SceneID
{
	//! ロゴシーンID
	SCENE_LOGO,
	
	//! オープニングシーンID
	SCENE_OPENING,

	//! タイトルシーンID
	SCENE_TITLE,

	//! ゲームシーンID
	SCENE_GAME,

	//! 続きからゲームを始めるときのシーンID
	SCENE_CONTINUE_GAME,

	//! リザルトシーンID
	SCENE_RESULT,

	//! エンディングシーンID
	SCENE_ENDING,

	//! シーン終了のID
	FIN
};

class Scene
{
public:
	/**
	 * Sceneクラスのコンストラクタ
	 * @param[in] _sceneID SceneのID
	 */
	Scene(SceneID _sceneID);

	/**
	 * Sceneクラスのデストラクタ
	 */
	virtual ~Scene();

	/**
	 * Sceneの描画関数
	 */
	virtual void Draw() = 0;

	/**
	 * Sceneの制御関数
	 * @return 遷移先のシーンID
	 */
	virtual SceneID Control() = 0;

	/**
	 * Sceneクラスのデストラクタ
	 * @return シーンのID
	 */
	SceneID GetSceneID()
	{ 
		return m_sceneID; 
	}

protected:
	SceneID m_sceneID;

};
#endif