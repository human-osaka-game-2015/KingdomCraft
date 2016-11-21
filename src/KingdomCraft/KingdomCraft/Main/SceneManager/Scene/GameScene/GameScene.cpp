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


GameScene::GameScene() :
Scene(SCENE_GAME)
{
	TextureManager::Create(DX11Manager::GetInstance()->GetDevice());
	ShaderManager::Create(DX11Manager::GetInstance()->GetDevice());
	DSoundManager::Create(DX11Manager::GetInstance()->GetWindowHandle());
	FbxFileManager::Create(DX11Manager::GetInstance()->GetDevice(), DX11Manager::GetInstance()->GetDeviceContext());
	FbxFileManager::GetInstance()->Init();
}

GameScene::~GameScene()
{
	FbxFileManager::GetInstance()->Release();
	FbxFileManager::Delete();
	DSoundManager::Destroy();
	ShaderManager::Delete();
	TextureManager::Delete();
}

Scene::SceneID GameScene::Control()
{
	return m_SceneID;
}

void GameScene::Draw()
{

}
