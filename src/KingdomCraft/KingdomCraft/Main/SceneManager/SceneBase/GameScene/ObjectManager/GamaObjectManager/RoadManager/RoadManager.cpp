/**
 * @file   RoadManager.cpp
 * @brief  RoadManagerクラスの実装
 * @author kotani
 */
#include "RoadManager.h"
#include "../MousePosConverter/MousePosConverter.h"
#include "BuildAreaManager\BuildAreaManager.h"
#include "ShaderManager\ShaderManager.h"
#include "Road\Road.h"


RoadManager::RoadManager() :
m_pBuildAreaManager(new BuildAreaManager()),
m_CreateAreaX(30.f),
m_CreateAreaZ(30.f),
m_Step(NONE)
{
	ShaderManager::GetInstance()->LoadVertexShader(TEXT("Resource\\Effect\\GameScene\\Road.fx"), "VS", &m_VertexShaderIndex);
	ShaderManager::GetInstance()->LoadPixelShader(TEXT("Resource\\Effect\\GameScene\\Road.fx"), "PS", &m_PixelShaderIndex);
}

RoadManager::~RoadManager()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		delete m_pRoad[i];
	}
	delete m_pBuildAreaManager;
}

void RoadManager::Control()
{
	BuildControl();
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->Control();
		m_pRoad[i]->GetEndPos();
	}

}

void RoadManager::BuildControl()
{
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
	const KeyDevice::KEYSTATE* pKeyState = InputDeviceManager::GetInstance()->GetKeyState();

	if (pKeyState[DIK_F] == KeyDevice::KEYSTATE::KEY_PUSH)
	{
		if (m_Step == NONE)
		{
			m_Step = START_SET_STEP;
		}
		else
		{
			m_StartPos = D3DXVECTOR3(0.f, 0.f, 0.f);
			m_EndPos = D3DXVECTOR3(0.f, 0.f, 0.f);
			m_Step = NONE;
		}
	}

	switch (m_Step)
	{
	case START_SET_STEP:
		StartSetStep();
		break;
	case END_SET_STEP:
		EndSetStep();
		break;
	case MIDDLE_SET_STEP:
		/// @todo カーブは今度実装する
		MiddleSetStep();
		break;
	case CREATE_STEP:
		CreateStep();
		break;
	}
}

void RoadManager::StartSetStep()
{
	if (m_MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_StartPos = MousePosConverter::GetInstance()->GetConvertPos();
		if (abs(m_StartPos.x) < m_CreateAreaX && abs(m_StartPos.z) < m_CreateAreaZ)
		{
			m_Step = END_SET_STEP;
		}
	}
	else if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_Step = NONE;
	}
}

void RoadManager::MiddleSetStep()
{
}

void RoadManager::EndSetStep()
{
	if (m_MouseState.rgbButtons[0] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_EndPos = MousePosConverter::GetInstance()->GetConvertPos();
		if (abs(m_EndPos.x) < m_CreateAreaX && abs(m_EndPos.z) < m_CreateAreaZ)
		{
			float length = sqrt(
				(m_EndPos.x - m_StartPos.x) * (m_EndPos.x - m_StartPos.x) +
				(m_EndPos.z - m_StartPos.z) * (m_EndPos.z - m_StartPos.z));
			if (length == 0.f)
			{
				m_StartPos = D3DXVECTOR3(0.f, 0.f, 0.f);
				m_EndPos = D3DXVECTOR3(0.f, 0.f, 0.f);
				m_Step = NONE;
			}
			else
			{
				m_Step = CREATE_STEP;
			}
		}
	}
	else if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTON_PUSH)
	{
		m_StartPos = D3DXVECTOR3(0.f, 0.f, 0.f);
		m_Step = NONE;
	}
}

void RoadManager::CreateStep()
{
	m_pRoad.push_back(new Road(m_VertexShaderIndex, m_PixelShaderIndex, &m_StartPos, &m_EndPos));
	m_StartPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_EndPos = D3DXVECTOR3(0.f, 0.f, 0.f);
	m_Step = NONE;
}

void RoadManager::Draw()
{
	for (unsigned int i = 0; i < m_pRoad.size(); i++)
	{
		m_pRoad[i]->Draw();
	}
}
