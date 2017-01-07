/**
 * @file   GameTimeUI.cpp
 * @brief  GameTimeUIクラスの実装
 * @author morimoto
 */
#include "GameTimeUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"
#include <stdio.h>

const D3DXVECTOR2 GameTimeUI::m_DefaultTextPos = D3DXVECTOR2(-130, 65);
const D3DXVECTOR2 GameTimeUI::m_DefaultFontSize = D3DXVECTOR2(16, 32);
const D3DXVECTOR2 GameTimeUI::m_YearTextPos = D3DXVECTOR2(-100, 0);
const D3DXVECTOR2 GameTimeUI::m_MonthTextPos = D3DXVECTOR2(-40, 0);
const D3DXVECTOR2 GameTimeUI::m_DayTextPos = D3DXVECTOR2(25, 0);
const D3DXVECTOR2 GameTimeUI::m_HourTextPos = D3DXVECTOR2(90, 0);
const Vertex::VERTEX GameTimeUI::m_DefaultVertexData[4] = 
{
	Vertex::VERTEX{ D3DXVECTOR3(-150, -20, 0), D3DXVECTOR2(0, 0), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3( 150, -20, 0), D3DXVECTOR2(1, 0), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3(-150,  20, 0), D3DXVECTOR2(0, 1), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3( 150,  20, 0), D3DXVECTOR2(1, 1), D3DXCOLOR(0xffffffff) }
};


GameTimeUI::GameTimeUI(const D3DXVECTOR2* _pParentUIPos) :
TextUI(&D3DXVECTOR2(m_DefaultTextPos + *_pParentUIPos), &m_DefaultFontSize),
m_ParentUIPos(*_pParentUIPos),
m_pVertex(NULL),
m_TextureIndex(TextureManager::m_InvalidIndex),
m_GameTime(0, 0, 0, 0)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\GameTime.png"),
		&m_TextureIndex);

	m_pVertex = new Vertex(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init();
	m_pVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultTextPos + *_pParentUIPos));
	m_pVertex->CreateVertexBuffer(m_DefaultVertexData, 4);

	m_GameTime = GameDataManager::GetInstance()->GetGameTime();
}

GameTimeUI::~GameTimeUI()
{
	m_pVertex->ReleaseVertexBuffer();
	m_pVertex->Release();
	delete m_pVertex;
	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void GameTimeUI::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_GameTime = GameDataManager::GetInstance()->GetGameTime();
}

void GameTimeUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	YearTextDraw();
	MonthTextDraw();
	DayTextDraw();
	HourTextDraw();

	m_pVertex->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultTextPos + m_ParentUIPos));
	m_pVertex->Draw();
}

void GameTimeUI::YearTextDraw()
{
	TCHAR YearText[64];
	sprintf_s(YearText, "%d", m_GameTime.Year);
	m_TextPos = D3DXVECTOR2(m_DefaultTextPos + m_ParentUIPos + m_YearTextPos);
	TextDraw(YearText);
}

void GameTimeUI::MonthTextDraw()
{
	TCHAR MonthText[64];
	sprintf_s(MonthText, "%d", m_GameTime.Month);
	m_TextPos = D3DXVECTOR2(m_DefaultTextPos + m_ParentUIPos + m_MonthTextPos);
	TextDraw(MonthText);
}

void GameTimeUI::DayTextDraw()
{
	TCHAR DayText[64];
	sprintf_s(DayText, "%d", m_GameTime.Day);
	m_TextPos = D3DXVECTOR2(m_DefaultTextPos + m_ParentUIPos + m_DayTextPos);
	TextDraw(DayText);
}

void GameTimeUI::HourTextDraw()
{
	TCHAR HourText[64];
	sprintf_s(HourText, "%d", m_GameTime.Hour);
	m_TextPos = D3DXVECTOR2(m_DefaultTextPos + m_ParentUIPos + m_HourTextPos);
	TextDraw(HourText);
}


