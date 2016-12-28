/**
 * @file   AccelerateOfTimeButtonUI.cpp
 * @brief  AccelerateOfTimeButtonUIクラスの実装
 * @author morimoto
 */
#include "AccelerateOfTimeButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 AccelerateOfTimeButtonUI::m_DefaultPos = D3DXVECTOR2(-118, 20);
const D3DXVECTOR2 AccelerateOfTimeButtonUI::m_DefaultSize = D3DXVECTOR2(32, 32);
const D3DXVECTOR2 AccelerateOfTimeButtonUI::m_DefaultTexel[4] =
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


AccelerateOfTimeButtonUI::AccelerateOfTimeButtonUI(const D3DXVECTOR2* _pParentUIPos) :
ButtonUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pVertex2D(NULL),
m_TextureIndex(TextureManager::m_InvalidIndex),
m_ParentUIPos(*_pParentUIPos)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\AccelerateOfTimeButtonUI.png"),
		&m_TextureIndex);

	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
}

AccelerateOfTimeButtonUI::~AccelerateOfTimeButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

bool AccelerateOfTimeButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void AccelerateOfTimeButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_pVertex2D->Draw();
}
