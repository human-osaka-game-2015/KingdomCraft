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
#include "GameDataManager\GameDataManager.h"
#include "EventManager\EventManager.h"
#include "ObjectManager\ObjectManager.h"


GameScene::GameScene() :
SceneBase(SCENE_GAME),
m_pObjectManager(NULL)
{
	TextureManager::Create(DX11Manager::GetInstance()->GetDevice());

	ShaderManager::Create(DX11Manager::GetInstance()->GetDevice());

	DSoundManager::Create();
	DSoundManager::GetInstance()->Init(DX11Manager::GetInstance()->GetWindowHandle());
	DSoundManager::GetInstance()->LoadSound("Resource\\Sounds\\TitleScene\\TitleSceneBGM.wav", &m_GameSceneBGMIndex);
	DSoundManager::GetInstance()->SoundOperation(m_GameSceneBGMIndex, DSoundManager::SOUND_LOOP);


	FbxFileManager::Create(DX11Manager::GetInstance()->GetDevice(), DX11Manager::GetInstance()->GetDeviceContext());
	FbxFileManager::GetInstance()->Init();

	GameDataManager::Create();
	EventManager::Create();
	m_pObjectManager = new ObjectManager();
}

GameScene::~GameScene()
{
	delete m_pObjectManager;
	EventManager::Delete();
	GameDataManager::Delete();

	FbxFileManager::GetInstance()->Release();
	FbxFileManager::Delete();

	DSoundManager::GetInstance()->SoundOperation(m_GameSceneBGMIndex, DSoundManager::SOUND_STOP);
	DSoundManager::GetInstance()->ReleaseSound(m_GameSceneBGMIndex);
	DSoundManager::GetInstance()->Release();
	DSoundManager::Delete();

	ShaderManager::Delete();

	TextureManager::Delete();
}

SceneBase::SceneID GameScene::Control()
{
	InputDeviceManager::GetInstance()->MouseUpdate();
	KeyUpdate();
	m_pObjectManager->Control();

	return m_SceneID;
}

void GameScene::Draw()
{
	DX11Manager::GetInstance()->BeginScene();

	m_pObjectManager->Draw();

	DX11Manager::GetInstance()->EndScene();
}

void GameScene::KeyUpdate()
{
	InputDeviceManager::GetInstance()->KeyUpdate();
	InputDeviceManager::GetInstance()->KeyCheck(DIK_W);
	InputDeviceManager::GetInstance()->KeyCheck(DIK_A);
	InputDeviceManager::GetInstance()->KeyCheck(DIK_S);
	InputDeviceManager::GetInstance()->KeyCheck(DIK_D);
	InputDeviceManager::GetInstance()->KeyCheck(DIK_F);
}
