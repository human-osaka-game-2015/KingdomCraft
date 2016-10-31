#ifndef FBXLOADER_H
#define FBXLOADER_H
#include <d3d11.h>
#include <fbxsdk.h>
#include "../FbxModel/FbxModel.h"

class FbxLoader
{
public:
	FbxLoader(ID3D11Device* _pDevice);
	~FbxLoader();

	/**
	 * FbxLoaderを初期化する
	 */
	bool Init();

	/**
	 * FbxLoaderを解放する
	 */
	void Release();

	/**
	 * Fbxモデルを読み込む
	 * @param[out] _pModel 読み込みに成功した場合はモデルデータが格納される、失敗したらNULL
	 * @param[in] _filePath 読み込むモデルのファイルパス
	 * @return 読み込みに成功したらtrue
	 */
	bool LoadFbxModel(FbxModel* _pModel, LPCTSTR _filePath);

private:
	bool InitFbxManager();
	bool InitFbxScene();
	bool InitFbxImporter();
	bool InitFbxIOSettings();
	void ReleaseFbxManager();
	void ReleaseFbxScene();
	void ReleaseFbxImporter();
	void ReleaseFbxIOSettings();

	void RecursiveNode(FbxNode* _pFbxNode);
	bool LoadMesh(FbxNodeAttribute* _pAttribute);
	bool LoadMeshVertexData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData);
	bool LoadMeshNormalData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData);
	bool LoadMeshTextureData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData);
	bool LoadMeshMaterialData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData);
	bool LoadMeshAnimationData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData);
	
	void GetTextureName(
		fbxsdk::FbxSurfaceMaterial* material,
		LPCTSTR matFlag,
		std::vector<LPCTSTR>* pOutFileName,
		std::vector<fbxsdk::FbxString>* pOutUvSetName,
		int* OutCount);


	ID3D11Device*			m_pDevice;
	fbxsdk::FbxManager*		m_pFbxManager;
	fbxsdk::FbxScene*		m_pFbxScene;
	fbxsdk::FbxImporter*	m_pFbxImporter;
	fbxsdk::FbxIOSettings*	m_pFbxIOSettings;
	FbxModel*				m_pModel;

};


#endif