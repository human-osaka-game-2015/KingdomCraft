/**
 * @file   SoldierTypeSelect.cpp
 * @brief  SoldierTypeSelectクラスの実装
 * @author morimoto
 */
#include "SoldierTypeSelect.h"
#include "SelectLeftButtonUI\SelectLeftButtonUI.h"
#include "SelectRightButtonUI\SelectRightButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 SoldierTypeSelect::m_DefaultPos = D3DXVECTOR2(-80, -150);
const D3DXVECTOR2 SoldierTypeSelect::m_DefaultSize = D3DXVECTOR2(100, 100);
const D3DXVECTOR2 SoldierTypeSelect::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0.0f,  0.0f),
	D3DXVECTOR2(0.25f, 0.0f),
	D3DXVECTOR2(0.0f,  0.5f),
	D3DXVECTOR2(0.25f, 0.5f)
};

const D3DXVECTOR2 SoldierTypeSelect::m_TexelOffset = D3DXVECTOR2(0.25, 0);


SoldierTypeSelect::SoldierTypeSelect(const D3DXVECTOR2* _pParentUIPos, int _textureIndex) :
m_Pos(D3DXVECTOR2(m_DefaultPos + *_pParentUIPos)),
m_pParentUIPos(_pParentUIPos),
m_TextureIndex(_textureIndex),
m_SelectType(SWORD_TYPE)
{
	m_pLeftButton = new SelectLeftButtonUI(&m_Pos, m_TextureIndex);
	m_pRightButton = new SelectRightButtonUI(&m_Pos, m_TextureIndex);

	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&m_Pos);
}

SoldierTypeSelect::~SoldierTypeSelect()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;

	delete m_pRightButton;
	delete m_pLeftButton;
}

void SoldierTypeSelect::Control()
{
	bool IsLeftButtonClick = m_pLeftButton->Control();
	bool IsRightButtonClick = m_pRightButton->Control();

	if (IsLeftButtonClick == true)
	{
		SelectMoveToLeft();
	}
	else if (IsRightButtonClick == true)
	{
		SelectMoveToRight();
	}
}

void SoldierTypeSelect::Draw()
{
	SelectTypeDraw();
	m_pLeftButton->Draw();
	m_pRightButton->Draw();
}

void SoldierTypeSelect::SelectMoveToLeft()
{
	switch (m_SelectType)
	{
	case SWORD_TYPE:
		m_SelectType = WITCH_TYPE;
		break;
	case ARCHER_TYPE:
		m_SelectType = SWORD_TYPE;
		break;
	case WITCH_TYPE:
		m_SelectType = ARCHER_TYPE;
		break;
	}
}

void SoldierTypeSelect::SelectMoveToRight()
{
	switch (m_SelectType)
	{
	case SWORD_TYPE:
		m_SelectType = ARCHER_TYPE;
		break;
	case ARCHER_TYPE:
		m_SelectType = WITCH_TYPE;
		break;
	case WITCH_TYPE:
		m_SelectType = SWORD_TYPE;
		break;
	}
}

void SoldierTypeSelect::SelectTypeDraw()
{
	D3DXVECTOR2 TexelOffset(0.0f, 0.0f);

	switch (m_SelectType)
	{
	case SWORD_TYPE:
		break;
	case ARCHER_TYPE:
		TexelOffset = m_TexelOffset;
		break;
	case WITCH_TYPE:
		TexelOffset = m_TexelOffset * WITCH_TYPE;
		break;
	}

	m_Pos = D3DXVECTOR2(m_DefaultPos + *m_pParentUIPos);
	m_pVertex2D->WriteConstantBuffer(&m_Pos, &D3DXVECTOR2(1.0f, 1.0f), &TexelOffset);
	m_pVertex2D->Draw();
}
