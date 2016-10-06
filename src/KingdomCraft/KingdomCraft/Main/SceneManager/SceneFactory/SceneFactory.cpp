#include "SceneFactory.h"
#include "..//Scene//GameScene//GameScene.h"
#include "..//Scene//TitleScene//TitleScene.h"
#include <Windows.h>
Scene* SceneFactory::CreateScene(SceneID _sceneID)
{
	Scene* pScene = NULL;

	switch (_sceneID)
	{
	case SCENE_LOGO:
		break;
	case SCENE_OPENING:
		break;
	case SCENE_TITLE:
		pScene = new TitleScene();
		break;
	case SCENE_GAME:
		pScene = new GameScene();
		break;
	case SCENE_CONTINUE_GAME:
		pScene = new GameScene();
		break;
	case SCENE_RESULT:
		break;
	case SCENE_ENDING:
		break;
	case FIN:
		break;
	default:
		break;
	}

	return pScene;
}
