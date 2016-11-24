/**
 * @file   FbxLoader.cpp
 * @brief  FbxLoaderクラスの実装
 * @author morimoto
 */
#include "FbxLoader.h"


//----------------------------------------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------------------------------------

FbxLoader::FbxLoader(ID3D11Device* _pDevice):
m_pDevice(_pDevice),
m_pFbxManager(NULL),
m_pFbxScene(NULL),
m_pFbxImporter(NULL),
m_pFbxIOSettings(NULL),
m_pModel(NULL)
{

}

FbxLoader::~FbxLoader()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool FbxLoader::Init()
{
	if (!InitFbxManager())
	{
		return false;
	}

	if (!InitFbxScene())
	{
		ReleaseFbxManager();
		return false;
	}

	if (!InitFbxImporter())
	{
		ReleaseFbxScene();
		ReleaseFbxManager();
		return false;
	}

	if (!InitFbxIOSettings())
	{
		ReleaseFbxImporter();
		ReleaseFbxScene();
		ReleaseFbxManager();
		return false;
	}

	return true;
}

void FbxLoader::Release()
{
	ReleaseFbxIOSettings();
	ReleaseFbxImporter();
	ReleaseFbxScene();
	ReleaseFbxManager();
}

bool FbxLoader::LoadFbxModel(FbxModel* _pModel, LPCTSTR _pFileName)
{
	m_pModel = _pModel;
	if (!m_pFbxImporter->Initialize(_pFileName, -1, m_pFbxIOSettings))
	{
		OutputDebugString(TEXT("FbxImporterのInitializeに失敗しました\n"));
		return false;
	}

	if (!m_pFbxImporter->Import(m_pFbxScene))
	{
		OutputDebugString(TEXT("FbxImporterのImportに失敗しました\n"));
		return false;
	}

	FbxGeometryConverter GeometryConverter(m_pFbxManager);
	if (!GeometryConverter.Triangulate(m_pFbxScene, true))
	{
		OutputDebugString(TEXT("三角形化に失敗しました\n"));
		return false;
	}

	FbxNode* pNode = m_pFbxScene->GetRootNode();
	RecursiveNode(pNode);

	return true;
}

void FbxLoader::RecursiveNode(FbxNode* _pFbxNode)
{
	FbxNode* pChildNode = NULL;
	int ChildCount = _pFbxNode->GetChildCount();
	for (int i = 0; i < ChildCount; i++)
	{
		pChildNode = _pFbxNode->GetChild(i);
		RecursiveNode(pChildNode);
	}

	fbxsdk::FbxNodeAttribute* pAttribute = _pFbxNode->GetNodeAttribute();

	if (pAttribute != NULL)
	{
		switch (pAttribute->GetAttributeType())
		{
		case fbxsdk::FbxNodeAttribute::eMesh:

			LoadMesh(pAttribute);

			break;
		}
	}
}

bool FbxLoader::LoadMesh(FbxNodeAttribute* _pAttribute)
{
	FbxMesh* pFbxMesh = reinterpret_cast<FbxMesh*>(_pAttribute);
	FbxModel::MESH_DATA MeshData;
	ZeroMemory(&MeshData, sizeof(FbxModel::MESH_DATA));

	if (!LoadMeshVertexData(pFbxMesh, &MeshData))
	{
		OutputDebugString(TEXT("頂点情報の読み込みに失敗しました\n"));
		return false;
	}
	
	if (!LoadMeshNormalData(pFbxMesh, &MeshData))
	{
		OutputDebugString(TEXT("法線情報の読み込みに失敗しました\n"));
		return false;
	}

	if (!LoadMeshTextureData(pFbxMesh, &MeshData))
	{
		OutputDebugString("テクスチャ情報の読み込みに失敗しました\n");
		return false;
	}

	if (!LoadMeshMaterialData(pFbxMesh, &MeshData))
	{
		OutputDebugString("マテリアル情報の読み込みに失敗しました\n");
		return false;
	}

	if (!LoadMeshAnimationData(pFbxMesh, &MeshData))
	{
		OutputDebugString("アニメーション情報の読み込みに失敗しました\n");
		return false;
	}

	m_pModel->AddMeshData(&MeshData);

	return true;
}

bool FbxLoader::LoadMeshVertexData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
{
	FbxModel::VERTEX_DATA* pVertex = new FbxModel::VERTEX_DATA;

	// 総ポリゴン数
	int PolygonNum = _pMesh->GetPolygonCount();

	// 全ての頂点数(インデックスの数)
	int PolygonVertexNum = _pMesh->GetPolygonVertexCount();

	// インデックスデータ
	int* pIndexAry = _pMesh->GetPolygonVertices();

	// インデックスバッファが指す頂点数
	int ControlPositionNum = _pMesh->GetControlPointsCount();
	
	// インデックスバッファが指す頂点
	fbxsdk::FbxVector4* pFbxVec = _pMesh->GetControlPoints();


	pVertex->PolygonNum = PolygonNum;
	pVertex->PolygonVertexNum = PolygonVertexNum;
	pVertex->ControlPositionNum = ControlPositionNum;

	pVertex->pIndexAry = new int[PolygonVertexNum];
	for (int i = 0; i < PolygonVertexNum; i++)
	{
		pVertex->pIndexAry[i] = pIndexAry[i];
	}

	pVertex->pVertex = new D3DXVECTOR3[ControlPositionNum];
	for (int i = 0; i < ControlPositionNum; i++)
	{
		pVertex->pVertex[i].x = static_cast<float>(pFbxVec[i][0]);
		pVertex->pVertex[i].y = static_cast<float>(pFbxVec[i][1]);
		pVertex->pVertex[i].z = static_cast<float>(pFbxVec[i][2]);
	}

	_pMeshData->pVertexData = pVertex;

	return true;
}

bool FbxLoader::LoadMeshNormalData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
{
	int NormalSetCount = _pMesh->GetElementNormalCount();
	FbxModel::NORMAL_DATA* pNormalData = new FbxModel::NORMAL_DATA;

	for (int NormalIndex = 0; NormalIndex < NormalSetCount; NormalIndex++)
	{
		if (NormalIndex >= 1)
		{
			OutputDebugString(TEXT("法線セットが複数あります(対応していません)\n一番最初の法線セットを適応させます\n"));
			break;
		}

		// 法線セットの取得
		fbxsdk::FbxGeometryElementNormal* pNormal = _pMesh->GetElementNormal(NormalIndex);

		// マッピングモード取得
		FbxGeometryElement::EMappingMode MappingMode = pNormal->GetMappingMode();

		// リファレンスモード取得
		FbxGeometryElement::EReferenceMode ReferenceMode = pNormal->GetReferenceMode();


		switch (MappingMode)
		{
		case FbxGeometryElement::eByPolygonVertex:
			switch (ReferenceMode)
			{
			case FbxGeometryElement::eDirect:
				pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
				for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
				{
					pNormalData[NormalIndex].pNormalVec->x = float(pNormal->GetDirectArray().GetAt(i)[0]);
					pNormalData[NormalIndex].pNormalVec->y = float(pNormal->GetDirectArray().GetAt(i)[1]);
					pNormalData[NormalIndex].pNormalVec->z = float(pNormal->GetDirectArray().GetAt(i)[2]);
				}
			break;
			default:
				/// 不明なモードは空データで対応

				MessageBox(NULL, TEXT("リファレンスモード不明です\n空データを作成して対応します"), TEXT("エラー"), MB_ICONSTOP);

				pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
				for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
				{
					pNormalData[NormalIndex].pNormalVec->x = 0.0f;
					pNormalData[NormalIndex].pNormalVec->y = 0.0f;
					pNormalData[NormalIndex].pNormalVec->z = 0.0f;
				}
			break;
			}
			break;
		case FbxGeometryElement::eByControlPoint:	
			MessageBox(NULL, TEXT("マッピングモードeByControlPointに対応していません\n空データを作成して対応します"), TEXT("エラー"), MB_ICONSTOP);

			pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
			for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
			{
				pNormalData[NormalIndex].pNormalVec->x = 0.0f;
				pNormalData[NormalIndex].pNormalVec->y = 0.0f;
				pNormalData[NormalIndex].pNormalVec->z = 0.0f;
			}
			break;
		default:
			MessageBox(NULL, TEXT("マッピングモードが不明です\n空データを作成して対応します"), TEXT("エラー"), MB_ICONSTOP);

			pNormalData[NormalIndex].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertexData->PolygonVertexNum];
			for (int i = 0; i < _pMeshData->pVertexData->PolygonVertexNum; i++)
			{
				pNormalData[NormalIndex].pNormalVec->x = 0.0f;
				pNormalData[NormalIndex].pNormalVec->y = 0.0f;
				pNormalData[NormalIndex].pNormalVec->z = 0.0f;
			}
			break;
		}
	}

	_pMeshData->pNormalData = pNormalData;

	return true;
}

bool FbxLoader::LoadMeshTextureData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
{
	/// @todo テクスチャデータの取得は未実装
	return true;
}

bool FbxLoader::LoadMeshMaterialData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
{
	/// @todo マテリアルデータの取得は未実装
	return true;
}

bool FbxLoader::LoadMeshAnimationData(FbxMesh* _pMesh, FbxModel::MESH_DATA* _pMeshData)
{
	/// @todo アニメーションデータの取得は未実装
	return true;
}

void FbxLoader::GetTextureName(
	fbxsdk::FbxSurfaceMaterial* _pMaterial,
	LPCTSTR _pMatFlag,
	std::vector<LPCTSTR>* _pOutFileName,
	std::vector<fbxsdk::FbxString>* _pOutUvSetName,
	int* _pOutCount)
{
	fbxsdk::FbxProperty Property = _pMaterial->FindProperty(_pMatFlag);
	int LayerTextureCount = Property.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

	if (LayerTextureCount == 0)
	{
		int TextureCount = Property.GetSrcObjectCount<fbxsdk::FbxFileTexture>();
		for (int i = 0; i < TextureCount; i++)
		{
			(*_pOutCount)++;
			fbxsdk::FbxFileTexture* fbxTexture = FbxCast<fbxsdk::FbxFileTexture>(Property.GetSrcObject<fbxsdk::FbxFileTexture>(i));
			_pOutUvSetName->push_back(fbxTexture->UVSet.Get());
			_pOutFileName->push_back(fbxTexture->GetRelativeFileName());
		}
	}
}


//----------------------------------------------------------------------------------------------------
// Private Functions
//----------------------------------------------------------------------------------------------------

bool FbxLoader::InitFbxManager()
{
	m_pFbxManager = fbxsdk::FbxManager::Create();
	if (m_pFbxManager == NULL)
	{
		OutputDebugString(TEXT("FbxManagerクラスの生成に失敗\n"));
		return false;
	}

	return true;
}

bool FbxLoader::InitFbxScene()
{
	m_pFbxScene = fbxsdk::FbxScene::Create(m_pFbxManager, "");
	if (m_pFbxScene == NULL)
	{
		OutputDebugString(TEXT("FbxSceneクラスの生成に失敗\n"));
		return false;
	}

	return true;
}

bool FbxLoader::InitFbxImporter()
{
	m_pFbxImporter = fbxsdk::FbxImporter::Create(m_pFbxManager, "");
	if (m_pFbxImporter == NULL)
	{
		OutputDebugString(TEXT("FbxImporterクラスの生成に失敗\n"));
		return false;
	}

	return true;
}

bool FbxLoader::InitFbxIOSettings()
{
	m_pFbxIOSettings = fbxsdk::FbxIOSettings::Create(m_pFbxManager, IOSROOT);
	if (m_pFbxIOSettings == NULL)
	{
		OutputDebugString(TEXT("FbxIOSettingsクラスの生成に失敗\n"));
		return false;
	}
	m_pFbxManager->SetIOSettings(m_pFbxIOSettings);

	return true;
}

void FbxLoader::ReleaseFbxManager()
{
	if (m_pFbxManager != NULL)
	{
		m_pFbxManager->Destroy();
		m_pFbxManager = NULL;
	}
}

void FbxLoader::ReleaseFbxScene()
{
	if (m_pFbxScene != NULL)
	{
		m_pFbxScene->Destroy();
		m_pFbxScene = NULL;
	}
}

void FbxLoader::ReleaseFbxImporter()
{
	if (m_pFbxImporter != NULL)
	{
		m_pFbxImporter->Destroy();
		m_pFbxImporter = NULL;
	}
}

void FbxLoader::ReleaseFbxIOSettings()
{
	if (m_pFbxIOSettings != NULL)
	{
		m_pFbxIOSettings->Destroy();
		m_pFbxIOSettings = NULL;
	}
}

