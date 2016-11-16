/**
 * @file   Scene.h
 * @brief  Sceneクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENE_H
#define SCENE_H

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
 * シーンクラス
 */
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