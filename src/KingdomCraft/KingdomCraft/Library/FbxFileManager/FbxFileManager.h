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
 *  Fbxファイルを管理するクラス
 */
class FbxFileManager
{
public:
	/**
	 * FbxFileManagerのインスタンスを生成する関数
	 * @param[in] _pDevice Fbxファイルの読み込みに使用するDirectX11デバイス
	 * @param[in] _pDeviceContext 3Dモデルの描画に使用するDirectX11デバイスコンテキスト
	 */
	inline static void Create(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext)
	{
		if (m_pFbxFileManager == NULL)
		{
			m_pFbxFileManager = new FbxFileManager(_pDevice, _pDeviceContext);
		}
	}

	/**
	 * FbxFileManagerのインスタンスを取得する関数
	 * @return FbxFileManagerのインスタンスが返る
	 */
	inline static FbxFileManager* GetInstance()
	{
		return m_pFbxFileManager;
	}

	/**
	 * FbxFileManagerのインスタンスを破棄する関数
	 */
	inline static void Delete()
	{
		delete m_pFbxFileManager;
		m_pFbxFileManager = NULL;
	}

	/**
	 * FbxFileManagerクラスの初期化関数
	 * @return 初期化が成功したかのフラグ
	 */
	bool Init();

	/**
	 * FbxFileManagerクラスの解放関数
	 */
	void Release();

	/**
	 * Fbxモデルを読み込む
	 * @param[in] _pFileName 読み込むモデルのファイルパス
	 * @param[out] _pIndex 読み込んだモデルの格納先インデックス
	 * @return 読み込みに成功したらtrue
	 */
	bool LoadFbxModel(LPCTSTR _pFileName, int* _pIndex);

	/**
	 * Fbxモデルを取得する
	 * @param[in] _index 取得するモデルのインデックス
	 * @return Fbxのデータを格納したFbxModelクラス
	 */
	inline FbxModel* GetFbxModel(int _index) const
	{
		return m_pFbxModel[_index];
	}

	/**
	 * Fbxモデルを解放する
	 * @param[in] _index 解放するモデルのインデックス
	 */
	void ReleaseFbxModel(int _index);

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

	static const int m_InvalidIndex; //!< FbxFileManagerクラスがとるインデックスのエラー値

private:
	/**
	 * FbxFileManagerクラスのコンストラクタ
	 * @param[in] _pDevice Fbxの読み込みの際に利用するDirectX11のデバイス
	 * @param[in] _pDeviceContext Fbxの描画の際に利用するDirectX11のデバイスコンテキスト
	 */
	FbxFileManager(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext);

	/**
	 * FbxFileManagerクラスのデストラクタ
	 */
	~FbxFileManager();

	static FbxFileManager*		m_pFbxFileManager;
	ID3D11Device* const			m_pDevice;
	ID3D11DeviceContext* const	m_pDeviceContext;
	FbxLoader*					m_pFbxLoader;
	std::vector<FbxModel*>		m_pFbxModel;

};


#endif
