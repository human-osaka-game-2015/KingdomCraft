/**
 * @file   SceneFactory.cpp
 * @brief  SceneFactoryクラスの実装
 * @author kotani
 */
#include "SceneFactory.h"
#include "..\SceneBase\GameScene\GameScene.h"
#include "..\SceneBase\TitleScene\TitleScene.h"
#include <Windows.h>


SceneFactory::SceneFactory()
{
}

SceneFactory::~SceneFactory()
{
}

SceneBase* SceneFactory::CreateScene(SceneBase::SceneID _sceneID)
{
	SceneBase* pScene = NULL;

	switch (_sceneID)
	{
	case SceneBase::SCENE_LOGO:
		break;
	case SceneBase::SCENE_OPENING:
		break;
	case SceneBase::SCENE_TITLE:
		pScene = new TitleScene();
		break;
	case SceneBase::SCENE_GAME:
		pScene = new GameScene();
		break;
	case SceneBase::SCENE_CONTINUE_GAME:
		pScene = new GameScene();
		break;
	case SceneBase::SCENE_RESULT:
		break;
	case SceneBase::SCENE_ENDING:
		break;
	case SceneBase::FIN:
		break;
	default:
		break;
	}

	return pScene;
}
