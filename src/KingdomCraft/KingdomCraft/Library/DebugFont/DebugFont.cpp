#include "DebugFont.h"
#include <d3dx11.h>


DebugFont::DebugFont():
m_pDevice(NULL),
m_pDeviceContext(NULL),
m_pResourceView(NULL),
m_pConstantBuffer(NULL),
m_pVertexBuffer(NULL),
m_pVertexShader(NULL),
m_pLayout(NULL),
m_pPixelShader(NULL),
m_pSamplerState(NULL),
m_pBlendState(NULL),
m_pDepthStencilState(NULL)
{
}

DebugFont::~DebugFont()
{
}

bool DebugFont::Init(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, HWND _hWnd)
{
	m_pDevice = _pDevice;
	m_pDeviceContext = _pDeviceContext;
	m_hWnd = _hWnd;


	if (!InitResourceView())
	{
		MessageBox(m_hWnd, TEXT("InitResourceViewが失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (!InitConstantBuffer())
	{
		MessageBox(m_hWnd, TEXT("InitConstantBufferが失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		ReleaseResourceView();
		return false;
	}

	if (!InitShader())
	{
		MessageBox(m_hWnd, TEXT("InitShaderが失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		ReleaseConstantBuffer();
		ReleaseResourceView();
		return false;
	}

	if (!InitSamplerState())
	{
		MessageBox(m_hWnd, TEXT("InitSamplerStateが失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		ReleaseShader();
		ReleaseConstantBuffer();
		ReleaseResourceView();
		return false;
	}

	if (!InitBlendState())
	{
		MessageBox(m_hWnd, TEXT("InitBlendStateが失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		ReleaseSamplerState();
		ReleaseShader();
		ReleaseConstantBuffer();
		ReleaseResourceView();
		return false;
	}
	
	if (!InitDepthStencilState())
	{
		MessageBox(m_hWnd, TEXT("InitDepthStencilStateが失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		ReleaseBlendState();
		ReleaseSamplerState();
		ReleaseShader();
		ReleaseConstantBuffer();
		ReleaseResourceView();
		return false;
	}

	OutputDebugString(TEXT("DebugFontの初期化に成功しました\n"));

	return true;
}

void DebugFont::Release()
{
	ReleaseDepthStencilState();
	ReleaseBlendState();
	ReleaseSamplerState();
	ReleaseShader();
	ReleaseConstantBuffer();
	ReleaseResourceView();
}

bool DebugFont::InitFont(float _fontHeight, float _fontWidth, D3DXCOLOR _fontColor)
{
	m_FontWidth = _fontWidth;		// フォントの幅
	m_FontHeight = _fontHeight;     // フォントの高さ

	RECT WindowRect;
	GetWindowRect(m_hWnd, &WindowRect);
	m_WindowWidth = WindowRect.right - WindowRect.left;
	m_WindowHeight = WindowRect.bottom - WindowRect.top;

	FONT_VERTEX FontVertex[] =
	{
		D3DXVECTOR3(-m_WindowWidth / 2,					-m_WindowHeight / 2, 0),				_fontColor, 0, 0,
		D3DXVECTOR3(-m_WindowWidth / 2 + m_FontWidth,	-m_WindowHeight / 2, 0),				_fontColor, FONT_TU, 0,
		D3DXVECTOR3(-m_WindowWidth / 2,					-m_WindowHeight / 2 + m_FontHeight, 0), _fontColor, 0, 1,
		D3DXVECTOR3(-m_WindowWidth / 2 + m_FontWidth,	-m_WindowHeight / 2 + m_FontHeight, 0), _fontColor, FONT_TU, 1,
	};

	D3D11_BUFFER_DESC BufferDesc;
	ZeroMemory(&BufferDesc, sizeof(BufferDesc));
	BufferDesc.ByteWidth = sizeof(FontVertex);         
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;				
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;	
	BufferDesc.CPUAccessFlags = 0;                     
	BufferDesc.MiscFlags = 0;							

	D3D11_SUBRESOURCE_DATA ResourceData;
	ZeroMemory(&ResourceData, sizeof(ResourceData));
	ResourceData.pSysMem = (void*)FontVertex;			
	ResourceData.SysMemPitch = 0;
	ResourceData.SysMemSlicePitch = 0;

	if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &ResourceData, &m_pVertexBuffer)))
	{
		MessageBox(m_hWnd, TEXT("頂点データの作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	return true;
}

void DebugFont::DrawFont(D3DXVECTOR2* _pDrawPos, char* _pStr)
{
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->HSSetShader(NULL, NULL, 0);
	m_pDeviceContext->DSSetShader(NULL, NULL, 0);
	m_pDeviceContext->GSSetShader(NULL, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSamplerState);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pResourceView);
	m_pDeviceContext->CSSetShader(NULL, NULL, 0);

	m_pDeviceContext->OMSetBlendState(m_pBlendState, 0, 0xffffffff);
	m_pDeviceContext->OMSetDepthStencilState(m_pDepthStencilState, 0);

	UINT stride = sizeof(FONT_VERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);
	m_pDeviceContext->IASetInputLayout(m_pLayout);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);


	D3D11_MAPPED_SUBRESOURCE mappedResource;
	CONSTANT_BUFFER* cBuffer;
	D3DXMATRIX matTranslation;
	for (int i = 0; i < (int)strlen(_pStr); i++)
	{
		m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);	
		cBuffer = (CONSTANT_BUFFER*)(mappedResource.pData);

		D3DXMATRIX Proj(
			2.0f / m_WindowWidth, 0.0f, 0.0f, 0.0f,
			0.0f, -2.0f / m_WindowHeight, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
		cBuffer->MatWVP = Proj;

		cBuffer->TexelOffset.x = (float)(_pStr[i] - 32) * FONT_TU;
		cBuffer->TexelOffset.y = 0.0f;
		cBuffer->TexelOffset.z = 0.0f;
		cBuffer->TexelOffset.w = 0.0f;

		cBuffer->PosOffset.x = i * m_FontWidth + _pDrawPos->x;
		cBuffer->PosOffset.y = _pDrawPos->y;
		cBuffer->PosOffset.z = 0;
		cBuffer->PosOffset.w = 0;

		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

		m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

		m_pDeviceContext->Draw(4, 0);
	}
}

bool DebugFont::InitResourceView()
{
	D3DX11_IMAGE_LOAD_INFO LoadInfo;
	ZeroMemory(&LoadInfo, sizeof(D3DX11_IMAGE_LOAD_INFO));
	LoadInfo.Width = D3DX11_DEFAULT;
	LoadInfo.Height = D3DX11_DEFAULT;
	LoadInfo.Depth = D3DX11_DEFAULT;
	LoadInfo.FirstMipLevel = D3DX11_DEFAULT;
	LoadInfo.MipLevels = 1;
	LoadInfo.Usage = D3D11_USAGE_DEFAULT;
	LoadInfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	LoadInfo.CpuAccessFlags = 0;
	LoadInfo.MiscFlags = 0;
	LoadInfo.Format = DXGI_FORMAT_FROM_FILE;
	LoadInfo.Filter = D3DX11_FILTER_POINT;
	LoadInfo.MipFilter = D3DX11_FILTER_POINT;
	LoadInfo.pSrcInfo = NULL;

	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		TEXT("Library//DebugFont//Resource//Font.png"),
		&LoadInfo,
		NULL,
		&m_pResourceView,
		NULL)))
	{
		MessageBox(m_hWnd, TEXT("テクスチャリーソースビューの生成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	OutputDebugString(TEXT("DebugFont フォントテクスチャのResourceViewの生成に成功しました\n"));

	return true;
}

bool DebugFont::InitConstantBuffer()
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ZeroMemory(&ConstantBufferDesc, sizeof(ConstantBufferDesc));
	ConstantBufferDesc.ByteWidth = sizeof(CONSTANT_BUFFER);         // バッファのサイズ
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;					// 動的リソースを指定(CPUによる書き込みとGPUによる読み取りがされる)
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;		// バッファの種類(定数バッファを指定)
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;		// CPUのアクセス(CPU による書き込みを許可)
	ConstantBufferDesc.MiscFlags = 0;								// その他のフラグは設定しない

	if (FAILED(m_pDevice->CreateBuffer(&ConstantBufferDesc, NULL, &m_pConstantBuffer)))
	{
		MessageBox(m_hWnd, TEXT("コンスタントバッファの作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	OutputDebugString(TEXT("DebugFont 定数バッファの生成に成功しました\n"));

	return true;
}

bool DebugFont::InitShader()
{
	if (!InitVertexShader())
	{
		MessageBox(m_hWnd, TEXT("InitVertexShaderが失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	if (!InitPixelShader())
	{
		MessageBox(m_hWnd, TEXT("InitPixelShaderが失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		ReleaseVertexShader();
		return false;
	}

	OutputDebugString(TEXT("DebugFont シェーダーの初期化に成功しました\n"));

	return true;
}

bool DebugFont::InitVertexShader()
{
	ID3DBlob* pCompiledVertexShader = NULL;
	ID3DBlob* pVertexShaderErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("Library//DebugFont//Effect//DebugFont.fx"),
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledVertexShader,
		&pVertexShaderErrors,
		NULL)))
	{
		MessageBox(m_hWnd, TEXT("VertexShaderのコンパイルに失敗"), TEXT("エラー"), MB_ICONSTOP);
		if (pVertexShaderErrors != NULL) pVertexShaderErrors->Release();
		return false;
	}

	if (pVertexShaderErrors != NULL) pVertexShaderErrors->Release();



	if (FAILED(m_pDevice->CreateVertexShader(
		pCompiledVertexShader->GetBufferPointer(),
		pCompiledVertexShader->GetBufferSize(),
		NULL,
		&m_pVertexShader)))
	{
		MessageBox(m_hWnd, TEXT("VertexShaderの作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		pCompiledVertexShader->Release();
		return false;
	}



	D3D11_INPUT_ELEMENT_DESC Layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	if (FAILED(m_pDevice->CreateInputLayout(
		Layout,
		sizeof(Layout) / sizeof(Layout[0]),
		pCompiledVertexShader->GetBufferPointer(),
		pCompiledVertexShader->GetBufferSize(),
		&m_pLayout)))
	{
		MessageBox(m_hWnd, TEXT("InputLayoutの作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		m_pVertexShader->Release();
		pCompiledVertexShader->Release();
		return false;
	}

	pCompiledVertexShader->Release();

	OutputDebugString(TEXT("DebugFont バーテックスシェーダーの初期化に成功しました\n"));

	return true;
}

bool DebugFont::InitPixelShader()
{
	ID3DBlob* pCompiledPixelShader = NULL;
	ID3DBlob* pPixelShaderErrors = NULL;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("Library//DebugFont//Effect//DebugFont.fx"),
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledPixelShader,
		&pPixelShaderErrors,
		NULL)))
	{
		MessageBox(m_hWnd, TEXT("PixelShaderのコンパイルに失敗"), TEXT("エラー"), MB_ICONSTOP);
		if (pPixelShaderErrors != NULL) pPixelShaderErrors->Release();
		return false;
	}

	if (pPixelShaderErrors != NULL) pPixelShaderErrors->Release();



	if (FAILED(m_pDevice->CreatePixelShader(
		pCompiledPixelShader->GetBufferPointer(),
		pCompiledPixelShader->GetBufferSize(),
		NULL,
		&m_pPixelShader)))
	{
		MessageBox(m_hWnd, TEXT("PixelShaderのコンパイルに失敗"), TEXT("エラー"), MB_ICONSTOP);
		pCompiledPixelShader->Release();
		return false;
	}

	OutputDebugString(TEXT("DebugFont ピクセルシェーダーの初期化に成功しました\n"));

	return true;
}

bool DebugFont::InitSamplerState()
{
	D3D11_SAMPLER_DESC samplerDesc;
	ZeroMemory(&samplerDesc, sizeof(samplerDesc));
	samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;	// サンプリング時に使用するフィルタ。ここでは異方性フィルターを使用する。
	samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;		// 0 ～ 1 の範囲外にある u テクスチャー座標の描画方法
	samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;		// 0 ～ 1 の範囲外にある v テクスチャー座標の描画方法
	samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;		// 0 ～ 1 の範囲外にある w テクスチャー座標の描画方法
	samplerDesc.MipLODBias = 0;								// 計算されたミップマップ レベルからのバイアス
	samplerDesc.MaxAnisotropy = 0;							// サンプリングに異方性補間を使用している場合の限界値。有効な値は 1 ～ 16 。
	samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;	// 比較オプション。
	for (int i = 0; i < 4; i++)
	{
		samplerDesc.BorderColor[i] = 0.0f;					// 境界色
	}
	samplerDesc.MinLOD = 0;									// アクセス可能なミップマップの下限値
	samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;					// アクセス可能なミップマップの上限値

	if (FAILED(m_pDevice->CreateSamplerState(&samplerDesc, &m_pSamplerState)))
	{
		MessageBox(m_hWnd, TEXT("サンプラーステートの生成に失敗"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	OutputDebugString(TEXT("DebugFont サンプラーステートの生成に成功しました\n"));

	return true;
}

bool DebugFont::InitBlendState()
{
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(BlendDesc));
	BlendDesc.AlphaToCoverageEnable = FALSE;
	BlendDesc.IndependentBlendEnable = FALSE;
	BlendDesc.RenderTarget[0].BlendEnable = TRUE;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState)))
	{
		MessageBox(m_hWnd, TEXT("ブレンドステートの生成に失敗"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	OutputDebugString(TEXT("DebugFont ブレンドステートの生成に成功しました\n"));

	return true;
}

bool DebugFont::InitDepthStencilState()
{
	D3D11_DEPTH_STENCIL_DESC ddsDesc;
	ZeroMemory(&ddsDesc, sizeof(ddsDesc));
	ddsDesc.DepthEnable = FALSE;
	ddsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	ddsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	ddsDesc.StencilEnable = FALSE;

	if (FAILED(m_pDevice->CreateDepthStencilState(&ddsDesc, &m_pDepthStencilState)))
	{
		OutputDebugString(TEXT("DebugFont デプスステンシルステートの生成に失敗\n"));
		return false;
	}

	OutputDebugString(TEXT("DebugFont デプスステンシルステートの生成に成功しました\n"));

	return true;
}

void DebugFont::ReleaseResourceView()
{
	m_pResourceView->Release();
}

void DebugFont::ReleaseConstantBuffer()
{
	m_pConstantBuffer->Release();
}

void DebugFont::ReleaseShader()
{
	ReleaseVertexShader();
	ReleasePixelShader();
}

void DebugFont::ReleaseVertexShader()
{
	m_pLayout->Release();
	m_pVertexShader->Release();
}

void DebugFont::ReleasePixelShader()
{
	m_pPixelShader->Release();
}

void DebugFont::ReleaseSamplerState()
{
	m_pSamplerState->Release();
}

void DebugFont::ReleaseBlendState()
{
	m_pBlendState->Release();
}

void DebugFont::ReleaseDepthStencilState()
{
	m_pDepthStencilState->Release();
}
