#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H
#include <d3dx9.h>

#define FIELD_NUM 15
#define CHIP_SIZE 40
#define FIELDMANAGER_FVF ( D3DFVF_XYZRHW | D3DFVF_TEX1 )

class FieldManager
{
public:
	enum FIELD_TYPE
	{
		NONE_TYPE,
		ROAD_TYPE,
		HOUSE_TYPE,
		MAX_TYPE
	};

	struct CUSTOMVERTEX
	{
		D3DXVECTOR4 Pos;
		D3DXVECTOR2 UV;
	};

	FieldManager();
	~FieldManager();
	void Control();
	void Draw();
	bool HouseBuild(const D3DXVECTOR2* _pBuildPos);
	bool HouseDestroy(const D3DXVECTOR2* _pDestroyPos);


private:
	void CsvMapLoad(LPCTSTR _pFileName);

	int					m_pField[FIELD_NUM][FIELD_NUM];
	CUSTOMVERTEX		m_pVertex[4];
	LPDIRECT3DTEXTURE9	m_pTexture[MAX_TYPE];

};

#endif // !FIELDMANAGER_H
