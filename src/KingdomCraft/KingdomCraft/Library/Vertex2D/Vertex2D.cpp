/**
 * @file   Vertex2D.h
 * @brief  Vertex2Dクラスのcppファイル
 * @author kotani
 */
#include "Vertex2D.h"
#include <Windows.h>
#define VERTEX_NUM 4
#define COLORMASK 0xffffffff //抜き色

Vertex2D::Vertex2D(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, HWND _hwnd) :
m_pDevice(_pDevice),
m_pDeviceContext(_pDeviceContext),
m_hWnd(_hwnd),
m_pVertexShader(NULL),
m_pPixelShader(NULL),
m_pVertexLayout(NULL),
m_pConstantBuffer(NULL),
m_pBlendState(NULL)
{
}

Vertex2D::~Vertex2D()
{
}

void Vertex2D::Release()
{
	ReleaseConstantBuffer();
	ReleaseSamplerState();
	ReleaseBlendState();
	ReleasePixelShader();
	ReleaseVertexLayout();
	ReleaseVertexShader();
}

bool Vertex2D::Init(RECT* _pRectSize, D3DXVECTOR2* _pUV)
{
	RECT WindowRect;
	GetWindowRect(m_hWnd, &WindowRect);
	m_WindowWidth = WindowRect.right - WindowRect.left;
	m_WindowHeight = WindowRect.bottom - WindowRect.top;

	if (!InitVertexShader()) return false;

	if (!CreateVertexLayout())
	{
		ReleaseVertexShader();
		return false;
	}

	if (!InitPixelShader())
	{
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!InitBlendState())
	{
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!InitSamplerState())
	{
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!InitVertexBuffer(_pRectSize, _pUV))
	{
		ReleaseSamplerState();
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	if (!InitConstantBuffer())
	{
		ReleaseSamplerState();
		ReleaseBlendState();
		ReleasePixelShader();
		ReleaseVertexLayout();
		ReleaseVertexShader();
		return false;
	}

	return true;
}


void Vertex2D::Draw(D3DXVECTOR2* _pDrawPos,float _alpha, D3DXVECTOR3* _pScale, float _angle)
{
	D3DXMATRIX matWorld	,matTranslate ,matRotate;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixScaling(&matWorld, _pScale->x, _pScale->y, _pScale->z);
	D3DXMatrixRotationZ(&matRotate, _angle);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matRotate);
	D3DXMatrixTranslation(&matTranslate, _pDrawPos->x, _pDrawPos->y, 0);
	D3DXMatrixMultiply(&matWorld, &matWorld, &matTranslate);
	//使用するシェーダーのセット
	m_pDeviceContext->VSSetShader(m_pVertexShader, NULL, 0);
	m_pDeviceContext->PSSetShader(m_pPixelShader, NULL, 0);

	D3D11_MAPPED_SUBRESOURCE pData;
	SHADER_CONSTANT_BUFFER	 constantBuffer;
	if (SUCCEEDED(m_pDeviceContext->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &pData)))
	{
		constantBuffer.matWorld = matWorld;
		D3DXMatrixTranspose(&constantBuffer.matWorld, &constantBuffer.matWorld);
		//ビューポートサイズを渡す（クライアント領域の横と縦）
		constantBuffer.viewPort.x = m_WindowWidth;
		constantBuffer.viewPort.y = m_WindowHeight;

		constantBuffer.alpha.a = _alpha;

		memcpy_s(pData.pData, pData.RowPitch, (void*)(&constantBuffer), sizeof(constantBuffer));
		m_pDeviceContext->Unmap(m_pConstantBuffer, 0);
	}

	//このコンスタントバッファーをどのシェーダーで使うか
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pDeviceContext->PSSetConstantBuffers(0, 1, &m_pConstantBuffer);

	//頂点インプットレイアウトをセット
	m_pDeviceContext->IASetInputLayout(m_pVertexLayout);
	//プリミティブ・トポロジーをセット
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//テクスチャーをシェーダーに渡す
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureResourceView);
	
	//プリミティブをレンダリング
	m_pDeviceContext->Draw(VERTEX_NUM, 0);
}


bool Vertex2D::InitVertexBuffer(RECT* _pRectSize, D3DXVECTOR2* _pUV)
{
	Vertex vertex[] =
	{
		D3DXVECTOR3(-_pRectSize->left , -_pRectSize->top, 0.f)   , D3DXVECTOR2(_pUV[0].x, _pUV[0].y),
		D3DXVECTOR3(+_pRectSize->right, -_pRectSize->top, 0.f)   , D3DXVECTOR2(_pUV[1].x, _pUV[1].y),
		D3DXVECTOR3(-_pRectSize->left , +_pRectSize->bottom, 0.f), D3DXVECTOR2(_pUV[2].x, _pUV[2].y),
		D3DXVECTOR3(+_pRectSize->right, +_pRectSize->bottom, 0.f), D3DXVECTOR2(_pUV[3].x, _pUV[3].y)
	};

	//頂点バッファ作成
	D3D11_BUFFER_DESC BufferDesc;
	BufferDesc.ByteWidth = sizeof(Vertex) * VERTEX_NUM;
	BufferDesc.Usage = D3D11_USAGE_DEFAULT;
	BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferDesc.CPUAccessFlags = 0;
	BufferDesc.MiscFlags = 0;
	BufferDesc.StructureByteStride = sizeof(float);

	D3D11_SUBRESOURCE_DATA InitVertexData;
	InitVertexData.pSysMem = vertex;
	ID3D11Buffer* pBuffer;
	if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &InitVertexData, &pBuffer)))
	{
		MessageBox(m_hWnd, TEXT("VertexBufferの生成に失敗しました"), TEXT("Error"), MB_ICONSTOP);
		return false;
	}

	//バーテックスバッファーをセット
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &pBuffer, &stride, &offset);
	pBuffer->Release();
	return true;
}

bool Vertex2D::InitVertexShader()
{
	ID3DBlob *pErrors = NULL;

	// 頂点シェーダーの読み込みとレイアウト作成
	if (FAILED(D3DX11CompileFromFile(
		TEXT("Library//Vertex2D//Vertex2D.hlsl"),
		NULL,
		NULL,
		"VS",
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&m_pVertexCompiledShader,
		&pErrors,
		NULL)))
	{
		MessageBox(0, TEXT("VertexShaderのコンパイルに失敗"), TEXT("Error"), MB_ICONSTOP);
		pErrors->Release();
		return false;
	}
	m_pDevice->CreateVertexShader(m_pVertexCompiledShader->GetBufferPointer(), m_pVertexCompiledShader->GetBufferSize(), NULL, &m_pVertexShader);
	return true;
}

void Vertex2D::ReleaseVertexShader()
{
	if (m_pVertexShader != NULL)
	{
		m_pVertexShader->Release();
		m_pVertexShader = NULL;
	}
	if (m_pVertexCompiledShader != NULL)
	{
		m_pVertexCompiledShader->Release();
		m_pVertexCompiledShader = NULL;
	}
}

bool Vertex2D::InitPixelShader()
{
	ID3DBlob* pCompiledShader = NULL;
	ID3DBlob *pErrors = NULL;
	m_pPixelShader = NULL;
	if (FAILED(D3DX11CompileFromFile(
		TEXT("Library//Vertex2D//Vertex2D.hlsl"),
		NULL,
		NULL,
		"PS",
		"ps_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pErrors,
		NULL)))
	{
		MessageBox(m_hWnd, TEXT("PixelShaderのコンパイルに失敗"), TEXT("Error"), MB_ICONSTOP);
		pErrors->Release();
		return false;
	}
	m_pDevice->CreatePixelShader(pCompiledShader->GetBufferPointer(), pCompiledShader->GetBufferSize(), NULL, &m_pPixelShader);
	pCompiledShader->Release();
	return true;
}

void Vertex2D::ReleasePixelShader()
{
	if (m_pPixelShader != NULL)
	{
		m_pPixelShader->Release();
		m_pPixelShader = NULL;
	}
}

bool Vertex2D::CreateVertexLayout()
{
	//頂点レイアウト定義
	D3D11_INPUT_ELEMENT_DESC InElementDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	//頂点インプットレイアウトを作成
	if (FAILED(m_pDevice->CreateInputLayout(
		InElementDesc,
		sizeof(InElementDesc) / sizeof(InElementDesc[0]),
		m_pVertexCompiledShader->GetBufferPointer(),
		m_pVertexCompiledShader->GetBufferSize(),
		&m_pVertexLayout)))
	{
		MessageBox(m_hWnd, TEXT("CreateInputLayoutに失敗"), TEXT("Error"), MB_ICONSTOP);
		return false;
	}

	return true;
}

void Vertex2D::ReleaseVertexLayout()
{
	if (m_pVertexLayout != NULL)
	{
		m_pVertexLayout->Release();
		m_pVertexLayout = NULL;
	}
}

bool Vertex2D::InitBlendState()
{
	//アルファブレンド用ブレンドステート作成
	D3D11_BLEND_DESC BlendDesc;
	ZeroMemory(&BlendDesc, sizeof(D3D11_BLEND_DESC));
	BlendDesc.IndependentBlendEnable = false;
	BlendDesc.AlphaToCoverageEnable = false;
	BlendDesc.RenderTarget[0].BlendEnable = true;
	BlendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;

	if (FAILED(m_pDevice->CreateBlendState(&BlendDesc, &m_pBlendState)))
	{
		MessageBox(m_hWnd, TEXT("CreateBlendStateに失敗しました"), TEXT("Error"), MB_ICONSTOP);
		return false;
	}

	m_pDeviceContext->OMSetBlendState(m_pBlendState, NULL, COLORMASK);
	return true;
}

void Vertex2D::ReleaseBlendState()
{
	if (m_pBlendState != NULL)
	{
		m_pBlendState->Release();
		m_pBlendState = NULL;
	}
}

bool Vertex2D::InitSamplerState()
{
	//テクスチャー用サンプラー作成
	D3D11_SAMPLER_DESC SamDesc;
	ZeroMemory(&SamDesc, sizeof(D3D11_SAMPLER_DESC));
	SamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	SamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	SamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;

	if (FAILED(m_pDevice->CreateSamplerState(&SamDesc, &m_pSampler)))
	{
		MessageBox(m_hWnd, TEXT("CreateSamplerStateに失敗しました"), TEXT("Error"), MB_ICONSTOP);
		return false;
	}
	return true;
}

void Vertex2D::ReleaseSamplerState()
{
	if (m_pSampler != NULL)
	{
		m_pSampler->Release();
		m_pSampler = NULL;
	}
}

bool Vertex2D::InitConstantBuffer()
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ZeroMemory(&ConstantBufferDesc, sizeof(D3D11_BUFFER_DESC));
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.StructureByteStride = 0;
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;

	if (FAILED(m_pDevice->CreateBuffer(&ConstantBufferDesc, NULL, &m_pConstantBuffer)))
	{
		MessageBox(m_hWnd, TEXT("ConstantBufferの生成に失敗しました"), TEXT("Error"), MB_ICONSTOP);
		return false;
	}
	return true;
}

void Vertex2D::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}