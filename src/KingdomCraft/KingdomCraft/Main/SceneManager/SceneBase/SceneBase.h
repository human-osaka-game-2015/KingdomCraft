/**
 * @file   SceneBase.h
 * @brief  SceneBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef SCENEBASE_H
#define SCENEBASE_H

/**
 * シーンの基底クラス
 */
class SceneBase
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
		FIN					//!< シーン終了ID
	};

	/**
	 * SceneBaseクラスのコンストラクタ
	 * @param[in] _sceneID 作成したSceneBaseクラスのID
	 */
	SceneBase(SceneID _sceneID);

	/**
	 * SceneBaseクラスのデストラクタ
	 */
	virtual ~SceneBase();

	/**
	 * SceneBaseの制御関数
	 * @return 遷移先のシーンID
	 */
	virtual SceneID Control() = 0;

	/**
	 * SceneBaseの描画関数
	 */
	virtual void Draw() = 0;

	/**
	 * シーンIDの取得関数
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
