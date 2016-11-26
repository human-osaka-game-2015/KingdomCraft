#include "DX9Manager.h"

DX9Manager* DX9Manager::m_pDX9Manager = NULL;


DX9Manager::DX9Manager()
{
}

DX9Manager::~DX9Manager()
{
}

bool DX9Manager::Init(HWND _hwnd)
{
	m_hwnd = _hwnd;

	if (!InitDevice())
	{
		return false;
	}

	return true;
}

void DX9Manager::Release()
{
	ReleaseDevice();
}

bool DX9Manager::InitDevice()
{
	m_pDirect9 = Direct3DCreate9(D3D_SDK_VERSION);

	RECT WindowRect;
	GetWindowRect(m_hwnd, &WindowRect);

	m_D3dpp.BackBufferWidth = WindowRect.right - WindowRect.left;
	m_D3dpp.BackBufferHeight = WindowRect.bottom - WindowRect.top;
	m_D3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	m_D3dpp.BackBufferCount = 0;
	m_D3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
	m_D3dpp.MultiSampleQuality = 0;
	m_D3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	m_D3dpp.hDeviceWindow = NULL;
	m_D3dpp.Windowed = TRUE;
	m_D3dpp.EnableAutoDepthStencil = TRUE;
	m_D3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
	m_D3dpp.Flags = 0;
	m_D3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
	m_D3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;

	if (FAILED(m_pDirect9->CreateDevice(
		D3DADAPTER_DEFAULT, 
		D3DDEVTYPE_HAL, m_hwnd, 
		D3DCREATE_HARDWARE_VERTEXPROCESSING, 
		&m_D3dpp, 
		&m_pDevice)))
	{
		m_pDirect9->Release();
		return false;
	}

	return true;
}

void DX9Manager::ReleaseDevice()
{
	m_pDevice->Release();
	m_pDirect9->Release();
}

