#include "SceneManager.h"
#include "Scene//Scene.h"
#include "SceneFactory//SceneFactory.h"
#include "..//..//Library/DX11Manager/DX11Manager.h"

SceneManager::SceneManager(HWND _hwnd) :
m_pScene(NULL),
m_sceneState(SCENE_CREATE),
m_nextSceneID(SceneID::SCENE_TITLE),
m_end(false),
m_hWnd(_hwnd)
{
}


SceneManager::~SceneManager()
{
	// シーンオブジェクトを解放
	if (m_pScene != nullptr)
	{
		delete m_pScene;
		m_pScene = nullptr;
	}
}

void SceneManager::Control()
{
	SceneID currentSceneID;

	// シーン
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

	switch (m_sceneState) // ステップ分け
	{
	case SCENE_CREATE:

		// シーンIDを参照して生成するシーンを変える
		m_pScene = SceneFactory::Instance().CreateScene(currentSceneID);

		// 次のステップへ
		m_sceneState = SCENE_PROC;
		break;
	case SCENE_PROC:
		// newしたシーンのControl関数が呼び出される

		// 今現在のシーンＩＤと違うなら別のシーンに移動する
		if ((m_nextSceneID = m_pScene->Control()) != currentSceneID)
		{
			// 次のステップへ
			m_sceneState = SCENE_RELEASE;
		}
		break;
	case SCENE_RELEASE:
		if (m_pScene != nullptr)
		{
			delete m_pScene;
			m_pScene = nullptr;
		}
		// 次のステップへ
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
	if (!m_pScene == NULL){
		m_pScene->Draw();
	}
}

bool SceneManager::Run()
{
	Control();
	Draw();
	return m_end;
}