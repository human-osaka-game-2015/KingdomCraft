#ifndef FBXFILEMANAGER_H
#define FBXFILEMANAGER_H
#include <d3d11.h>
#include <map>
#include "FbxModel\FbxModel.h"

class FbxLoader;

class FbxFileManager
{
public:
	FbxFileManager(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext);
	~FbxFileManager();

	bool Init();
	void Release();

	/**
	 * Fbxモデルを読み込む
	 * @param[in] _key 読み込んだモデルの格納先キー
	 * @param[in] _filePath 読み込むモデルのファイルパス
	 * @return 読み込みに成功したらtrue
	 */
	bool LoadFbxModel(int _key, LPCTSTR _filePath);

	/**
	 * Fbxモデルを取得する
	 * @param[in] _key 取得するモデルのキー
	 * @return Fbxモデル
	 */
	inline FbxModel* GetFbxModel(int _key)
	{
		return m_pFbxModel[_key];
	}

	/**
	 * Fbxモデルを解放する
	 * @param[in] _key 解放するモデルのキー
	 */
	inline void ReleaseFbxModel(int _key)
	{
		m_pFbxModel[_key]->Release();
		delete m_pFbxModel[_key];
		m_pFbxModel.erase(_key);
	}

private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pDeviceContext;
	std::map<int, FbxModel*>	m_pFbxModel;
	FbxLoader*					m_pFbxLoader;

};


#endif