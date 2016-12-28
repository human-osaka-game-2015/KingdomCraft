/**
 * @file   KingdomParameterUI.cpp
 * @brief  KingdomParameterUIクラスの実装
 * @author morimoto
 */
#include "KingdomParameterUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 KingdomParameterUI::m_DefaultPos = D3DXVECTOR2(-230, -65);
const Vertex::VERTEX KingdomParameterUI::m_DefaultVertexData[4] =
{
	Vertex::VERTEX{ D3DXVECTOR3(-15,   0, 0), D3DXVECTOR2(0, 0), D3DXCOLOR(0xffffffff) },	// 政治力
	Vertex::VERTEX{ D3DXVECTOR3(  0, -15, 0), D3DXVECTOR2(1, 0), D3DXCOLOR(0xffffffff) },	// 戦闘力
	Vertex::VERTEX{ D3DXVECTOR3(  0,  15, 0), D3DXVECTOR2(0, 1), D3DXCOLOR(0xffffffff) },	// 魔法力
	Vertex::VERTEX{ D3DXVECTOR3( 15,   0, 0), D3DXVECTOR2(1, 1), D3DXCOLOR(0xffffffff) }	// 工業力
};


KingdomParameterUI::KingdomParameterUI(const D3DXVECTOR2* _pParentUIPos) :
m_TextureIndex(TextureManager::m_InvalidIndex),
m_pVertex(NULL),
m_ParentUIPos(*_pParentUIPos),
m_Parameter(0, 0, 0, 0)
{
	TextureManager::GetInstance()->LoadTexture(
		"Resource\\Texture\\GameScene\\UI\\Parameter.png",
		&m_TextureIndex);

	m_pVertex = new Vertex(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pVertex->Init();
	m_pVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TextureIndex));
	m_pVertex->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultPos + *_pParentUIPos));
	m_pVertex->CreateVertexBuffer(m_DefaultVertexData, 4);
}

KingdomParameterUI::~KingdomParameterUI()
{
	m_pVertex->ReleaseVertexBuffer();
	m_pVertex->Release();
	delete m_pVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_TextureIndex);
}

void KingdomParameterUI::Control()
{
}

void KingdomParameterUI::Draw()
{
	Vertex::VERTEX VertexData[4];
	for (int i = 0; i < 4; i++)
	{
		VertexData[i] = m_DefaultVertexData[i];
	}

	// 王国のパラメーターの大きさでひし形をいじる
	VertexData[0].Pos.x -= m_Parameter.Politics;
	VertexData[1].Pos.y -= m_Parameter.CombatPower;
	VertexData[2].Pos.y += m_Parameter.MagicPower;
	VertexData[3].Pos.x += m_Parameter.Industry;
	m_pVertex->WriteVertexBuffer(VertexData);


	DX11Manager::GetInstance()->SetDepthStencilTest(false);
	m_pVertex->Draw();
}
