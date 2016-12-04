#ifndef HOUSEBUILDBOX_H
#define HOUSEBUILDBOX_H
#include <d3dx9.h>
#include "..\..\House\House.h"

#define HOUSEBUILDBOX_FVF ( D3DFVF_XYZRHW | D3DFVF_TEX1 )

class HouseBuildBox
{
public:
	HouseBuildBox(const D3DXVECTOR2* _pBuildBoxPos, const D3DXVECTOR2* _pBuildBoxSize, HINSTANCE _hInst);
	~HouseBuildBox();
	
	/**
	 * HouseBuildBoxクラスの制御関数
	 * @return Boxが選択されたらtrue
	 */
	bool Control();
	void Draw();

	inline House::HOUSE_STATUS GetHouseStatus()
	{
		return m_HouseStatus;
	}

private:
	struct CUSTOMVERTEX
	{
		D3DXVECTOR4 Pos;
		D3DXVECTOR2 UV;
	};

	enum TEXTURE
	{
		BUILDBOX_TEXTURE,	//!< 建設BOXテクスチャ
		TEXTURE_MAX			//!< テクスチャの最大数
	};

	static LRESULT CALLBACK DialogBoxProc(HWND hDialog, UINT message, WPARAM wp, LPARAM lp);

	static House::HOUSE_STATUS	m_Status;
	static int					m_HouseBuildBoxNum;
	const D3DXVECTOR2			m_BuildBoxPos;
	const D3DXVECTOR2			m_BuildBoxSize;
	CUSTOMVERTEX				m_pVertex[4];
	LPDIRECT3DTEXTURE9			m_pTexture[TEXTURE_MAX];
	House::HOUSE_STATUS			m_HouseStatus;
	HINSTANCE					m_hInstance;
	int							m_Number;

};

#endif