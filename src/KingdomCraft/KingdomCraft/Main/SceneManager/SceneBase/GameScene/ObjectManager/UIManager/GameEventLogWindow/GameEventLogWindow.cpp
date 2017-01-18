/**
 * @file   GameEventLogWindow.cpp
 * @brief  GameEventLogWindowクラスの実装
 * @author morimoto
 */
#include "GameEventLogWindow.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include "EventManager.h"

const D3DXVECTOR2 GameEventLogWindow::m_DefaultPos = D3DXVECTOR2(1165, 600);
const D3DXVECTOR2 GameEventLogWindow::m_DefaultSize = D3DXVECTOR2(400, 100);
const float	GameEventLogWindow::m_DefaultAlpha = 1.0f;
const D3DXVECTOR2 GameEventLogWindow::m_DefaultTexel[4] = 
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 0.25),
	D3DXVECTOR2(1, 0.25)
};
const D3DXVECTOR2 GameEventLogWindow::m_VictoryTexelOffset = D3DXVECTOR2(0, 0.25);
const D3DXVECTOR2 GameEventLogWindow::m_DefeatTexelOffset = D3DXVECTOR2(0, 0.5);
const int GameEventLogWindow::m_EventLogMax = 5;
const float GameEventLogWindow::m_EventLogMoveSpeed = 2.0f;
const float GameEventLogWindow::m_EventLogAlphaSpeed = 0.006f;


GameEventLogWindow::GameEventLogWindow() : 
WindowUI(&m_DefaultPos, &m_DefaultSize),
m_pEventListener(new GameEventListener())
{
	EventManager::GetInstance()->AddEventListener(m_pEventListener);

	TextureManager::GetInstance()->LoadTexture(
		"Resource\\Texture\\GameScene\\UI\\GameEventLogWindow.png",
		&m_TextureIndex);

	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(0, 0), &D3DXVECTOR2(1.0f, 1.0f));
}

GameEventLogWindow::~GameEventLogWindow()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);

	EventManager::GetInstance()->RemoveEventListener(m_pEventListener);
	delete m_pEventListener;
}

void GameEventLogWindow::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}

	EventMessageControl();
	EventLogControl();
}

void GameEventLogWindow::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	EventLogDraw();
}

void GameEventLogWindow::EventMessageControl()
{
	switch (m_pEventListener->GetEventType())
	{
	case GameEvent::VICTORY_EVENT:
		if (m_EventLogs.size() < m_EventLogMax)
		{
			m_EventLogs.push_back(GameEvent::VICTORY_EVENT);
			m_EventLogsPos.push_back(m_DefaultPos);
			m_EventLogsAlpha.push_back(m_DefaultAlpha);
		}
		break;
	case GameEvent::DEFEAT_EVENT:
		if (m_EventLogs.size() < m_EventLogMax)
		{
			m_EventLogs.push_back(GameEvent::DEFEAT_EVENT);
			m_EventLogsPos.push_back(m_DefaultPos);
			m_EventLogsAlpha.push_back(m_DefaultAlpha);
		}
		break;
	}

	m_pEventListener->ClearEventType();
}

void GameEventLogWindow::EventLogControl()
{
	for (unsigned int i = 0; i < m_EventLogs.size(); i++)
	{
		m_EventLogsPos[i].y -= m_EventLogMoveSpeed;
		m_EventLogsAlpha[i] -= m_EventLogAlphaSpeed;

		if (m_EventLogsAlpha[i] <= 0)	// 透過度が0になって見えなくなっていたら
		{
			// イベントログから削除
			m_EventLogs.erase(m_EventLogs.begin() + i);
			m_EventLogsPos.erase(m_EventLogsPos.begin() + i);
			m_EventLogsAlpha.erase(m_EventLogsAlpha.begin() + i);
		}
	}
}

void GameEventLogWindow::EventLogDraw()
{
	for (unsigned int i = 0; i < m_EventLogs.size(); i++)
	{
		switch (m_EventLogs[i])
		{
		case GameEvent::VICTORY_EVENT:
			m_pVertex2D->WriteConstantBuffer(
				&m_EventLogsPos[i],
				&D3DXVECTOR2(1.0f, 1.0f), 
				&m_VictoryTexelOffset,
				0.0f,
				m_EventLogsAlpha[i]);

			break;
		case GameEvent::DEFEAT_EVENT:
			m_pVertex2D->WriteConstantBuffer(
				&m_EventLogsPos[i], 
				&D3DXVECTOR2(1.0f, 1.0f), 
				&m_DefeatTexelOffset,
				0.0f,
				m_EventLogsAlpha[i]);

			break;
		}

		m_pVertex2D->Draw();
	}
}
