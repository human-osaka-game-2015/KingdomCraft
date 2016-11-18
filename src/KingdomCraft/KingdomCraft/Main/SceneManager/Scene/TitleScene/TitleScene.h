/**
 * @file TitleScene.h
 * @brief TitleSceneクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLESCENE_H
#define TITLESCENE_H

#include "..\Scene.h"

class TitleMenu;
class TitleBackground;
class TitleLogo;

/**
 * タイトルシーンを管理するクラス
 */
class TitleScene : public Scene
{
public:
	/**
	 * TitleSceneのコンストラクタ
	 */
	TitleScene();

	/**
	 * TitleSceneのデストラクタ
	 */
	virtual ~TitleScene();

	/**
	 * TitleSceneの制御関数
	 * @return 遷移先のシーンID
	 */
	virtual SceneID Control();

	/**
	 * TitleSceneの描画関数
	 */
	virtual void Draw();

private:
	TitleScene(const TitleScene&);
	void operator=(const TitleScene&);

	TitleBackground*	m_pTitleBackground;
	TitleLogo*			m_pTitleLogo;
	TitleMenu*			m_pTitleMenu;

};

#endif
