#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <d3d11.h>
#include <map>

class TextureManager
{
public:
	~TextureManager();

	/**
	 * インスタンスを生成
	 */
	static void Create(ID3D11Device* _pDevice)
	{
		if (m_pTextureManager == NULL)
		{
			m_pTextureManager = new TextureManager(_pDevice);
		}
	}

	/**
	 * インスタンスを取得する
	 * @return インスタンスが返る
	 */
	static TextureManager* GetInstance()
	{
		return m_pTextureManager;
	}

	/**
	 * TextureManagerインスタンスを破棄する
	 */
	static void Delete()
	{
		delete m_pTextureManager;
		m_pTextureManager = NULL;
	}

	/**
	 * テクスチャを読み込む
	 * @param[in] _key 読み込んだテクスチャの格納先へのキー
	 * @param[in] _filePath 読み込むテクスチャ
	 * @return テクスチャの読み込みに成功したらtrue
	 */
	bool LoadTexture(int _key, LPCTCH _filePath);

	/**
	 * 格納しているテクスチャを取得する
	 * @param[in] _key 取得したいテクスチャのキー
	 * @return テクスチャのリソースビュー
	 */
	inline ID3D11ShaderResourceView* GetTexture(int _key)
	{ 
		return m_pTextureResourceView[_key];
	}
	
	/**
	 * 格納しているテクスチャを解放する
	 * @param[in] _key 解放したいテクスチャのキー
	 */
	inline void ReleaseTexture(int _key)
	{ 
		m_pTextureResourceView[_key]->Release();
		m_pTextureResourceView.erase(_key);
	}

private:
	TextureManager(ID3D11Device* _pDevice);

	static TextureManager*						m_pTextureManager;
	ID3D11Device*								m_pDevice;
	std::map<int, ID3D11ShaderResourceView*>	m_pTextureResourceView;

};

#endif