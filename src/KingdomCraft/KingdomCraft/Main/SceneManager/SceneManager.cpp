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
m_sceneState(SCENE_CREATE),
m_nextSceneID(SceneID::SCENE_TITLE),
m_end(false),
m_hWnd(_hwnd)
{
	DX11Manager::Create();
	DX11Manager::GetInstance()->Init(m_hWnd);

	InputDeviceManager::Create();
	InputDeviceManager::GetInstance()->Init(m_hWnd);
	InputDeviceManager::GetInstance()->CreateKeyDevice();
	InputDeviceManager::GetInstance()->CreateMouseDevice();

	TextureManager::Create(DX11Manager::GetInstance()->GetDevice());

	ShaderManager::Create(DX11Manager::GetInstance()->GetDevice());

	DSoundManager::Create(m_hWnd);

	FbxFileManager::Create(DX11Manager::GetInstance()->GetDevice(), DX11Manager::GetInstance()->GetDeviceContext());
	FbxFileManager::GetInstance()->Init();

	m_pSceneFactory = new SceneFactory();
}

SceneManager::~SceneManager()
{
	delete m_pScene;
	delete m_pSceneFactory;

	FbxFileManager::GetInstance()->Release();
	FbxFileManager::Delete();

	DSoundManager::Destroy();
	
	ShaderManager::Delete();

	TextureManager::Delete();

	InputDeviceManager::GetInstance()->Release();
	InputDeviceManager::Delete();

	DX11Manager::GetInstance()->Release();
	DX11Manager::Delete();
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