/**
 * @file   DX11Manager.h
 * @brief  DX11Managerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef DX11MANAGER_H
#define DX11MANAGER_H

#include <Windows.h>
#include <d3d11.h>
#include <d3dx11.h>	

/**
 * @brief  DirectX11関係のオブジェクトを管理しているクラス
 *
 * DirectX11のデバイスやデバイスコンテキストなどを管理している。\n
 * デバイスなどを利用して描画前のバッファのクリアやバッファの表示なども行う。\n
 * 複数実体を作る必要がないのでシングルトンにしている。
 */
class DX11Manager
{
public:
	~DX11Manager();

	/**
	 * インスタンスを生成
	 */
	static void Create()
	{
		if (m_pDX11Manager == NULL)
		{
			m_pDX11Manager = new DX11Manager();
		}
	}

	/**
	 * インスタンスを取得する
	 * @return インスタンスが返る
	 */
	static DX11Manager* GetInstance()
	{
		return m_pDX11Manager;
	}

	/**
	 * DX11Managerインスタンスを破棄する
	 */
	static void Delete()
	{
		delete m_pDX11Manager;
		m_pDX11Manager = NULL;
	}

	/**
	 * DX11Managerの初期化関数
	 * @param[in] _hWnd DX11Managerが対応するウィンドウのハンドル
	 * @return 初期化に成功したらtrue
	 */
	bool Init(HWND _hWnd);

	/**
	 * DX11Managerの解放関数
	 */
	void Release();

	/**
	 * 描画前処理を行う関数
	 */
	void BeginScene();

	/**
	 * 描画後処理を行う関数
	 */	
	void EndScene();
	
	/**
	 * DirectX11デバイスを取得する関数
	 * @return DirectX11デバイス
	 */
	ID3D11Device* GetDevice();

	/**
	 * DirectX11デバイスコンテキストを取得する関数
	 * @return DirectX11デバイスコンテキスト
	 */
	ID3D11DeviceContext* GetDeviceContext();

private:
	DX11Manager();
	bool InitDevice();
	bool InitDisplay();
	void ReleaseDevice();
	void ReleaseDisplay();

	static DX11Manager*		m_pDX11Manager;

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