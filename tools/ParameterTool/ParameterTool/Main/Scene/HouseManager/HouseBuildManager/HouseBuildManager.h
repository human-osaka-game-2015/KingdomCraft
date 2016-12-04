#ifndef HOUSEBUILDMANAGER_H
#include "..\House\House.h"
#include "HouseBuildBox\HouseBuildBox.h"
#include <d3dx9.h>
#include <vector>

#define HOUSEBUILDMANAGER_FVF ( D3DFVF_XYZRHW | D3DFVF_TEX1 )

class FieldMessenger;

class HouseBuildManager
{
public:
	enum STATE
	{
		NONE_STATE,		//!< 何も行わない状態
		BUILD_STATE,	//!< 家を建設する状態
		DESTROY_STATE	//!< 家を撤去する状態
	};

	HouseBuildManager(FieldMessenger* _pFieldMessenger, HINSTANCE _hInst);
	~HouseBuildManager();
	void NoneStateControl();
	bool BuildStateControl();
	bool DestroyStateControl();
	void Draw();

	House* HouseBuild();

	inline STATE GetState()
	{
		return m_State;
	}

	inline void GetNum(int* _pNumX, int* _pNumY)
	{
		*_pNumX = m_NumX;
		*_pNumY = m_NumY;
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

	void Control();
	void DrawBuildBox();

	static const D3DXVECTOR2			m_BuildBoxPos;
	static const D3DXVECTOR2			m_BuildBoxSize;
	static const int					m_BuilBoxNumX;		//!< x方向にある建設BOXの数
	static const int					m_BuilBoxNumY;		//!< y方向にある建設BOXの数
	FieldMessenger*						m_pFieldMessenger;
	STATE								m_State;
	HINSTANCE							m_hInstance;
	std::vector<HouseBuildBox*>			m_pHouseBuildBox;
	int									m_IsSelectBoxIndex;	//!< 選択されているBuildBoxのインデックス
	int									m_NumX;
	int									m_NumY;

};


#endif // !HOUSEBUILDMANAGER_H
