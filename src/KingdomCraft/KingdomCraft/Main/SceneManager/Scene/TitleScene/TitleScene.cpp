/**
 * @file TitleScene.cpp
 * @brief TitleSceneクラス実装
 * @author morimoto
 */
#include "TitleScene.h"
#include "TitleMenu\TitleMenu.h"
#include "TitleBackground\TitleBackground.h"
#include "TitleLogo\TitleLogo.h"
#include "DX11Manager\DX11Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "TextureManager\TextureManager.h"
#include "ShaderManager\ShaderManager.h"
#include "FbxFileManager\FbxFileManager.h"


TitleScene::TitleScene() :
Scene(SceneID::SCENE_TITLE),
m_pTitleBackground(new TitleBackground()),
m_pTitleLogo(new TitleLogo()),
m_pTitleMenu(new TitleMenu())
{
}

TitleScene::~TitleScene()
{
	delete m_pTitleMenu;
	delete m_pTitleLogo;
	delete m_pTitleBackground;
	TextureManager::GetInstance()->ClearBuffer();
	ShaderManager::GetInstance()->ClearPixelShaderBuffer();
	ShaderManager::GetInstance()->ClearVertexShaderBuffer();
	FbxFileManager::GetInstance()->ClearBuffer();
}

SceneID TitleScene::Control()
{
	InputDeviceManager::GetInstance()->MouseUpdate();

	SceneID NextSceneID = m_sceneID;

	m_pTitleBackground->Control();
	m_pTitleLogo->Control();

	switch (m_pTitleMenu->Control())
	{
	case TitleMenu::START_ID:
		NextSceneID = SCENE_GAME;
		break;
	case TitleMenu::CONTINUE_ID:
		NextSceneID = SCENE_CONTINUE_GAME;
		break;
	case TitleMenu::NONE_ID:

		break;
	}

	return NextSceneID;
}

void TitleScene::Draw()
{
	DX11Manager::GetInstance()->BeginScene();

	m_pTitleBackground->Draw();
	m_pTitleLogo->Draw();
	m_pTitleMenu->Draw();

	DX11Manager::GetInstance()->EndScene();
}
