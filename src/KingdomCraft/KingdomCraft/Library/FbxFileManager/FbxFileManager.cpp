/**
 * @file   FbxFileManager.cpp
 * @brief  FbxFileManagerクラスの実装
 * @author morimoto
 */
#include "FbxFileManager.h"
#include "FbxLoader\FbxLoader.h"

const int FbxFileManager::m_InvalidIndex = 0;
FbxFileManager* FbxFileManager::m_pFbxFileManager = NULL;


FbxFileManager::FbxFileManager(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext) :
m_pDevice(_pDevice),
m_pDeviceContext(_pDeviceContext)
{
	m_pFbxModel.push_back(NULL);	// 読み込みに失敗した際に参照する値としてNULLを追加
}

FbxFileManager::~FbxFileManager()
{
}

bool FbxFileManager::Init()
{
	m_pFbxLoader = new FbxLoader(m_pDevice);
	return m_pFbxLoader->Init();
}

void FbxFileManager::Release()
{
	m_pFbxLoader->Release();
	delete m_pFbxLoader;
}

bool FbxFileManager::LoadFbxModel(LPCTSTR _pFileName, int* _pIndex)
{
	FbxModel* pModel = new FbxModel(m_pDevice, m_pDeviceContext);
	if (!m_pFbxLoader->LoadFbxModel(pModel, _pFileName))
	{
		OutputDebugString(TEXT("Fbxモデルの読み込みに失敗しました\n"));
		*_pIndex = m_InvalidIndex;
		delete pModel;
		return false;
	}

	pModel->Init();
	*_pIndex = m_pFbxModel.size();
	m_pFbxModel.push_back(pModel);

	return true;
}

void FbxFileManager::ReleaseFbxModel(int _index)
{
	if (m_pFbxModel[_index] != NULL)
	{
		m_pFbxModel[_index]->Release();
		delete m_pFbxModel[_index];
		m_pFbxModel[_index] = NULL;
	}
}
