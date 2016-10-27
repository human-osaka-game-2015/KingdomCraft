#ifndef SHADERMANAGER_H
#define SHADERMANAGER_H
#include <d3d11.h>
#include <map>

class ShaderManager
{
public:
	ShaderManager(ID3D11Device* _pDevice);
	~ShaderManager();

	/**
	 * 頂点シェーダーを読み込む(頂点シェーダーのバージョンはvs_5_0)
	 * @param[in] _key 頂点シェーダーが格納される場所のキー
	 * @param[in] _fileName 読み込むエフェクトファイルのパス
	 * @param[in] _funcName 頂点シェーダーの関数名
	 * @return 成功したかのフラグ
	 */
	bool LoadVertexShader(int _key, char* _fileName, char* _funcName);

	/**
	 * ピクセルシェーダーを読み込む(ピクセルシェーダーをのバージョンはps_5_0)
	 * @param[in] _key ピクセルシェーダーが格納される場所のキー
	 * @param[in] _fileName 読み込むエフェクトファイルのパス
	 * @param[in] _funcName ピクセルシェーダーの関数名
	 * @return 成功したかのフラグ
	 */
	bool LoadPixelShader(int _key, char* _fileName, char* _funcName);

	/**
	 * 頂点シェーダーを取得する
	 * @param[in] _key 取得したい頂点シェーダーのキー
	 * @return 頂点シェーダー
	 */
	ID3D11VertexShader* GetVertexShader(int _key)
	{
		return m_pVertexShader[_key];
	}

	/**
	 * 頂点シェーダーのコンパイルデータを取得する
	 * @param[in] _key 取得したいコンパイルデータのキー
	 * @return 頂点シェーダーのコンパイルデータ
	 */
	ID3DBlob* GetCompiledVertexShader(int _key)
	{
		return m_pCompiledVertexShader[_key];
	}
	
	/**
	 * ピクセルシェーダーを取得する
	 * @param[in] _key 取得したいピクセルシェーダーのキー
	 * @return ピクセルシェーダー
	 */
	ID3D11PixelShader* GetPixelShader(int _key)
	{
		return m_pPixelShader[_key];
	}

	/**
	 * ピクセルシェーダーのコンパイルデータを取得する
	 * @param[in] _key 取得したいコンパイルデータのキー
	 * @return ピクセルシェーダーのコンパイルデータ
	 */
	ID3DBlob* GetCompiledPixelShader(int _key)
	{
		return m_pCompiledPixelShader[_key];
	}

	/**
	 * 頂点シェーダーを解放する
	 * @param[in] _key 解放する頂点シェーダーのキー
	 */
	void ReleaseVertexShader(int _key)
	{
		m_pVertexShader[_key]->Release();
		m_pVertexShader.erase(_key);
	}

	/**
	 * 頂点シェーダーのコンパイルデータを解放する
	 * @param[in] _key 解放するコンパイルデータのキー
	 */
	void ReleaseCompiledVertexShader(int _key)
	{
		m_pCompiledVertexShader[_key]->Release();
		m_pCompiledVertexShader.erase(_key);
	}

	/**
	 * ピクセルシェーダーを解放する
	 * @param[in] _key 解放するピクセルシェーダーのキー
	 */
	void ReleasePixelShader(int _key)
	{
		m_pPixelShader[_key]->Release();
		m_pPixelShader.erase(_key);
	}

	/**
	 * ピクセルシェーダーのコンパイルデータを解放する
	 * @param[in] _key 解放するコンパイルデータのキー
	 */
	void ReleaseCompiledPixelShader(int _key)
	{
		m_pCompiledPixelShader[_key]->Release();
		m_pCompiledPixelShader.erase(_key);
	}

private:
	ID3D11Device* m_pDevice;
	std::map<int, ID3D11VertexShader*>	m_pVertexShader;
	std::map<int, ID3D11PixelShader*>	m_pPixelShader;
	std::map<int, ID3DBlob*>			m_pCompiledVertexShader;
	std::map<int, ID3DBlob*>			m_pCompiledPixelShader;

};

#endif