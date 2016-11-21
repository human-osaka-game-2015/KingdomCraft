/**
 * @file   SceneManager.cpp
 * @brief  SceneManagerクラスの実装
 * @author kotani
 */
#include "SceneManager.h"
#include "Scene\Scene.h"
#include "SceneFactory\SceneFactory.h"
#include "DX11Manager\DX11Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "TextureManager\TextureManager.h"
#include "ShaderManager\ShaderManager.h"
#include "DSoundManager\DSoundManager.h"
#include "FbxFileManager\FbxFileManager.h"


SceneManager::SceneManager(HWND _hwnd) :
m_pScene(NULL),
m_State(SCENE_CREATE),
m_NextSceneID(Scene::SCENE_TITLE),
m_hWnd(_hwnd),
m_IsGameEnd(false)
{
	DX11Manager::Create();
	DX11Manager::GetInstance()->Init(m_hWnd);
	InputDeviceManager::Create();
	InputDeviceManager::GetInstance()->Init(m_hWnd);
	InputDeviceManager::GetInstance()->CreateKeyDevice();
	InputDeviceManager::GetInstance()->CreateMouseDevice();
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	InputDeviceManager::GetInstance()->Release();
	InputDeviceManager::Delete();
	DX11Manager::GetInstance()->Release();
	DX11Manager::Delete();
}

bool SceneManager::Run()
{
	Control();
	Draw();

	return m_IsGameEnd;
}

void SceneManager::Control()
{
	Scene::SceneID CurrentSceneID;

	switch (m_State)
	{
	case SCENE_CREATE:
		if (m_NextSceneID == Scene::FIN)
		{
			m_IsGameEnd = true;
			return;
		}
		m_pScene = SceneFactory::CreateScene(m_NextSceneID);
		m_State = SCENE_PROC;
		break;
	case SCENE_PROC:
		CurrentSceneID = m_pScene->GetSceneID();
		m_NextSceneID = m_pScene->Control();
		if (m_NextSceneID != CurrentSceneID)
		{
			m_State = SCENE_RELEASE;
		}
		break;
	case SCENE_RELEASE:
		delete m_pScene;
		m_pScene = NULL;
		m_State = SCENE_CREATE;
		break;
	}
}

void SceneManager::Draw()
{
	if (m_State == SCENE_PROC)
	{
		m_pScene->Draw();
	}
}

