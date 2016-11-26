#include "House.h"
#include "..\..\FieldManager\FieldManager.h"
#include "..\HouseBuildManager\HouseBuildBox\HouseBuildBox.h"
#include "DX9Manager\DX9Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "DebugFont\DebugFont.h"

#define STATUSBOX_POS_X 0
#define STATUSBOX_POS_Y 600
#define STATUSBOX_SIZE_SIZE_X 300
#define STATUSBOX_SIZE_SIZE_Y 100


House::House(int _numX, int _numY, HouseBuildBox* _pBuildBox) :
m_pBuildBox(_pBuildBox),
m_NumX(_numX),
m_NumY(_numY),
m_IsStatusBoxVisible(false)
{
	m_Status = m_pBuildBox->GetHouseStatus();
	m_HouseRect.left = CHIP_SIZE * _numX;
	m_HouseRect.top = CHIP_SIZE * _numY;

	float StatusBoxX = static_cast<float>(m_HouseRect.left);
	float StatusBoxY = static_cast<float>(m_HouseRect.top);

	m_pVertex[0].Pos = D3DXVECTOR4(STATUSBOX_POS_X, STATUSBOX_POS_Y, 0.5, 1.0);
	m_pVertex[0].UV = D3DXVECTOR2(0.0, 0.0);
	m_pVertex[1].Pos = D3DXVECTOR4(STATUSBOX_POS_X + STATUSBOX_SIZE_SIZE_X, STATUSBOX_POS_Y, 0.5, 1.0);
	m_pVertex[1].UV = D3DXVECTOR2(1.0, 0.0);
	m_pVertex[2].Pos = D3DXVECTOR4(STATUSBOX_POS_X, STATUSBOX_POS_Y + STATUSBOX_SIZE_SIZE_Y, 0.5, 1.0);
	m_pVertex[2].UV = D3DXVECTOR2(0.0, 1.0);
	m_pVertex[3].Pos = D3DXVECTOR4(STATUSBOX_POS_X + STATUSBOX_SIZE_SIZE_X, STATUSBOX_POS_Y + STATUSBOX_SIZE_SIZE_Y, 0.5, 1.0);
	m_pVertex[3].UV = D3DXVECTOR2(1.0, 1.0);

}

House::~House()
{
}

void House::Control()
{
	m_Status = m_pBuildBox->GetHouseStatus();// 基礎ステータス更新


	MouseDevice::MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	if (m_HouseRect.left < MouseState.CursorPos.x &&
		m_HouseRect.left + CHIP_SIZE > MouseState.CursorPos.x)
	{
		if (m_HouseRect.top < MouseState.CursorPos.y &&
			m_HouseRect.top + CHIP_SIZE > MouseState.CursorPos.y)
		{
			if (MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_ON)
			{
				m_IsStatusBoxVisible = true;
				return;
			}
		}
	}

	m_IsStatusBoxVisible = false;
	return;
}

void House::Draw()
{
	char Buff[256];
	RECT Rect = m_HouseRect;
	sprintf_s(Buff, "%s", m_Status.Name.substr(0,2).c_str());
	DebugFont::GetInstance()->DrawFont(Rect, Buff);

	if (m_IsStatusBoxVisible)
	{
		Rect.left = STATUSBOX_POS_X;
		Rect.top = STATUSBOX_POS_Y;
		DX9Manager::GetInstance()->GetDevice()->SetTexture(0, NULL);
		DX9Manager::GetInstance()->GetDevice()->SetFVF(HOUSE_FVF);
		DX9Manager::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_pVertex, sizeof(CUSTOMVERTEX));

		sprintf_s(Buff, "%s", m_Status.Name.c_str());
		DebugFont::GetInstance()->DrawFont(Rect, Buff);

		sprintf_s(Buff, "信仰：%d", m_Status.Param1);
		Rect.top += 30;
		DebugFont::GetInstance()->DrawFont(Rect, Buff);

		sprintf_s(Buff, "治安：%d", m_Status.Param2);
		Rect.top += 25;
		DebugFont::GetInstance()->DrawFont(Rect, Buff);

		sprintf_s(Buff, "景観：%d", m_Status.Param3);
		Rect.top += 25;
		DebugFont::GetInstance()->DrawFont(Rect, Buff);

	}
}

bool House::NumCheck(int _numX, int _numY)
{
	if (m_NumX == _numX)
	{
		if (m_NumY == _numY)
		{
			return true;
		}
	}

	return false;
}
