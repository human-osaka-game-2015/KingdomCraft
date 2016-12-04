#ifndef DEBUGFONT_H
#define DEBUGFONT_H
#include <d3d9.h>
#include <d3dx9.h>


class DebugFont
{
public:
	DebugFont();
	~DebugFont();

	static void Create()
	{
		if (m_pDebugFont == NULL)
		{
			m_pDebugFont = new DebugFont();
		}
	}

	static DebugFont* GetInstance()
	{
		return m_pDebugFont;
	}

	static void Delete()
	{
		delete m_pDebugFont;
		m_pDebugFont = NULL;
	}


	bool Init(LPDIRECT3DDEVICE9 _pDevice, int _fontSize);
	void Release();

	void DrawFont(RECT _rect, LPCTSTR _font);

private:
	static DebugFont* m_pDebugFont;
	LPD3DXFONT m_pFont;


};

#endif // DEBUGFONT_H