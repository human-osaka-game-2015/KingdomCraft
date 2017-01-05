/**
 * @file   DebugFont.cpp
 * @brief  DebugFontクラスの実装
 * @author morimoto
 */
#include "DebugFont.h"


//----------------------------------------------------------------------------------------------------
// Static Private Variables
//----------------------------------------------------------------------------------------------------

const float DebugFont::m_DebugFontTu = 1.0f / 95;
const int DebugFont::m_SpaceAsciiCode = 32;


//----------------------------------------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------------------------------------

DebugFont::DebugFont(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext) :
m_pDevice(_pDevice),
m_pDeviceContext(_pDeviceContext),
m_pResourceView(NULL),
m_pConstantBuffer(NULL),
m_pVertexBuffer(NULL),
m_pVertexShader(NULL),
m_pLayout(NULL),
m_pPixelShader(NULL),
m_pSamplerState(NULL),
m_pBlendState(NULL),
m_pDepthStencilState(NULL),
m_hWnd(NULL),
m_FontHeight(0),
m_FontWidth(0),
m_WindowHeight(0),
m_WindowWidth(0)
{
}

DebugFont::~DebugFont()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool DebugFont::Init(HWND _hWnd)
{
	if (m_pResourceView != NULL)
	{
		MessageBox(_hWnd, TEXT("DebugFontクラスはすでに初期化されています"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

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
	ReleaseFont();
	ReleaseDepthStencilState();
	ReleaseBlendState();
	ReleaseSamplerState();
	ReleaseShader();
	ReleaseConstantBuffer();
	ReleaseResourceView();
}

bool DebugFont::InitFont(float _fontHeight, float _fontWidth, D3DXCOLOR _fontColor)
{
	m_FontWidth = _fontWidth;
	m_FontHeight = _fontHeight;

	RECT WindowRect;
	GetWindowRect(m_hWnd, &WindowRect);
	m_WindowWidth = static_cast<float>(WindowRect.right - WindowRect.left);
	m_WindowHeight = static_cast<float>(WindowRect.bottom - WindowRect.top);

	FONT_VERTEX FontVertex[] =
	{
		D3DXVECTOR3(-m_WindowWidth / 2,					-m_WindowHeight / 2, 0),				_fontColor, D3DXVECTOR2(0,				0),
		D3DXVECTOR3(-m_WindowWidth / 2 + m_FontWidth,	-m_WindowHeight / 2, 0),				_fontColor, D3DXVECTOR2(m_DebugFontTu,	0),
		D3DXVECTOR3(-m_WindowWidth / 2,					-m_WindowHeight / 2 + m_FontHeight, 0), _fontColor, D3DXVECTOR2(0,				1),
		D3DXVECTOR3(-m_WindowWidth / 2 + m_FontWidth,	-m_WindowHeight / 2 + m_FontHeight, 0), _fontColor, D3DXVECTOR2(m_DebugFontTu,	1),
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
	ResourceData.pSysMem = reinterpret_cast<void*>(FontVertex);
	ResourceData.SysMemPitch = 0;
	ResourceData.SysMemSlicePitch = 0;

	if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &ResourceData, &m_pVertexBuffer)))
	{
		MessageBox(m_hWnd, TEXT("頂点データの作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	return true;
}

void DebugFont::DrawFont(const D3DXVECTOR2* _pDrawPos, LPCTSTR _pStr)
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


	D3D11_MAPPED_SUBRESOURCE MappedResource;
	CONSTANT_BUFFER* pConstantBuffer;
	for (int i = 0; i < static_cast<int>(strlen(_pStr)); i++)
	{
		m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &MappedResource);
		pConstantBuffer = reinterpret_cast<CONSTANT_BUFFER*>(MappedResource.pData);

		D3DXMATRIX Proj(
			2.0f / m_WindowWidth, 0.0f, 0.0f, 0.0f,
			0.0f, -2.0f / m_WindowHeight, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f);
		pConstantBuffer->MatWVP = Proj;

		pConstantBuffer->TexelOffset.x = static_cast<float>(_pStr[i] - m_SpaceAsciiCode) * m_DebugFontTu;
		pConstantBuffer->TexelOffset.y = 0.0f;
		pConstantBuffer->TexelOffset.z = 0.0f;
		pConstantBuffer->TexelOffset.w = 0.0f;

		pConstantBuffer->PosOffset.x = i * m_FontWidth + _pDrawPos->x;
		pConstantBuffer->PosOffset.y = _pDrawPos->y;
		pConstantBuffer->PosOffset.z = 0;
		pConstantBuffer->PosOffset.w = 0;

		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);

		m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
		m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

		m_pDeviceContext->Draw(4, 0);
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

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
		TEXT("Library\\DebugFont\\Resource\\Font.png"),
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
	ConstantBufferDesc.ByteWidth = sizeof(CONSTANT_BUFFER);
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;

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
		TEXT("Library\\DebugFont\\Effect\\DebugFont.fx"),
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
		{ "POSITION",	0, DXGI_FORMAT_R32G32B32_FLOAT,		0, 0,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR",		0, DXGI_FORMAT_R32G32B32A32_FLOAT,	0, 12,	D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD",	0, DXGI_FORMAT_R32G32_FLOAT,		0, 28,	D3D11_INPUT_PER_VERTEX_DATA, 0 }
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
		TEXT("Library\\DebugFont\\Effect\\DebugFont.fx"),
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
	D3D11_SAMPLER_DESC SamplerDesc;
	ZeroMemory(&SamplerDesc, sizeof(SamplerDesc));
	SamplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	SamplerDesc.MipLODBias = 0;
	SamplerDesc.MaxAnisotropy = 0;
	SamplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
	for (int i = 0; i < 4; i++)
	{
		SamplerDesc.BorderColor[i] = 0.0f;
	}
	SamplerDesc.MinLOD = 0;
	SamplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

	if (FAILED(m_pDevice->CreateSamplerState(&SamplerDesc, &m_pSamplerState)))
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
	D3D11_DEPTH_STENCIL_DESC DepthStencilDesc;
	ZeroMemory(&DepthStencilDesc, sizeof(DepthStencilDesc));
	DepthStencilDesc.DepthEnable = FALSE;
	DepthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	DepthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	DepthStencilDesc.StencilEnable = FALSE;

	if (FAILED(m_pDevice->CreateDepthStencilState(&DepthStencilDesc, &m_pDepthStencilState)))
	{
		OutputDebugString(TEXT("DebugFont デプスステンシルステートの生成に失敗\n"));
		return false;
	}

	OutputDebugString(TEXT("DebugFont デプスステンシルステートの生成に成功しました\n"));

	return true;
}

void DebugFont::ReleaseResourceView()
{
	if (m_pResourceView != NULL)
	{
		m_pResourceView->Release();
		m_pResourceView = NULL;
	}
}

void DebugFont::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}

void DebugFont::ReleaseShader()
{
	ReleaseVertexShader();
	ReleasePixelShader();
}

void DebugFont::ReleaseVertexShader()
{
	if (m_pLayout != NULL)
	{
		m_pLayout->Release();
		m_pLayout = NULL;
	}

	if (m_pVertexShader != NULL)
	{
		m_pVertexShader->Release();
		m_pVertexShader = NULL;
	}
}

void DebugFont::ReleasePixelShader()
{
	if (m_pPixelShader != NULL)
	{
		m_pPixelShader->Release();
		m_pPixelShader = NULL;
	}
}

void DebugFont::ReleaseSamplerState()
{
	if (m_pSamplerState != NULL)
	{
		m_pSamplerState->Release();
		m_pSamplerState = NULL;
	}
}

void DebugFont::ReleaseBlendState()
{
	if (m_pBlendState != NULL)
	{
		m_pBlendState->Release();
		m_pBlendState = NULL;
	}
}

void DebugFont::ReleaseDepthStencilState()
{
	if (m_pDepthStencilState != NULL)
	{
		m_pDepthStencilState->Release();
		m_pDepthStencilState = NULL;
	}
}

void DebugFont::ReleaseFont()
{
	if (m_pVertexBuffer != NULL)
	{
		m_pVertexBuffer->Release();
		m_pVertexBuffer = NULL;
	}
}
