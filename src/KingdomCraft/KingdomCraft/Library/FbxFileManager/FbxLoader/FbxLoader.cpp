#include "FbxLoader.h"

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

bool FbxLoader::LoadFbxModel(FbxModel* _pModel, LPCTSTR _filePath)
{
	m_pModel = _pModel;
	if (!m_pFbxImporter->Initialize(_filePath, -1, m_pFbxIOSettings))
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
	FbxMesh* pFbxMesh = (FbxMesh*)_pAttribute;
	FbxModel::MeshData MeshData;
	ZeroMemory(&MeshData, sizeof(FbxModel::MeshData));

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

	/*if (!LoadMeshTextureData(pFbxMesh, &MeshData))
	{
		OutputDebugString("テクスチャ情報の読み込みに失敗しました\n");
		return false;
	}

	if (!LoadMeshMaterialData(pFbxMesh, &MeshData))
	{
		OutputDebugString("マテリアル情報の読み込みに失敗しました\n");
		return false;
	}*/

	//if (!LoadMeshAnimationData(pFbxMesh, &MeshData))
	//{
	//	OutputDebugString("アニメーション情報の読み込みに失敗しました\n");
	//	return false;
	//}

	m_pModel->AddMeshData(&MeshData);

	return true;
}

bool FbxLoader::LoadMeshVertexData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData)
{
	FbxModel::VertexData* pVertex = new FbxModel::VertexData;

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
		pVertex->pVertex[i].x = (float)pFbxVec[i][0];
		pVertex->pVertex[i].y = (float)pFbxVec[i][1];
		pVertex->pVertex[i].z = (float)pFbxVec[i][2];
	}

	_pMeshData->pVertex = pVertex;

	return true;
}

bool FbxLoader::LoadMeshNormalData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData)
{
	int NormalSetCount = _pMesh->GetElementNormalCount();
	FbxModel::NormalData* pNormal = new FbxModel::NormalData;

	for (int i = 0; i < NormalSetCount; i++)
	{
		if (i >= 1)
		{
			OutputDebugString(TEXT("法線セットが複数あります(対応していません)\n一番最初の法線セットを適応させます\n"));
			break;
		}

		// 法線セットの取得
		fbxsdk::FbxGeometryElementNormal* Normal = _pMesh->GetElementNormal(i);

		// マッピングモード取得
		FbxGeometryElement::EMappingMode MappingMode = Normal->GetMappingMode();

		// リファレンスモード取得
		FbxGeometryElement::EReferenceMode ReferenceMode = Normal->GetReferenceMode();


		switch (MappingMode)
		{
		case FbxGeometryElement::eByPolygonVertex:
			switch (ReferenceMode)
			{
			case FbxGeometryElement::eDirect:
				pNormal[i].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertex->PolygonVertexNum];
				for (int n = 0; n < _pMeshData->pVertex->PolygonVertexNum; n++)
				{
					pNormal[i].pNormalVec->x = float(Normal->GetDirectArray().GetAt(n)[0]);
					pNormal[i].pNormalVec->y = float(Normal->GetDirectArray().GetAt(n)[1]);
					pNormal[i].pNormalVec->z = float(Normal->GetDirectArray().GetAt(n)[2]);
				}
			break;
			default:
				/// 不明なモードはからデータで対応

				MessageBox(NULL, TEXT("リファレンスモード不明です\n空データを作成して対応します"), TEXT("エラー"), MB_ICONSTOP);

				pNormal[i].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertex->PolygonVertexNum];
				for (int n = 0; n < _pMeshData->pVertex->PolygonVertexNum; n++)
				{
					pNormal[i].pNormalVec->x = 0.0f;
					pNormal[i].pNormalVec->y = 0.0f;
					pNormal[i].pNormalVec->z = 0.0f;
				}
			break;
			}
			break;
		case FbxGeometryElement::eByControlPoint:	
			MessageBox(NULL, TEXT("マッピングモードeByControlPointに対応していません\n空データを作成して対応します"), TEXT("エラー"), MB_ICONSTOP);

			pNormal[i].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertex->PolygonVertexNum];
			for (int n = 0; n < _pMeshData->pVertex->PolygonVertexNum; n++)
			{
				pNormal[i].pNormalVec->x = 0.0f;
				pNormal[i].pNormalVec->y = 0.0f;
				pNormal[i].pNormalVec->z = 0.0f;
			}
			break;
		default:
			MessageBox(NULL, TEXT("マッピングモードが不明です\n空データを作成して対応します"), TEXT("エラー"), MB_ICONSTOP);

			pNormal[i].pNormalVec = new D3DXVECTOR3[_pMeshData->pVertex->PolygonVertexNum];
			for (int n = 0; n < _pMeshData->pVertex->PolygonVertexNum; n++)
			{
				pNormal[i].pNormalVec->x = 0.0f;
				pNormal[i].pNormalVec->y = 0.0f;
				pNormal[i].pNormalVec->z = 0.0f;
			}
			break;
		}
	}

	_pMeshData->pNormal = pNormal;

	return true;
}

bool FbxLoader::LoadMeshTextureData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData)
{
	
	return true;
}

bool FbxLoader::LoadMeshMaterialData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData)
{
	
	return true;
}

bool FbxLoader::LoadMeshAnimationData(FbxMesh* _pMesh, FbxModel::MeshData* _pMeshData)
{

	return true;
}

void FbxLoader::GetTextureName(
	fbxsdk::FbxSurfaceMaterial* material,
	LPCTSTR matFlag,
	std::vector<LPCTSTR>* pOutFileName,
	std::vector<fbxsdk::FbxString>* pOutUvSetName,
	int* OutCount)
{
	fbxsdk::FbxProperty Property = material->FindProperty(matFlag);
	int LayerTextureCount = Property.GetSrcObjectCount<fbxsdk::FbxLayeredTexture>();

	if (LayerTextureCount == 0)
	{
		int TextureCount = Property.GetSrcObjectCount<fbxsdk::FbxFileTexture>();
		for (int i = 0; i < TextureCount; ++i)
		{
			(*OutCount)++;
			fbxsdk::FbxFileTexture* fbxTexture = FbxCast<fbxsdk::FbxFileTexture>(Property.GetSrcObject<fbxsdk::FbxFileTexture>(i));
			pOutUvSetName->push_back(fbxTexture->UVSet.Get());
			pOutFileName->push_back(fbxTexture->GetRelativeFileName());
		}
	}
}

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
	m_pFbxManager->Destroy();
}

void FbxLoader::ReleaseFbxScene()
{
	m_pFbxScene->Destroy();
}

void FbxLoader::ReleaseFbxImporter()
{
	m_pFbxImporter->Destroy();
}

void FbxLoader::ReleaseFbxIOSettings()
{
	m_pFbxIOSettings->Destroy();
}


