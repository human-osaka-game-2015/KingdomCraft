/**
 * @file   ShaderManager.h
 * @brief  ShaderManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <D3DX11.h>
#include <vector>

/**
 * エフェクトファイルを管理するクラス
 *
 * シェーダーの読み込みから破棄まで管理している
 */
class ShaderManager
{
public:
	/**
	 * ShaderManagerのインスタンスを生成する関数
	 * @param[in] _pDevice シェーダーを読み込むためのDirectX11デバイス
	 */
	static void Create(ID3D11Device* _pDevice)
	{
		if (m_pShaderManager == NULL)
		{
			m_pShaderManager = new ShaderManager(_pDevice);
		}
	}

	/**
	 * ShaderManagerのインスタンスを取得する関数
	 * @return ShaderManagerのインスタンス
	 */
	static ShaderManager* GetInstance()
	{
		return m_pShaderManager;
	}

	/**
	 * ShaderManagerのインスタンスを破棄する関数
	 */
	static void Delete()
	{
		delete m_pShaderManager;
		m_pShaderManager = NULL;
	}

	/**
	 * 頂点シェーダーを読み込む(頂点シェーダーのバージョンはvs_5_0)
	 * @param[in] _pFileName 読み込むエフェクトファイルのパス
	 * @param[in] _pFuncName 頂点シェーダーの関数名
	 * @param[out] _pIndex 頂点シェーダーとコンパイルデータの格納先インデックスが入る
	 * @return 成功したかのフラグ
	 */
	bool LoadVertexShader(LPCTSTR _pFileName, LPCTSTR _pFuncName, int* _pIndex);

	/**
	 * ピクセルシェーダーを読み込む(ピクセルシェーダーをのバージョンはps_5_0)
	 * @param[in] _pFileName 読み込むエフェクトファイルのパス
	 * @param[in] _pFuncName ピクセルシェーダーの関数名
	 * @param[out] _pIndex ピクセルシェーダーとコンパイルデータの格納先インデックスが入る
	 * @return 成功したかのフラグ
	 */
	bool LoadPixelShader(LPCTSTR _pFileName, LPCTSTR _pFuncName, int* _pIndex);

	/**
	 * 頂点シェーダーを取得する
	 * @param[in] _index 取得したい頂点シェーダーのインデックス
	 * @return 頂点シェーダー
	 */
	inline ID3D11VertexShader* GetVertexShader(int _index) const
	{
		return m_pVertexShader[_index];
	}

	/**
	 * 頂点シェーダーのコンパイルデータを取得する
	 * @param[in] _index 取得したいコンパイルデータのインデックス
	 * @return 頂点シェーダーのコンパイルデータ
	 */
	inline ID3DBlob* GetCompiledVertexShader(int _index) const
	{
		return m_pCompiledVertexShader[_index];
	}

	/**
	 * ピクセルシェーダーを取得する
	 * @param[in] _index 取得したいピクセルシェーダーのインデックス
	 * @return ピクセルシェーダー
	 */
	inline ID3D11PixelShader* GetPixelShader(int _index) const
	{
		return m_pPixelShader[_index];
	}

	/**
	 * ピクセルシェーダーのコンパイルデータを取得する
	 * @param[in] _index 取得したいコンパイルデータのインデックス
	 * @return ピクセルシェーダーのコンパイルデータ
	 */
	inline ID3DBlob* GetCompiledPixelShader(int _index) const
	{
		return m_pCompiledPixelShader[_index];
	}

	/**
	 * 頂点シェーダーとそのコンパイルデータを解放する
	 * @param[in] _index 解放する頂点シェーダーのインデックス
	 */
	void ReleaseVertexShader(int _index);

	/**
	 * ピクセルシェーダーとそのコンパイルデータを解放する
	 * @param[in] _index 解放するピクセルシェーダーのインデックス
	 */
	void ReleasePixelShader(int _index);


	/**
	 * 頂点シェーダーとコンパイルデータを確保しているバッファをクリアする
	 *
	 * vectorを使用しているのでバッファ領域は解放されない。\n
	 * バッファ領域はShaderManagerが破棄されたときに解放される。
	 */
	inline void ClearVertexShaderBuffer()
	{
		m_pVertexShader.clear();
		m_pCompiledVertexShader.clear();
	}

	/**
	 * ピクセルシェーダーとコンパイルデータを確保しているバッファをクリアする
	 *
	 * vectorを使用しているのでバッファ領域は解放されない。\n
	 * バッファ領域はShaderManagerが破棄されたときに解放される。
	 */
	inline void ClearPixelShaderBuffer()
	{
		m_pPixelShader.clear();
		m_pCompiledPixelShader.clear();
	}

	/**
	 * シェーダーのデータを確保しているバッファをクリアする
	 *
	 * vectorを使用しているのでバッファ領域は解放されない。\n
	 * バッファ領域はShaderManagerが破棄されたときに解放される。
	 */
	inline void ClearShaderBuffer()
	{
		ClearVertexShaderBuffer();
		ClearPixelShaderBuffer();
	}

	static const int m_InvalidIndex;	//!< ShaderManagerクラスがとるインデックスのエラー値

private:
	/**
	 * ShaderManagerクラスのコンストラクタ
	 * @param[in] _pDevice シェーダーを読み込むためのDirectX11デバイス
	 */
	ShaderManager(ID3D11Device* _pDevice);

	/**
	 * ShaderManagerクラスのデストラクタ
	 */
	~ShaderManager();

	static ShaderManager*				m_pShaderManager;
	ID3D11Device* const					m_pDevice;
	std::vector<ID3D11VertexShader*>	m_pVertexShader;
	std::vector<ID3D11PixelShader*>		m_pPixelShader;
	std::vector<ID3DBlob*>				m_pCompiledVertexShader;
	std::vector<ID3DBlob*>				m_pCompiledPixelShader;

};


#endif
