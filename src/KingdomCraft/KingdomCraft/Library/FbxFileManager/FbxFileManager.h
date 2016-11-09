/**
 * @file   FbxFileManager.h
 * @brief  FbxFileManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef FBXFILEMANAGER_H
#define FBXFILEMANAGER_H
#include <d3d11.h>
#include <vector>
#include "FbxModel\FbxModel.h"

class FbxLoader;

/**
 * @brief  Fbxファイルを管理するクラス
 */
class FbxFileManager
{
public:
	FbxFileManager(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext);
	~FbxFileManager();

	bool Init();
	void Release();

	/**
	 * Fbxモデルを読み込む
	 * @param[in] _filePath 読み込むモデルのファイルパス
	 * @param[in] _pOutKey 読み込んだモデルの格納先キー
	 * @return 読み込みに成功したらtrue
	 */
	bool LoadFbxModel(LPCTSTR _filePath, int* _pOutKey);

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
	}

	/**
	 * モデルを確保しているバッファをクリアする
	 *
	 * vectorを使用しているのでバッファ領域は解放されない。\n
	 * バッファ領域はFbxFileManagerが破棄されたときに解放される。
	 */
	inline void ClearBuffer()
	{
		m_pFbxModel.clear();
	}

private:
	ID3D11Device*				m_pDevice;
	ID3D11DeviceContext*		m_pDeviceContext;
	std::vector<FbxModel*>		m_pFbxModel;
	FbxLoader*					m_pFbxLoader;

};


#endif