#include "FieldManager.h"
#include "DX9Manager\DX9Manager.h"
#include <stdio.h>


FieldManager::FieldManager()
{
	D3DXCreateTextureFromFile(DX9Manager::GetInstance()->GetDevice(), "Resource\\NoneArea.png", &m_pTexture[NONE_TYPE]);
	D3DXCreateTextureFromFile(DX9Manager::GetInstance()->GetDevice(), "Resource\\RoadArea.png", &m_pTexture[ROAD_TYPE]);
	D3DXCreateTextureFromFile(DX9Manager::GetInstance()->GetDevice(), "Resource\\HouseArea.png", &m_pTexture[HOUSE_TYPE]);

	for (int y = 0; y < FIELD_NUM; y++)
	{
		for (int x = 0; x < FIELD_NUM; x++)
		{
			m_pField[y][x] = NONE_TYPE;
		}
	}

	CsvMapLoad("Resource\\map2.csv");

	m_pVertex[0].Pos = D3DXVECTOR4(0, 0, 0.5, 1.0);
	m_pVertex[0].UV = D3DXVECTOR2(0.0, 0.0);
	m_pVertex[1].Pos = D3DXVECTOR4(CHIP_SIZE, 0, 0.5, 1.0);
	m_pVertex[1].UV = D3DXVECTOR2(1.0, 0.0);
	m_pVertex[2].Pos = D3DXVECTOR4(0, CHIP_SIZE, 0.5, 1.0);
	m_pVertex[2].UV = D3DXVECTOR2(0.0, 1.0);
	m_pVertex[3].Pos = D3DXVECTOR4(CHIP_SIZE, CHIP_SIZE, 0.5, 1.0);
	m_pVertex[3].UV = D3DXVECTOR2(1.0, 1.0);
}

FieldManager::~FieldManager()
{
	m_pTexture[HOUSE_TYPE]->Release();
	m_pTexture[ROAD_TYPE]->Release();
	m_pTexture[NONE_TYPE]->Release();
}

void FieldManager::Control()
{

}

void FieldManager::Draw()
{
	CUSTOMVERTEX TmpVertex[4];
	for (int i = 0; i < 4; i++)
	{
		TmpVertex[i] = m_pVertex[i];
	}

	for (int y = 0; y < FIELD_NUM; y++)
	{
		TmpVertex[0].Pos.x = 0;
		TmpVertex[1].Pos.x = CHIP_SIZE;
		TmpVertex[2].Pos.x = 0;
		TmpVertex[3].Pos.x = CHIP_SIZE;

		for (int x = 0; x < FIELD_NUM; x++)
		{
			switch (m_pField[y][x])
			{
			case NONE_TYPE:
				DX9Manager::GetInstance()->GetDevice()->SetTexture(0, m_pTexture[NONE_TYPE]);

				break;
			case ROAD_TYPE:
				DX9Manager::GetInstance()->GetDevice()->SetTexture(0, m_pTexture[ROAD_TYPE]);

				break;
			case HOUSE_TYPE:
				DX9Manager::GetInstance()->GetDevice()->SetTexture(0, m_pTexture[HOUSE_TYPE]);

				break;
			default:
				DX9Manager::GetInstance()->GetDevice()->SetTexture(0, NULL);

				break;
			}
			DX9Manager::GetInstance()->GetDevice()->SetFVF(FIELDMANAGER_FVF);
			DX9Manager::GetInstance()->GetDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, TmpVertex, sizeof(CUSTOMVERTEX));


			for (int i = 0; i < 4; i++)
			{
				TmpVertex[i].Pos.x += CHIP_SIZE;
			}
		}

		for (int i = 0; i < 4; i++)
		{
			TmpVertex[i].Pos.y += CHIP_SIZE;
		}
	}
}

bool FieldManager::HouseBuild(const D3DXVECTOR2* _pBuildPos)
{
	int MapX = static_cast<int>((_pBuildPos->x) / CHIP_SIZE);
	int MapY = static_cast<int>((_pBuildPos->y) / CHIP_SIZE);

	if (MapX >= 0 && MapX < FIELD_NUM)
	{
		if (MapY >= 0 && MapY < FIELD_NUM)
		{
			if (m_pField[MapY][MapX] == NONE_TYPE)
			{
				m_pField[MapY][MapX] = HOUSE_TYPE;
				return true;
			}
		}
	}

	return false;
}

bool FieldManager::HouseDestroy(const D3DXVECTOR2* _pDestroyPos)
{
	int MapX = static_cast<int>(_pDestroyPos->x / CHIP_SIZE);
	int MapY = static_cast<int>(_pDestroyPos->y / CHIP_SIZE);

	if (MapX >= 0 && MapX < FIELD_NUM)
	{
		if (MapY >= 0 && MapY < FIELD_NUM)
		{
			if (m_pField[MapY][MapX] == HOUSE_TYPE)
			{
				m_pField[MapY][MapX] = NONE_TYPE;
				return true;
			}
		}
	}

	return false;
}

void FieldManager::CsvMapLoad(LPCTSTR _pFileName)
{
	FILE*  fp;
	fopen_s(&fp, _pFileName, "r");

	for (int i = 0; i < FIELD_NUM; i++)
	{
		for (int j = 0; j < FIELD_NUM; j++)
		{
			fscanf_s(fp, "%d,", &m_pField[i][j], _countof(m_pField));
		}
	}
}

