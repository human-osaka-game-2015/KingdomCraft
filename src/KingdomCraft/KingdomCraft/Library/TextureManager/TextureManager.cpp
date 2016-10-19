#include "TextureManager.h"
#include <d3dx11.h>


TextureManager::TextureManager(ID3D11Device* _pDevice):
m_pDevice(_pDevice)
{
}

TextureManager::~TextureManager()
{
}

bool TextureManager::LoadTexture(int _Key, char* _FilePath)
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

	ID3D11ShaderResourceView* pResourceView;
	if (FAILED(D3DX11CreateShaderResourceViewFromFile(
		m_pDevice,
		_FilePath,
		&LoadInfo,
		NULL,
		&pResourceView,
		NULL)))
	{
		OutputDebugString("テクスチャの読み込みに失敗しました\n");
		return false;
	}

	m_pTextureResourceView[_Key] = pResourceView;

	return true;
}
