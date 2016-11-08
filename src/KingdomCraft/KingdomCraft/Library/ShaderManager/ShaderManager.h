/**
 * @file   ShaderManager.h
 * @brief  ShaderManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <d3d11.h>
#include <vector>

/**
 * @brief エフェクトファイルを管理するクラス
 *
 * シェーダーの読み込みから破棄まで管理している
 */
class ShaderManager
{
public:
	~ShaderManager();

	/**
	 * インスタンスを生成
	 */
	static void Create(ID3D11Device* _pDevice)
	{
		if (m_pShaderManager == NULL)
		{
			m_pShaderManager = new ShaderManager(_pDevice);
		}
	}

	/**
	 * インスタンスを取得する
	 * @return インスタンスが返る
	 */
	static ShaderManager* GetInstance()
	{
		return m_pShaderManager;
	}

	/**
	 * ShaderManagerインスタンスを破棄する
	 */
	static void Delete()
	{
		delete m_pShaderManager;
		m_pShaderManager = NULL;
	}

	/**
	 * 頂点シェーダーを読み込む(頂点シェーダーのバージョンはvs_5_0)
	 * @param[in] _fileName 読み込むエフェクトファイルのパス
	 * @param[in] _funcName 頂点シェーダーの関数名
	 * @param[in] _pOutKey 頂点シェーダーとコンパイルデータの格納先キー
	 * @return 成功したかのフラグ
	 */
	bool LoadVertexShader(LPCTSTR _fileName, LPCTSTR _funcName, int* _pOutKey);

	/**
	 * ピクセルシェーダーを読み込む(ピクセルシェーダーをのバージョンはps_5_0)
	 * @param[in] _fileName 読み込むエフェクトファイルのパス
	 * @param[in] _funcName ピクセルシェーダーの関数名
	 * @param[in] _pOutKey ピクセルシェーダーとコンパイルデータの格納先キー
	 * @return 成功したかのフラグ
	 */
	bool LoadPixelShader(LPCTSTR _fileName, LPCTSTR _funcName, int* _pOutKey);

	/**
	 * 頂点シェーダーを取得する
	 * @param[in] _key 取得したい頂点シェーダーのキー
	 * @return 頂点シェーダー
	 */
	inline ID3D11VertexShader* GetVertexShader(int _key)
	{
		return m_pVertexShader[_key];
	}

	/**
	 * 頂点シェーダーのコンパイルデータを取得する
	 * @param[in] _key 取得したいコンパイルデータのキー
	 * @return 頂点シェーダーのコンパイルデータ
	 */
	inline ID3DBlob* GetCompiledVertexShader(int _key)
	{
		return m_pCompiledVertexShader[_key];
	}
	
	/**
	 * ピクセルシェーダーを取得する
	 * @param[in] _key 取得したいピクセルシェーダーのキー
	 * @return ピクセルシェーダー
	 */
	inline ID3D11PixelShader* GetPixelShader(int _key)
	{
		return m_pPixelShader[_key];
	}

	/**
	 * ピクセルシェーダーのコンパイルデータを取得する
	 * @param[in] _key 取得したいコンパイルデータのキー
	 * @return ピクセルシェーダーのコンパイルデータ
	 */
	inline ID3DBlob* GetCompiledPixelShader(int _key)
	{
		return m_pCompiledPixelShader[_key];
	}

	/**
	 * 頂点シェーダーとそのコンパイルデータを解放する
	 * @param[in] _key 解放する頂点シェーダーのキー
	 */
	inline void ReleaseVertexShader(int _key)
	{
		m_pVertexShader[_key]->Release();
		m_pCompiledVertexShader[_key]->Release();
	}

	/**
	 * ピクセルシェーダーとそのコンパイルデータを解放する
	 * @param[in] _key 解放するピクセルシェーダーのキー
	 */
	inline void ReleasePixelShader(int _key)
	{
		m_pPixelShader[_key]->Release();
		m_pCompiledPixelShader[_key]->Release();
	}

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

private:
	ShaderManager(ID3D11Device* _pDevice);

	static ShaderManager* m_pShaderManager;
	ID3D11Device* m_pDevice;
	std::vector<ID3D11VertexShader*>	m_pVertexShader;
	std::vector<ID3D11PixelShader*>		m_pPixelShader;
	std::vector<ID3DBlob*>				m_pCompiledVertexShader;
	std::vector<ID3DBlob*>				m_pCompiledPixelShader;

};

#endif