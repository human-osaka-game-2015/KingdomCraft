#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <d3d11.h>
#include <map>

class TextureManager
{
public:
	TextureManager(ID3D11Device* _pDevice);
	~TextureManager();

	bool LoadTexture(int _key, char* _filePath);

	inline ID3D11ShaderResourceView* GetTexture(int _key)
	{ 
		return m_pTextureResourceView[_key];
	}
	
	inline void ReleaseTexture(int _key)
	{ 
		m_pTextureResourceView[_key]->Release();
		m_pTextureResourceView.erase(_key);
	}

private:
	ID3D11Device*								m_pDevice;
	std::map<int, ID3D11ShaderResourceView*>	m_pTextureResourceView;

};

#endif