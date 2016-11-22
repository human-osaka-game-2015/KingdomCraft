/**
 * @file   TextureManager.h
 * @brief  TextureManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H
#include <d3d11.h>
#include <vector>

/**
 * テクスチャの管理クラス
 */
class TextureManager
{
public:
	/**
	 * インスタンスを生成
	 * @param[in] _pDevice テクスチャの読み込みに使用するDirectX11のデバイス
	 */
	inline static void Create(ID3D11Device* const _pDevice)
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
	inline static TextureManager* GetInstance()
	{
		return m_pTextureManager;
	}

	/**
	 * インスタンスを破棄する
	 */
	inline static void Delete()
	{
		delete m_pTextureManager;
		m_pTextureManager = NULL;
	}

	/**
	 * テクスチャを読み込む関数
	 *
	 * テクスチャの読み込みが失敗したらNULLへのインデックスが返る
	 * @param[in] _pFileName 読み込むテクスチャファイルのパス
	 * @param[out] _pIndex 読み込んだテクスチャが格納されている先のインデックス(読み込みが失敗した場合0が格納される)
	 * @return テクスチャの読み込みに成功したらtrue
	 */
	bool LoadTexture(LPCTSTR _pFileName, int* _pIndex);

	/**
	 * 格納しているテクスチャを取得する
	 * @param[in] _index 取得したいテクスチャのインデックス
	 * @return テクスチャのリソースビュー
	 */
	inline ID3D11ShaderResourceView* GetTexture(int _index)
	{
		return m_pTextureResourceView[_index];
	}

	/**
	 * 格納しているテクスチャを解放する
	 * 
	 * 0を引数として渡してはいけない
	 * @param[in] _index 解放したいテクスチャのインデックス
	 */
	void ReleaseTexture(int _index);
	

	/**
	 * テクスチャを確保しているバッファをクリアする
	 *
	 * vectorを使用しているのでバッファ領域は解放されない。\n
	 * バッファ領域はTextureManagerのDelete関数が呼ばれて破棄されたときに解放される。
	 */
	inline void ClearBuffer()
	{
		m_pTextureResourceView.clear();
	}

	static const int m_InvalidIndex;	//!< TextureManagerクラスがとるインデックスのエラー値

private:
	/**
	 * TextureManagerクラスのコンストラクタ
	 * @param[in] _pDevice テクスチャの読み込みに使用するDirectX11のデバイス
	 */
	TextureManager(ID3D11Device* const _pDevice);

	/**
	 * TextureManagerクラスのデストラクタ
	 */
	~TextureManager();

	static TextureManager*						m_pTextureManager;
	ID3D11Device* const							m_pDevice;
	std::vector<ID3D11ShaderResourceView*>		m_pTextureResourceView;

};


#endif
