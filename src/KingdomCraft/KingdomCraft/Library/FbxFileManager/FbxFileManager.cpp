/**
 * @file   FbxFileManager.cpp
 * @brief  FbxFileManagerクラスの実装
 * @author morimoto
 */
#include "FbxFileManager.h"
#include "FbxLoader\FbxLoader.h"

FbxFileManager::FbxFileManager(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext) :
m_pDevice(_pDevice),
m_pDeviceContext(_pDeviceContext),
m_pFbxLoader(new FbxLoader(_pDevice))
{
}

FbxFileManager::~FbxFileManager()
{
	delete m_pFbxLoader;
}

bool FbxFileManager::Init()
{
	return m_pFbxLoader->Init();
}

void FbxFileManager::Release()
{
	m_pFbxLoader->Release();
}

bool FbxFileManager::LoadFbxModel(LPCTSTR _filePath, int* _pOutKey)
{
	FbxModel* pModel = new FbxModel(m_pDevice, m_pDeviceContext);
	if (!m_pFbxLoader->LoadFbxModel(pModel, _filePath))
	{
		OutputDebugString(TEXT("Fbxモデルの読み込みに失敗しました\n"));
		delete pModel;
		return false;
	}

	pModel->Init();
	*_pOutKey = m_pFbxModel.size();
	m_pFbxModel.push_back(pModel);

	return true;
}

