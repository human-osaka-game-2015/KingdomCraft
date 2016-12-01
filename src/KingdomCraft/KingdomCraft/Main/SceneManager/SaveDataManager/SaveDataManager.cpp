/**
 * @file   SaveDataManager.cpp
 * @brief  SaveDataManagerクラスの実装
 * @author kotani
 */
#include "SaveDataManager.h"

SaveDataManager* SaveDataManager::m_pSaveDataManager = NULL;


SaveDataManager::SaveDataManager() :
m_pFile(NULL),
m_pBuffer(NULL),
m_pTmpBuffer(NULL)
{
}

SaveDataManager::~SaveDataManager()
{
}

void SaveDataManager::FileLoad(LPCTSTR _pFileName)
{
	ReleaseLoadBuffer();
	fopen_s(&m_pFile, _pFileName, "r");
	fseek(m_pFile, 0, SEEK_END);
	m_FileSize = ftell(m_pFile);
	fseek(m_pFile, 0, SEEK_SET);

	m_pBuffer = new TCHAR[m_FileSize];
	m_pTmpBuffer = new TCHAR[m_FileSize];
	memset(m_pBuffer, '\0', m_FileSize);
	memset(m_pTmpBuffer, '\0', m_FileSize);

	fread(m_pBuffer, m_FileSize, 1, m_pFile);
	fclose(m_pFile);
}

void SaveDataManager::FileSave(LPCTSTR _pFileName)
{
	fopen_s(&m_pFile, _pFileName, "w");

	m_StrBuffer += '\0';
	fprintf_s(m_pFile, m_StrBuffer.c_str());
	ReleaseWriteBuffer();
	fclose(m_pFile);
}

void SaveDataManager::WriteData(LPCTSTR _pGroupName, std::vector<int>* _pData)
{
	m_StrBuffer = m_StrBuffer + _pGroupName + '{';
	for (unsigned int i = 0; i < _pData->size(); i++)
	{
		m_StrBuffer = m_StrBuffer + std::to_string((*_pData)[i]) + ',';
	}
	m_StrBuffer = m_StrBuffer + "}\n";
}

void SaveDataManager::WriteData(LPCTSTR _pGroupName, std::vector<float>* _pData)
{
	m_StrBuffer = m_StrBuffer + _pGroupName + '{';
	for (unsigned int i = 0; i < _pData->size(); i++)
	{
		m_StrBuffer = m_StrBuffer + std::to_string((*_pData)[i]) + ',';
	}
	m_StrBuffer = m_StrBuffer + "}\n";
}

void SaveDataManager::WriteData(LPCTSTR _pGroupName, std::vector<std::string>* _pData)
{
	m_StrBuffer = m_StrBuffer + _pGroupName + '{';
	for (unsigned int i = 0; i < _pData->size(); i++)
	{
		m_StrBuffer = m_StrBuffer + (*_pData)[i] + ',';
	}
	m_StrBuffer = m_StrBuffer + "}\n";
}

bool SaveDataManager::ReadData(LPCTSTR _pGroupName, std::vector<int>* _pData)
{
	TCHAR* pContext;

	TCHAR* pBuffer = strstr(m_pBuffer, _pGroupName);
	if (pBuffer == NULL)
	{
		return false;
	}

	strcpy_s(m_pTmpBuffer, m_FileSize, pBuffer);
	//見つけたグループを終わりまで取ってくる
	strcpy_s(m_pTmpBuffer, m_FileSize, strtok_s(m_pTmpBuffer, "}", &pContext));

	//最初のグループ名はいらないので保存しない
	strtok_s(m_pTmpBuffer, "{,", &pContext);

	while (1)
	{
		pBuffer = strtok_s(NULL, "{,", &pContext);

		if (pBuffer == NULL)
		{
			break;
		}
		else
		{
			_pData->push_back(atoi(pBuffer));
		}
	}
	return true;
}

bool SaveDataManager::ReadData(LPCTSTR _pGroupName, std::vector<float>* _pData)
{
	TCHAR* pContext;

	TCHAR* pBuffer = strstr(m_pBuffer, _pGroupName);
	if (pBuffer == NULL)
	{
		return false;
	}

	strcpy_s(m_pTmpBuffer, m_FileSize, pBuffer);
	//見つけたグループを終わりまで取ってくる
	strcpy_s(m_pTmpBuffer, m_FileSize, strtok_s(m_pTmpBuffer, "}", &pContext));

	//最初のグループ名はいらないので保存しない
	strtok_s(m_pTmpBuffer, "{,", &pContext);

	while (1)
	{
		pBuffer = strtok_s(NULL, "{,", &pContext);

		if (pBuffer == NULL)
		{
			break;
		}
		else
		{
			_pData->push_back(static_cast<float>(atof(pBuffer)));
		}
	}
	return true;
}

bool SaveDataManager::ReadData(LPCTSTR _pGroupName, std::vector<std::string>* _pData)
{
	TCHAR* pContext;

	TCHAR* pBuffer = strstr(m_pBuffer, _pGroupName);
	if (pBuffer == NULL)
	{
		return false;
	}

	strcpy_s(m_pTmpBuffer, m_FileSize, pBuffer);
	//見つけたグループを終わりまで取ってくる
	strcpy_s(m_pTmpBuffer, m_FileSize, strtok_s(m_pTmpBuffer, "}", &pContext));

	//最初のグループ名はいらないので保存しない
	strtok_s(m_pTmpBuffer, "{,", &pContext);

	while (1)
	{
		pBuffer = strtok_s(NULL, "{,", &pContext);

		if (pBuffer == NULL)
		{
			break;
		}
		else
		{
			_pData->push_back(pBuffer);
		}
	}
	return true;
}

void SaveDataManager::ReleaseLoadBuffer()
{
	delete[] m_pBuffer;
	m_pBuffer = NULL;

	delete[] m_pTmpBuffer;
	m_pTmpBuffer = NULL;
}

void SaveDataManager::ReleaseWriteBuffer()
{
	m_StrBuffer.clear();
}
