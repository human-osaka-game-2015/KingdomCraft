/**
 * @file   TextureManager.cpp
 * @brief  TextureManagerクラスの実装
 * @author morimoto
 */
#include "TextureManager.h"


//----------------------------------------------------------------------------------------------------
// Static Public Variables
//----------------------------------------------------------------------------------------------------

const int TextureManager::m_InvalidIndex = 0;


//----------------------------------------------------------------------------------------------------
// Static Private Variables
//----------------------------------------------------------------------------------------------------

TextureManager* TextureManager::m_pTextureManager = NULL;


//----------------------------------------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------------------------------------

TextureManager::TextureManager(ID3D11Device* _pDevice) :
m_pDevice(_pDevice)
{
	m_pTextureResourceView.push_back(NULL);	// 読み込みに失敗した際に参照する値としてNULLを追加
}

TextureManager::~TextureManager()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool TextureManager::LoadTexture(LPCTSTR _pFileName, int* _pIndex)
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

	ID3D11ShaderResourceView* pResourceView = NULL;
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		_pFileName,
		&LoadInfo,
		NULL,
		&pResourceView,
		NULL)))
	{
		OutputDebugString(TEXT("テクスチャの読み込みに失敗しました\n"));
		*_pIndex = m_InvalidIndex;
		return false;
	}

	*_pIndex = m_pTextureResourceView.size();
	m_pTextureResourceView.push_back(pResourceView);

	return true;
}

void TextureManager::ReleaseTexture(int _index)
{
	if (m_pTextureResourceView[_index] != NULL)
	{
		m_pTextureResourceView[_index]->Release();
		m_pTextureResourceView[_index] = NULL;
	}
}

