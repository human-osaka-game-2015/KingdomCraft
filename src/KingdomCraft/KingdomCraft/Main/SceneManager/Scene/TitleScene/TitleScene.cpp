/**
 * @file   TitleScene.cpp
 * @brief  TitleSceneクラスの実装
 * @author kotani
 */
#include "TitleScene.h"
#include "..//Scene.h"

TitleScene::TitleScene() :
Scene(SceneID::SCENE_TITLE)
{
}


TitleScene::~TitleScene()
{
}

SceneID TitleScene::Control()
{
	return m_sceneID;
}

void TitleScene::Draw()
{

}