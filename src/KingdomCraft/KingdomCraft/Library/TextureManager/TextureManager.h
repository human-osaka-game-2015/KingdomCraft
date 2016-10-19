#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <d3d11.h>
#include <map>

class TextureManager
{
public:
	TextureManager(ID3D11Device* _pDevice);
	~TextureManager();

	bool LoadTexture(int _Key, char* _FilePath);

	inline ID3D11ShaderResourceView* GetTexture(int _Key)
	{ 
		return m_pTextureResourceView[_Key]; 
	}
	
	inline void ReleaseTexture(int _Key)
	{ 
		m_pTextureResourceView[_Key]->Release(); 
		m_pTextureResourceView.erase(_Key); 
	}

private:
	ID3D11Device*								m_pDevice;
	std::map<int, ID3D11ShaderResourceView*>	m_pTextureResourceView;

};

#endif