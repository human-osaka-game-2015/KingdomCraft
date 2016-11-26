#include "HouseBuildBox.h"
#include "DX9Manager\DX9Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"
#include "DebugFont\DebugFont.h"
#include "..\Resource\resource.h"
#include <stdio.h>

House::HOUSE_STATUS	HouseBuildBox::m_Status;
int HouseBuildBox::m_HouseBuildBoxNum = 0;


LRESULT CALLBACK HouseBuildBox::DialogBoxProc(HWND hDialog, UINT message, WPARAM wp, LPARAM lp)
{
	switch (message)
	{
	case WM_INITDIALOG:
		SetDlgItemText(hDialog, IDC_PARAM_NAME, "None");
		SetDlgItemInt(hDialog, IDC_PARAM1, 0, FALSE);
		SetDlgItemInt(hDialog, IDC_PARAM2, 0, FALSE);
		SetDlgItemInt(hDialog, IDC_PARAM3, 0, FALSE);

		m_Status.Name = "None";
		m_Status.Param1 = 0;
		m_Status.Param2 = 0;
		m_Status.Param3 = 0;

		break;
	case WM_CLOSE:
		EndDialog(hDialog, WM_CLOSE);
		break;
	case WM_COMMAND:
		switch (LOWORD(wp))
		{
		case IDC_APPLYBTN:
		{
			BOOL IsSuccess = false;
			TCHAR Buff[128];
			GetDlgItemText(hDialog, IDC_PARAM_NAME, Buff, _countof(Buff));
			m_Status.Name = Buff;
			m_Status.Param1 = GetDlgItemInt(hDialog, IDC_PARAM1, &IsSuccess, FALSE);
			m_Status.Param2 = GetDlgItemInt(hDialog, IDC_PARAM2, &IsSuccess, FALSE);
			m_Status.Param3 = GetDlgItemInt(hDialog, IDC_PARAM3, &IsSuccess, FALSE);
		}
		break;
		case IDC_ENDBTN:
		{
			EndDialog(hDialog, WM_CLOSE);
		}
		break;
		}
	default:
		return false;
	}

	return true;
}

HouseBuildBox::HouseBuildBox(const D3DXVECTOR2* _pBuildBoxPos, const D3DXVECTOR2* _pBuildBoxSize, HINSTANCE _hInst) :
m_BuildBoxPos(*_pBuildBoxPos),
m_BuildBoxSize(*_pBuildBoxSize),
m_hInstance(_hInst),
m_Number(m_HouseBuildBoxNum)
{
	m_HouseBuildBoxNum++;

	D3DXCreateTextureFromFile(DX9Manager::GetInstance()->GetDevice(), "Resource\\BuildBox.png", &m_pTexture[BUILDBOX_TEXTURE]);

	m_pVertex[0].Pos = D3DXVECTOR4(m_BuildBoxPos.x, m_BuildBoxPos.y, 0.5, 1.0);
	m_pVertex[0].UV = D3DXVECTOR2(0.0, 0.0);
	m_pVertex[1].Pos = D3DXVECTOR4(m_BuildBoxPos.x + m_BuildBoxSize.x, m_BuildBoxPos.y, 0.5, 1.0);
	m_pVertex[1].UV = D3DXVECTOR2(1.0, 0.0);
	m_pVertex[2].Pos = D3DXVECTOR4(m_BuildBoxPos.x, m_BuildBoxPos.y + m_BuildBoxSize.y, 0.5, 1.0);
	m_pVertex[2].UV = D3DXVECTOR2(0.0, 1.0);
	m_pVertex[3].Pos = D3DXVECTOR4(m_BuildBoxPos.x + m_BuildBoxSize.x, m_BuildBoxPos.y + m_BuildBoxSize.y, 0.5, 1.0);
	m_pVertex[3].UV = D3DXVECTOR2(1.0, 1.0);

	m_HouseStatus.Name = "None";
	m_HouseStatus.Param1 = 0;
	m_HouseStatus.Param2 = 0;
	m_HouseStatus.Param3 = 0;
}

HouseBuildBox::~HouseBuildBox()
{
	m_pTexture[BUILDBOX_TEXTURE]->Release();
}

bool HouseBuildBox::Control()
{
	MouseDevice::MOUSESTATE MouseState = InputDeviceManager::GetInstance()->GetMouseState();

	if (m_BuildBoxPos.x < MouseState.CursorPos.x &&
		m_BuildBoxPos.x + m_BuildBoxSize.x > MouseState.CursorPos.x)
	{
		if (m_BuildBoxPos.y < MouseState.CursorPos.y &&
			m_BuildBoxPos.y + m_BuildBoxSize.y > MouseState.CursorPos.y)
		{
			if (MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_RELEASE)
			{
				return true;
			}
			else if (MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_RELEASE)
			{
				DialogBox(m_hInstance, TEXT("SERVER_DLG"), NULL, (DLGPROC)HouseBuildBox::DialogBoxProc);
				m_HouseStatus.Name = m_Status.Name;
				m_HouseStatus.Param1 = m_Status.Param1;
				m_HouseStatus.Param2 = m_Status.Param2;
				m_HouseStatus.Param3 = m_Status.Param3;
			}
		}
	}

	return false;
}

void HouseBuildBox::Draw()
{
	DX9Manager::GetInstance()->GetDevice()->SetTexture(0, m_pTexture[BUILDBOX_TEXTURE]);
	DX9Manager::GetInstance()->GetDevice()->SetFVF(HOUSEBUILDBOX_FVF);
	DX9Manager::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, m_pVertex, sizeof(CUSTOMVERTEX));

	char Buff[256];
	RECT Rect;
	Rect.left = static_cast<LONG>(m_BuildBoxPos.x + 5);
	Rect.top = static_cast<LONG>(m_BuildBoxPos.y + 5);


	sprintf_s(Buff, "%s：建物番号 %d", m_HouseStatus.Name.c_str(), m_Number);
	DebugFont::GetInstance()->DrawFont(Rect, Buff);

	sprintf_s(Buff, "信仰：%d", m_HouseStatus.Param1);
	Rect.top += 30;
	DebugFont::GetInstance()->DrawFont(Rect, Buff);

	sprintf_s(Buff, "治安：%d", m_HouseStatus.Param2);
	Rect.top += 25;
	DebugFont::GetInstance()->DrawFont(Rect, Buff);

	sprintf_s(Buff, "景観：%d",m_HouseStatus.Param3);
	Rect.top += 25;
	DebugFont::GetInstance()->DrawFont(Rect, Buff);
}
