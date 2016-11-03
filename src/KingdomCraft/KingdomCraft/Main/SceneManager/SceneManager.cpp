#include "SceneManager.h"
#include "Scene//Scene.h"
#include "SceneFactory//SceneFactory.h"

SceneManager::SceneManager(HWND _hwnd) :
m_pScene(NULL),
m_pSceneFactory(new SceneFactory()),
m_sceneState(SCENE_CREATE),
m_nextSceneID(SceneID::SCENE_TITLE),
m_end(false),
m_hWnd(_hwnd)
{
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	delete m_pSceneFactory;
}

void SceneManager::Control()
{
	SceneID currentSceneID;

	if (m_pScene == NULL)
	{
		currentSceneID = m_nextSceneID;
		if (currentSceneID == FIN)
		{
			m_end = true;
			return;
		}
	}
	else
	{
		currentSceneID = m_pScene->GetSceneID();
	}

	switch (m_sceneState) 
	{
	case SCENE_CREATE:
		m_pScene = m_pSceneFactory->CreateScene(currentSceneID);
		m_sceneState = SCENE_PROC;
		break;
	case SCENE_PROC:
		m_nextSceneID = m_pScene->Control();
		if (m_nextSceneID != currentSceneID)
		{
			m_sceneState = SCENE_RELEASE;
		}
		break;
	case SCENE_RELEASE:
		delete m_pScene;
		m_pScene = NULL;
		m_sceneState = SCENE_CREATE;
		break;
	}
}

void SceneManager::Draw()
{
	if (m_sceneState != SCENE_PROC)
	{
		return;
	}
	if (!m_pScene == NULL)
	{
		m_pScene->Draw();
	}
}

bool SceneManager::Run()
{
	Control();
	Draw();
	return m_end;
}