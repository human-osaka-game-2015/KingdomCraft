#include "DX11Manager.h"


DX11Manager* DX11Manager::m_pDX11Manager = NULL;

DX11Manager::DX11Manager()
{
	
}

DX11Manager::~DX11Manager()
{
	
}

bool DX11Manager::Init(HWND _hWnd)
{
	m_hWnd = _hWnd;
	GetWindowRect(m_hWnd, &m_WindowRect);

	if (!InitDevice())
	{
		MessageBox(m_hWnd, TEXT("InitDeviceに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (!InitDisplay())
	{
		MessageBox(m_hWnd, TEXT("InitDisplayに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		ReleaseDevice();
		return false;
	}

	OutputDebugString(TEXT("DX11Managerの初期化に成功\n"));

	return true;
}

void DX11Manager::Release()
{
	ReleaseDisplay();
	ReleaseDevice();
}

void DX11Manager::BeginScene()
{
	float ClearColor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };

	m_pDeviceContext->ClearRenderTargetView(m_pRenderTargetView, ClearColor);
	m_pDeviceContext->ClearDepthStencilView(m_pDepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void DX11Manager::EndScene()
{
	m_pDXGISwapChain->Present(1, 0);
}

ID3D11Device* DX11Manager::GetDevice()
{
	return m_pDevice;
}

ID3D11DeviceContext* DX11Manager::GetDeviceContext()
{
	return m_pDeviceContext;
}

bool DX11Manager::InitDevice()
{
	if (FAILED(D3D11CreateDevice(
		NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		0,
		NULL,
		0,
		D3D11_SDK_VERSION,
		&m_pDevice,
		NULL,
		&m_pDeviceContext)))
	{
		return false;
		MessageBox(m_hWnd, TEXT("D3D11CreateDeviceに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
	}

	OutputDebugString(TEXT("デバイス生成成功\n"));
	
	return true;
}

bool DX11Manager::InitDisplay()
{
	if (FAILED(m_pDevice->QueryInterface(__uuidof(IDXGIDevice1), (void**)&m_pDXGI)))
	{
		MessageBox(m_hWnd, TEXT("DX11のインターフェイスの取得に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}
	OutputDebugString(TEXT("DX11のインターフェイス(グラフィック)の取得に成功しました\n"));

	if (FAILED(m_pDXGI->GetAdapter(&m_pAdapter)))
	{
		MessageBox(m_hWnd, TEXT("DX11のアダプターの取得に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDXGI->Release();
		return false;
	}
	OutputDebugString(TEXT("DX11アダプターの取得に成功しました\n"));

	m_pAdapter->GetParent(__uuidof(IDXGIFactory), (void**)&m_pDXGIFactory);
	if (m_pDXGIFactory == NULL)
	{
		MessageBox(m_hWnd, TEXT("DX11のファクトリーの取得に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}
	OutputDebugString(TEXT("DX11のファクトリー取得に成功しました\n"));

	if (FAILED(m_pDXGIFactory->MakeWindowAssociation(m_hWnd, 0)))
	{
		MessageBox(m_hWnd, TEXT("フルスクリーン化に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}
	OutputDebugString(TEXT("フルスクリーン対応に成功しました\n"));



	m_DXGISwapChainDesc.BufferDesc.Width = m_WindowRect.right - m_WindowRect.left;
	m_DXGISwapChainDesc.BufferDesc.Height = m_WindowRect.bottom - m_WindowRect.top;
	m_DXGISwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	m_DXGISwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	m_DXGISwapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	m_DXGISwapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	m_DXGISwapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	m_DXGISwapChainDesc.SampleDesc.Count = 1;
	m_DXGISwapChainDesc.SampleDesc.Quality = 0;
	m_DXGISwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	m_DXGISwapChainDesc.BufferCount = 1;
	m_DXGISwapChainDesc.OutputWindow = m_hWnd;
	m_DXGISwapChainDesc.Windowed = TRUE;
	m_DXGISwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	m_DXGISwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	if (FAILED(m_pDXGIFactory->CreateSwapChain(m_pDevice, &m_DXGISwapChainDesc, &m_pDXGISwapChain)))
	{
		MessageBox(m_hWnd, TEXT("スワップチェインの作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}
	OutputDebugString(TEXT("スワップチェインの作成に成功しました\n"));

	if (FAILED(m_pDXGISwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (void**)&m_pBackBuffer)))
	{
		MessageBox(m_hWnd, TEXT("スワップチェインのバックバッファ取得に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}
	OutputDebugString(TEXT("スワップチェインのバックバッファ取得に成功しました\n"));

	if (FAILED(m_pDevice->CreateRenderTargetView(m_pBackBuffer, NULL, &m_pRenderTargetView)))
	{
		MessageBox(m_hWnd, TEXT("描画ターゲット生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pBackBuffer->Release();
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}
	OutputDebugString(TEXT("描画ターゲット生成に成功しました\n"));


	m_DepthDesc.Width  = m_WindowRect.right - m_WindowRect.left;
	m_DepthDesc.Height = m_WindowRect.bottom - m_WindowRect.top;
	m_DepthDesc.MipLevels = 1;
	m_DepthDesc.ArraySize = 1;
	m_DepthDesc.Format = DXGI_FORMAT_D32_FLOAT;
	m_DepthDesc.SampleDesc.Count = 1;
	m_DepthDesc.SampleDesc.Quality = 0;
	m_DepthDesc.Usage = D3D11_USAGE_DEFAULT;
	m_DepthDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	m_DepthDesc.CPUAccessFlags = 0;
	m_DepthDesc.MiscFlags = 0;

	if (FAILED(m_pDevice->CreateTexture2D(&m_DepthDesc, NULL, &m_pDepthStencilBuffer)))
	{
		MessageBox(m_hWnd, TEXT("ステンシルビュー生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pRenderTargetView->Release();
		m_pBackBuffer->Release();
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}
	OutputDebugString(TEXT("ステンシルビュー生成に成功しました\n"));

	if (FAILED(m_pDevice->CreateDepthStencilView(m_pDepthStencilBuffer, NULL, &m_pDepthStencilView)))
	{
		MessageBox(m_hWnd, TEXT("ステンシルバッファ生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pDepthStencilBuffer->Release();
		m_pRenderTargetView->Release();
		m_pBackBuffer->Release();
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		return false;
	}
	OutputDebugString(TEXT("ステンシルバッファ生成に成功しました\n"));

	m_pDeviceContext->OMSetRenderTargets(1, &m_pRenderTargetView, m_pDepthStencilView);



	m_ViewPort.TopLeftX = 0;
	m_ViewPort.TopLeftY = 0;
	m_ViewPort.Width  = float(m_WindowRect.right - m_WindowRect.left);
	m_ViewPort.Height = float(m_WindowRect.bottom - m_WindowRect.top);
	m_ViewPort.MinDepth = 0.0f;
	m_ViewPort.MaxDepth = 1.0f;
	m_pDeviceContext->RSSetViewports(1, &m_ViewPort);


	m_RasterizerDesc =
	{
		D3D11_FILL_SOLID,
		D3D11_CULL_BACK,
		FALSE,
		0,
		0.0f,
		FALSE,
		FALSE,
		FALSE,
		FALSE,
		FALSE
	};

	if (FAILED(m_pDevice->CreateRasterizerState(&m_RasterizerDesc, &m_pRasterizerState)))
	{
		m_pDepthStencilView->Release();
		m_pDepthStencilBuffer->Release();
		m_pRenderTargetView->Release();
		m_pBackBuffer->Release();
		m_pDXGISwapChain->Release();
		m_pDXGIFactory->Release();
		m_pAdapter->Release();
		m_pDXGI->Release();
		MessageBox(m_hWnd, TEXT("RasterizerStateの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}
	OutputDebugString(TEXT("RasterizerStateの状態の生成に成功しました\n"));
	m_pDeviceContext->RSSetState(m_pRasterizerState);


	return true;
}

void DX11Manager::ReleaseDevice()
{
	m_pDeviceContext->Release();
	m_pDevice->Release();
}

void DX11Manager::ReleaseDisplay()
{
	m_pRasterizerState->Release();
	m_pDepthStencilView->Release();
	m_pDepthStencilBuffer->Release();
	m_pRenderTargetView->Release();
	m_pBackBuffer->Release();
	m_pDXGISwapChain->Release();
	m_pDXGIFactory->Release();
	m_pAdapter->Release();
	m_pDXGI->Release();
}
