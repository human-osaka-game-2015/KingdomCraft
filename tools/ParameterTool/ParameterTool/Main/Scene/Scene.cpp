#include "Scene.h"
#include "FieldManager\FieldManager.h"
#include "FieldMessenger\FieldMessenger.h"
#include "HouseManager\HouseManager.h"
#include "DX9Manager\DX9Manager.h"
#include "DebugFont\DebugFont.h"
#include "InputDeviceManager\InputDeviceManager.h"


Scene::Scene(HWND _hWnd, HINSTANCE _hInst) :
m_hWnd(_hWnd),
m_hInstance(_hInst)
{
	DX9Manager::Create();
	DX9Manager::GetInstance()->Init(m_hWnd);

	InputDeviceManager::Create();
	InputDeviceManager::GetInstance()->Init(m_hWnd);
	InputDeviceManager::GetInstance()->CreateKeyDevice();
	InputDeviceManager::GetInstance()->CreateMouseDevice();

	DebugFont::Create();
	DebugFont::GetInstance()->Init(DX9Manager::GetInstance()->GetDevice(), 16);

	m_pFieldManager = new FieldManager();
	m_pFieldMessenger = new FieldMessenger(m_pFieldManager);
	m_pHouseManager = new HouseManager(m_pFieldMessenger, m_hInstance);
}

Scene::~Scene()
{
	delete m_pHouseManager;
	delete m_pFieldMessenger;
	delete m_pFieldManager;

	DebugFont::GetInstance()->Release();
	DebugFont::Delete();

	InputDeviceManager::GetInstance()->Release();
	InputDeviceManager::Delete();

	DX9Manager::GetInstance()->Release();
	DX9Manager::Delete();
}

bool Scene::Run()
{
	bool isEnd = Control();
	Draw();

	return isEnd;
}

bool Scene::Control()
{
	InputDeviceManager::GetInstance()->MouseUpdate();
	InputDeviceManager::GetInstance()->KeyUpdate();
	InputDeviceManager::GetInstance()->KeyCheck(DIK_Z);
	InputDeviceManager::GetInstance()->KeyCheck(DIK_X);
	InputDeviceManager::GetInstance()->KeyCheck(DIK_C);
	m_pFieldManager->Control();
	m_pHouseManager->Control();

	return false;
}

void Scene::Draw()
{
	DX9Manager::GetInstance()->GetInstance()->GetDevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_STENCIL | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 120, 120), 1.0f, 0);
	DX9Manager::GetInstance()->GetInstance()->GetDevice()->BeginScene();
	m_pFieldManager->Draw();
	m_pHouseManager->Draw();
	DX9Manager::GetInstance()->GetInstance()->GetDevice()->EndScene();
	DX9Manager::GetInstance()->GetInstance()->GetDevice()->Present(NULL, NULL, NULL, NULL);
}
