#ifndef DX11MANAGER_H
#define DX11MANAGER_H

#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>	

class DX11Manager
{
public:
	DX11Manager();
	~DX11Manager();

	bool Init(HWND _hWnd);
	void Release();

	void BeginScene();
	void EndScene();

	ID3D11Device* GetDevice();
	ID3D11DeviceContext* GetDeviceContext();


private:
	bool InitDevice();
	bool InitDisplay();
	void ReleaseDevice();
	void ReleaseDisplay();

	ID3D11Device*			m_pDevice;			
	ID3D11DeviceContext*	m_pDeviceContext;

	IDXGIDevice1*			m_pDXGI;			
	IDXGIAdapter*			m_pAdapter;			
	IDXGIFactory*			m_pDXGIFactory;

	IDXGISwapChain*			m_pDXGISwapChain;
	DXGI_SWAP_CHAIN_DESC	m_DXGISwapChainDesc;

	ID3D11Texture2D*		m_pBackBuffer;
	ID3D11RenderTargetView* m_pRenderTargetView;

	ID3D11Texture2D*		m_pDepthStencilBuffer;
	D3D11_TEXTURE2D_DESC	m_DepthDesc;
	ID3D11DepthStencilView* m_pDepthStencilView;

	D3D11_VIEWPORT			m_ViewPort;

	ID3D11RasterizerState*  m_pRasterizerState;
	D3D11_RASTERIZER_DESC	m_RasterizerDesc;

	HWND					m_hWnd;
	RECT					m_WindowRect;

};

#endif