/**
 * @file   GameScene.cpp
 * @brief  GameSceneクラスの実装
 * @author kotani
 */
#include "GameScene.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include "ShaderManager\ShaderManager.h"
#include "DSoundManager\DSoundManager.h"
#include "FbxFileManager\FbxFileManager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "ObjectManager\ObjectManager.h"

GameScene::GameScene() :
Scene(SCENE_GAME)
{
	TextureManager::Create(DX11Manager::GetInstance()->GetDevice());

	ShaderManager::Create(DX11Manager::GetInstance()->GetDevice());

	DSoundManager::Create();
	DSoundManager::GetInstance()->Init(DX11Manager::GetInstance()->GetWindowHandle());

	FbxFileManager::Create(DX11Manager::GetInstance()->GetDevice(), DX11Manager::GetInstance()->GetDeviceContext());
	FbxFileManager::GetInstance()->Init();

	m_pObjectManager = new ObjectManager();

}

GameScene::~GameScene()
{
	delete m_pObjectManager;

	FbxFileManager::GetInstance()->Release();
	FbxFileManager::Delete();

	DSoundManager::GetInstance()->Release();
	DSoundManager::Delete();

	ShaderManager::Delete();

	TextureManager::Delete();

}

Scene::SceneID GameScene::Control()
{
	InputDeviceManager::GetInstance()->MouseUpdate();

	m_pObjectManager->Control();
	return m_SceneID;
}

void GameScene::Draw()
{
	DX11Manager::GetInstance()->BeginScene();

	m_pObjectManager->Draw();

	DX11Manager::GetInstance()->EndScene();

}
