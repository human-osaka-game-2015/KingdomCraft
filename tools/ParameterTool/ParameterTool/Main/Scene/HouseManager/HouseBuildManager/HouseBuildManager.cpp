#include "HouseBuildManager.h"
#include "..\..\FieldManager\FieldManager.h"
#include "..\..\FieldMessenger\FieldMessenger.h"
#include "DX9Manager\DX9Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "DebugFont\DebugFont.h"

const D3DXVECTOR2 HouseBuildManager::m_BuildBoxPos = D3DXVECTOR2(650, 0);
const D3DXVECTOR2 HouseBuildManager::m_BuildBoxSize = D3DXVECTOR2(256, 128);
const int HouseBuildManager::m_BuilBoxNumX = 2;
const int HouseBuildManager::m_BuilBoxNumY = 5;


HouseBuildManager::HouseBuildManager(FieldMessenger* _pFieldMessenger, HINSTANCE _hInst) :
m_pFieldMessenger(_pFieldMessenger),
m_State(NONE_STATE),
m_hInstance(_hInst),
m_IsSelectBoxIndex(0)
{
	D3DXVECTOR2 BuildBoxPos = m_BuildBoxPos;
	for (int i = 0; i < m_BuilBoxNumY; i++)
	{
		BuildBoxPos.x = m_BuildBoxPos.x;

		for (int i = 0; i < m_BuilBoxNumX; i++)
		{
			m_pHouseBuildBox.push_back(new HouseBuildBox(&BuildBoxPos, &m_BuildBoxSize, m_hInstance));

			BuildBoxPos.x += m_BuildBoxSize.x;
		}
		
		BuildBoxPos.y += m_BuildBoxSize.y;
	}
}

HouseBuildManager::~HouseBuildManager()
{
	for (unsigned int i = 0; i < m_pHouseBuildBox.size(); i++)
	{
		delete m_pHouseBuildBox[i];
	}
}

void HouseBuildManager::Control()
{
	const KeyDevice::KEYSTATE* pState = InputDeviceManager::GetInstance()->GetKeyState();

	if (pState[DIK_Z] == KeyDevice::KEY_PUSH)
	{
		m_State = BUILD_STATE;
	}
	else if (pState[DIK_X] == KeyDevice::KEY_PUSH)
	{
		m_State = DESTROY_STATE;
	}
	else if (pState[DIK_C] == KeyDevice::KEY_PUSH)
	{
		m_State = NONE_STATE;
	}
}

void HouseBuildManager::NoneStateControl()
{
	Control();

	for (unsigned int i = 0; i < m_pHouseBuildBox.size(); i++)
	{
		if (m_pHouseBuildBox[i]->Control())
		{
			m_IsSelectBoxIndex = i;
		}
	}
}

bool HouseBuildManager::BuildStateControl()
{
	Control();

	MouseDevice::MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	if (MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		D3DXVECTOR2 MouseCursor;
		MouseCursor.x = static_cast<FLOAT>(MouseState.CursorPos.x);
		MouseCursor.y = static_cast<FLOAT>(MouseState.CursorPos.y);

		if (m_pFieldMessenger->HouseBuildMessage(&MouseCursor))
		{
			m_NumX = static_cast<int>((MouseCursor.x) / CHIP_SIZE);
			m_NumY = static_cast<int>((MouseCursor.y) / CHIP_SIZE);
			return true;
		}
	}

	return false;
}

bool HouseBuildManager::DestroyStateControl()
{
	Control();

	MouseDevice::MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	if (MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		D3DXVECTOR2 MouseCursor;
		MouseCursor.x = static_cast<FLOAT>(MouseState.CursorPos.x);
		MouseCursor.y = static_cast<FLOAT>(MouseState.CursorPos.y);

		if( m_pFieldMessenger->HouseDestroyMessage(&MouseCursor))
		{
			m_NumX = static_cast<int>((MouseCursor.x) / CHIP_SIZE);
			m_NumY = static_cast<int>((MouseCursor.y) / CHIP_SIZE);
			return true;
		}
	}

	return false;
}

void HouseBuildManager::Draw()
{
	for (unsigned int i = 0; i < m_pHouseBuildBox.size(); i++)
	{
		m_pHouseBuildBox[i]->Draw();
	}

	RECT Rect;
	TCHAR Buff[128];

	Rect.left = 750;
	Rect.top = 650;
	sprintf_s(Buff, "BUILD_STATE：Zキー : DESTROY_STATE：Xキー : NONE_STATE：Cキー");
	DebugFont::GetInstance()->DrawFont(Rect, Buff);
	
	Rect.top += 25;
	switch (m_State)
	{
	case NONE_STATE:
		sprintf_s(Buff, "現在の状態 : ノーマルモード ");
		break;
	case BUILD_STATE:
		sprintf_s(Buff, "現在の状態 : ビルドモード ");
		break;
	case DESTROY_STATE:
		sprintf_s(Buff, "現在の状態 : デストロイモード");
		break;
	}
	DebugFont::GetInstance()->DrawFont(Rect, Buff);

	Rect.top += 25;
	sprintf_s(Buff, "選択している建物番号 ： %d", m_IsSelectBoxIndex);
	DebugFont::GetInstance()->DrawFont(Rect, Buff);
}

House* HouseBuildManager::HouseBuild()
{
	House* pHouse = new House(m_NumX, m_NumY, m_pHouseBuildBox[m_IsSelectBoxIndex]);

	return pHouse;
}
