/**
 * @file   KingdomDataUI.cpp
 * @brief  KingdomDataUIクラスの実装
 * @author morimoto
 */
#include "KingdomDataUI.h"
#include "..\GameDataManager\GameDataManager.h"
#include <stdio.h>

const D3DXVECTOR2 KingdomDataUI::m_MoneyTextPos = D3DXVECTOR2(-240, -45);
const D3DXVECTOR2 KingdomDataUI::m_PopulationTextPos = D3DXVECTOR2(-240, 0);
const D3DXVECTOR2 KingdomDataUI::m_DefaultFontSize = D3DXVECTOR2(16, 32);


KingdomDataUI::KingdomDataUI(const D3DXVECTOR2* _pParentUIPos) :
TextUI(&D3DXVECTOR2(*_pParentUIPos), &m_DefaultFontSize),
m_ParentUIPos(*_pParentUIPos)
{
}

KingdomDataUI::~KingdomDataUI()
{
}

void KingdomDataUI::Control()
{
	if (m_IsVisible == false)
	{
		return;
	}
}

void KingdomDataUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	MoneyTextDraw();
	PopulationTextDraw();
}

void KingdomDataUI::MoneyTextDraw()
{
	KingdomDataManager::KINGDOMDATA KingdomData = GameDataManager::GetInstance()->GetKingdomData();
	TCHAR MoneyText[64];
	sprintf_s(MoneyText, "Money %d G", KingdomData.Money);

	m_TextPos = m_ParentUIPos + m_MoneyTextPos;
	TextDraw(MoneyText);
}

void KingdomDataUI::PopulationTextDraw()
{
	KingdomDataManager::KINGDOMDATA KingdomData = GameDataManager::GetInstance()->GetKingdomData();
	TCHAR PopulationText[64];
	sprintf_s(PopulationText, "Population %d", KingdomData.Population);

	m_TextPos = m_ParentUIPos + m_PopulationTextPos;
	TextDraw(PopulationText);
}

