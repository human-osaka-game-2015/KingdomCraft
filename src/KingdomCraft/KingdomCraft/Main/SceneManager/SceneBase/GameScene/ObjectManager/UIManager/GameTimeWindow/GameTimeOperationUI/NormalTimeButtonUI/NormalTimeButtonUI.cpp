/**
 * @file   NormalTimeButtonUI.cpp
 * @brief  NormalTimeButtonUIクラスの実装
 * @author morimoto
 */
#include "NormalTimeButtonUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 NormalTimeButtonUI::m_DefaultPos = D3DXVECTOR2(-150, 20);
const D3DXVECTOR2 NormalTimeButtonUI::m_DefaultSize = D3DXVECTOR2(32, 32);
const D3DXVECTOR2 NormalTimeButtonUI::m_DefaultTexel[4] = 
{
	D3DXVECTOR2(0, 0),
	D3DXVECTOR2(1, 0),
	D3DXVECTOR2(0, 1),
	D3DXVECTOR2(1, 1)
};


NormalTimeButtonUI::NormalTimeButtonUI(const D3DXVECTOR2* _pParentUIPos) :
ButtonUI(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos), &m_DefaultSize),
m_pVertex2D(NULL),
m_TextureIndex(TextureManager::m_InvalidIndex),
m_ParentUIPos(*_pParentUIPos)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\NormalTimeButtonUI.png"), 
		&m_TextureIndex);

	m_pVertex2D = new Vertex2D(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex2D->Init(&m_DefaultSize, m_DefaultTexel);
	m_pVertex2D->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex2D->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
}

NormalTimeButtonUI::~NormalTimeButtonUI()
{
	m_pVertex2D->Release();
	delete m_pVertex2D;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

bool NormalTimeButtonUI::Control()
{
	if (m_IsVisible == false)
	{
		return false;
	}

	return IsClicked();
}

void NormalTimeButtonUI::Draw()
{
	if (m_IsVisible == false)
	{
		return;
	}

	m_pVertex2D->Draw();
}
