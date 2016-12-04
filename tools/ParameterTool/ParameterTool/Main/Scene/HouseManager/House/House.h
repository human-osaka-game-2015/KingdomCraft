#ifndef HOUSE_H
#define HOUSE_H
#include <d3dx9.h>
#include <string>

#define HOUSE_FVF ( D3DFVF_XYZRHW | D3DFVF_TEX1 )

class HouseBuildBox;

class House
{
public:
	struct HOUSE_STATUS
	{
		std::string Name; // 建物名
		int Param1; // 信仰
		int Param2; // 治安
		int Param3; // 景観
	};

	House(int _numX, int _numY, HouseBuildBox* _pBuildBox);
	~House();
	void Control();
	void Draw();
	bool NumCheck(int _numX, int _numY);

private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR4 Pos;
		D3DXVECTOR2 UV;
	};

	HOUSE_STATUS	m_Status;
	RECT			m_HouseRect;
	HouseBuildBox*	m_pBuildBox;
	int				m_NumX;
	int				m_NumY;
	CUSTOMVERTEX	m_pVertex[4];
	bool			m_IsStatusBoxVisible;

};

#endif // !HOUSE_H
