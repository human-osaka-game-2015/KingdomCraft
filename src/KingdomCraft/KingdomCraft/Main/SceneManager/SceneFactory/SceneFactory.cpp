/**
 * @file   SceneFactory.cpp
 * @brief  SceneFactoryクラスの実装
 * @author kotani
 */
#include "SceneFactory.h"
#include "..\Scene\GameScene\GameScene.h"
#include "..\Scene\TitleScene\TitleScene.h"
#include <Windows.h>


SceneFactory::SceneFactory()
{

}

SceneFactory::~SceneFactory()
{

}

Scene* SceneFactory::CreateScene(Scene::SceneID _sceneID)
{
	Scene* pScene = NULL;

	switch (_sceneID)
	{
	case Scene::SCENE_LOGO:
		break;
	case Scene::SCENE_OPENING:
		break;
	case Scene::SCENE_TITLE:
		pScene = new TitleScene();
		break;
	case Scene::SCENE_GAME:
		pScene = new GameScene();
		break;
	case Scene::SCENE_CONTINUE_GAME:
		pScene = new GameScene();
		break;
	case Scene::SCENE_RESULT:
		break;
	case Scene::SCENE_ENDING:
		break;
	case Scene::FIN:
		break;
	default:
		break;
	}

	return pScene;
}
