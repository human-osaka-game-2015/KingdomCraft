/**
 * @file   KingdomDemandUI.cpp
 * @brief  KingdomDemandUIクラスの実装
 * @author morimoto
 */
#include "KingdomDemandUI.h"
#include "DX11Manager\DX11Manager.h"
#include "TextureManager\TextureManager.h"

const D3DXVECTOR2 KingdomDemandUI::m_DefaultTitlePos = D3DXVECTOR2(-45, -75);
const Vertex::VERTEX KingdomDemandUI::m_DefaultTitleVertexData[4] =
{
	Vertex::VERTEX{ D3DXVECTOR3(-40, -20, 0), D3DXVECTOR2(0, 0), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3( 40, -20, 0), D3DXVECTOR2(1, 0), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3(-40,  20, 0), D3DXVECTOR2(0, 1), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3( 40,  20, 0), D3DXVECTOR2(1, 1), D3DXCOLOR(0xffffffff) }
};

const D3DXVECTOR2 KingdomDemandUI::m_DefaultHousePos = D3DXVECTOR2(-75, -40);
const D3DXVECTOR2 KingdomDemandUI::m_DefaultCommercePos = D3DXVECTOR2(-45, -40);
const D3DXVECTOR2 KingdomDemandUI::m_DefaultIndustryPos = D3DXVECTOR2(-15, -40);

const Vertex::VERTEX KingdomDemandUI::m_DefaultGaugeVertexData[4] = 
{
	Vertex::VERTEX{ D3DXVECTOR3(-10, 0, 0), D3DXVECTOR2(0, 0), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3( 10, 0, 0), D3DXVECTOR2(1, 0), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3(-10, 0, 0), D3DXVECTOR2(0, 1), D3DXCOLOR(0xffffffff) },
	Vertex::VERTEX{ D3DXVECTOR3( 10, 0, 0), D3DXVECTOR2(1, 1), D3DXCOLOR(0xffffffff) }
};

const D3DXCOLOR KingdomDemandUI::m_PlusColor = 0xff0000ff;
const D3DXCOLOR KingdomDemandUI::m_MinusColor = 0xffff0000;


KingdomDemandUI::KingdomDemandUI(const D3DXVECTOR2* _pParentUIPos) : 
m_ParentUIPos(*_pParentUIPos),
m_KingdomDemand(0.f, 0.f, 0.f)
{
	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\DemandTitle.png"),
		&m_TitleTextureIndex);

	m_pTitleVertex = new Vertex(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());


	m_pTitleVertex->Init();
	m_pTitleVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_TitleTextureIndex));
	m_pTitleVertex->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultTitlePos + *_pParentUIPos));
	m_pTitleVertex->CreateVertexBuffer(m_DefaultTitleVertexData, 4);


	TextureManager::GetInstance()->LoadTexture(
		TEXT("Resource\\Texture\\GameScene\\UI\\KingdomDemandGauge.png"),
		&m_GaugeTextureIndex);

	m_pGaugeVertex = new Vertex(
		DX11Manager::GetInstance()->GetDevice(),
		DX11Manager::GetInstance()->GetDeviceContext(),
		DX11Manager::GetInstance()->GetWindowHandle());

	m_pGaugeVertex->Init();
	m_pGaugeVertex->SetTexture(TextureManager::GetInstance()->GetTexture(m_GaugeTextureIndex));
	m_pGaugeVertex->WriteConstantBuffer(&D3DXVECTOR2(*_pParentUIPos));
	m_pGaugeVertex->CreateVertexBuffer(m_DefaultGaugeVertexData, 4);
}

KingdomDemandUI::~KingdomDemandUI()
{
	m_pGaugeVertex->ReleaseVertexBuffer();
	m_pGaugeVertex->Release();
	delete m_pGaugeVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_GaugeTextureIndex);


	m_pTitleVertex->ReleaseVertexBuffer();
	m_pTitleVertex->Release();
	delete m_pTitleVertex;

	TextureManager::GetInstance()->ReleaseTexture(m_TitleTextureIndex);
}

void KingdomDemandUI::Control()
{
}

void KingdomDemandUI::Draw()
{
	TitleDraw();	// 需要UIのタイトル描画
	GaugeDraw();	// 需要UIのゲージ描画
}

void KingdomDemandUI::TitleDraw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);

	m_pTitleVertex->Draw();
}

void KingdomDemandUI::GaugeDraw()
{
	DX11Manager::GetInstance()->SetDepthStencilTest(false);

	HouseGaugeDraw();		// 住宅需要のゲージ描画
	CommerceGaugeDraw();	// 商業需要のゲージ描画
	IndustryGaugeDraw();	// 工業需要のゲージ描画
}

void KingdomDemandUI::HouseGaugeDraw()
{
	Vertex::VERTEX Vertex[4];
	memcpy_s(Vertex, sizeof(Vertex::VERTEX) * 4, m_DefaultGaugeVertexData, sizeof(Vertex::VERTEX) * 4);

	if (m_KingdomDemand.House > 0.f)
	{
		Vertex[0].Pos.y -= m_KingdomDemand.House;
		Vertex[1].Pos.y -= m_KingdomDemand.House;

		for (int i = 0; i < 4; i++)
		{
			Vertex[i].Color = m_PlusColor;
		}
	}
	else
	{
		Vertex[2].Pos.y -= m_KingdomDemand.House;
		Vertex[3].Pos.y -= m_KingdomDemand.House;

		for (int i = 0; i < 4; i++)
		{
			Vertex[i].Color = m_MinusColor;
		}
	}

	m_pGaugeVertex->WriteVertexBuffer(Vertex);
	m_pGaugeVertex->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultHousePos + m_ParentUIPos));
	m_pGaugeVertex->Draw();
}

void KingdomDemandUI::CommerceGaugeDraw()
{
	Vertex::VERTEX Vertex[4];
	memcpy_s(Vertex, sizeof(Vertex::VERTEX) * 4, m_DefaultGaugeVertexData, sizeof(Vertex::VERTEX) * 4);

	if (m_KingdomDemand.Commerce > 0.f)
	{
		Vertex[0].Pos.y -= m_KingdomDemand.Commerce;
		Vertex[1].Pos.y -= m_KingdomDemand.Commerce;

		for (int i = 0; i < 4; i++)
		{
			Vertex[i].Color = m_PlusColor;
		}
	}
	else
	{
		Vertex[2].Pos.y -= m_KingdomDemand.Commerce;
		Vertex[3].Pos.y -= m_KingdomDemand.Commerce;

		for (int i = 0; i < 4; i++)
		{
			Vertex[i].Color = m_MinusColor;
		}
	}

	m_pGaugeVertex->WriteVertexBuffer(Vertex);
	m_pGaugeVertex->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultCommercePos + m_ParentUIPos));
	m_pGaugeVertex->Draw();
}

void KingdomDemandUI::IndustryGaugeDraw()
{
	Vertex::VERTEX Vertex[4];
	memcpy_s(Vertex, sizeof(Vertex::VERTEX) * 4, m_DefaultGaugeVertexData, sizeof(Vertex::VERTEX) * 4);

	if (m_KingdomDemand.Industry > 0.f)
	{
		Vertex[0].Pos.y -= m_KingdomDemand.Industry;
		Vertex[1].Pos.y -= m_KingdomDemand.Industry;

		for (int i = 0; i < 4; i++)
		{
			Vertex[i].Color = m_PlusColor;
		}
	}
	else
	{
		Vertex[2].Pos.y -= m_KingdomDemand.Industry;
		Vertex[3].Pos.y -= m_KingdomDemand.Industry;

		for (int i = 0; i < 4; i++)
		{
			Vertex[i].Color = m_MinusColor;
		}
	}

	m_pGaugeVertex->WriteVertexBuffer(Vertex);
	m_pGaugeVertex->WriteConstantBuffer(&D3DXVECTOR2(m_DefaultIndustryPos + m_ParentUIPos));
	m_pGaugeVertex->Draw();
}
