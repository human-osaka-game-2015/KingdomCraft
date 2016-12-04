#ifndef DX9MANAGER_H
#define DX9MANAGER_H
#include <d3d9.h>
#include <d3dx9.h>


class DX9Manager
{
public:
	~DX9Manager();

	static void Create()
	{
		if (m_pDX9Manager == NULL)
		{
			m_pDX9Manager = new DX9Manager();
		}
	}

	static DX9Manager* GetInstance()
	{
		return m_pDX9Manager;
	}

	static void Delete()
	{
		delete m_pDX9Manager;
		m_pDX9Manager = NULL;
	}

	bool Init(HWND _hwnd);
	void Release();

	inline LPDIRECT3DDEVICE9 GetDevice()
	{
		return m_pDevice;
	}


private:
	DX9Manager();
	bool InitDevice();
	void ReleaseDevice();

	static DX9Manager*		m_pDX9Manager;
	LPDIRECT3D9				m_pDirect9;
	LPDIRECT3DDEVICE9		m_pDevice;
	D3DPRESENT_PARAMETERS	m_D3dpp;
	HWND					m_hwnd;

};

#endif // DX9MANAGER_H