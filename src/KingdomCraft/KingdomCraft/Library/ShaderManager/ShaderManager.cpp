/**
 * @file   ShaderManager.cpp
 * @brief  ShaderManagerクラスの実装
 * @author morimoto
 */
#include "ShaderManager.h"


//----------------------------------------------------------------------------------------------------
// Static Public Variables
//----------------------------------------------------------------------------------------------------

const int ShaderManager::m_InvalidIndex = 0;


//----------------------------------------------------------------------------------------------------
// Static Private Variables
//----------------------------------------------------------------------------------------------------

ShaderManager* ShaderManager::m_pShaderManager = NULL;


//----------------------------------------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------------------------------------

ShaderManager::ShaderManager(ID3D11Device* _pDevice) :
m_pDevice(_pDevice)
{
	// 読み込みに失敗した際に参照する値としてNULLを追加
	m_pVertexShader.push_back(NULL);
	m_pPixelShader.push_back(NULL);
	m_pCompiledVertexShader.push_back(NULL);
	m_pCompiledPixelShader.push_back(NULL);
}

ShaderManager::~ShaderManager()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

bool ShaderManager::LoadVertexShader(LPCTSTR _pFileName, LPCTSTR _pFuncName, int* _pIndex)
{
	ID3D11VertexShader* pVertexShader = NULL;
	ID3DBlob* pShaderErrors = NULL;
	ID3DBlob* pCompiledShader = NULL;
	if (FAILED(D3DX11CompileFromFile(
		_pFileName,
		NULL,
		NULL,
		_pFuncName,
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pShaderErrors,
		NULL)))
	{
		if (pShaderErrors != NULL) pShaderErrors->Release();
		*_pIndex = m_InvalidIndex;
		return false;
	}

	if (pShaderErrors != NULL) pShaderErrors->Release();


	if (FAILED(m_pDevice->CreateVertexShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&pVertexShader)))
	{
		pCompiledShader->Release();
		*_pIndex = m_InvalidIndex;
		return false;
	}

	*_pIndex = m_pVertexShader.size();
	m_pVertexShader.push_back(pVertexShader);
	m_pCompiledVertexShader.push_back(pCompiledShader);

	return true;
}

bool ShaderManager::LoadPixelShader(LPCTSTR _pFileName, LPCTSTR _pFuncName, int* _pIndex)
{
	ID3D11PixelShader* pPixelShader = NULL;
	ID3DBlob* pShaderErrors = NULL;
	ID3DBlob* pCompiledShader = NULL;
	if (FAILED(D3DX11CompileFromFile(
		_pFileName,
		NULL,
		NULL,
		_pFuncName,
		"ps_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pShaderErrors,
		NULL)))
	{
		if (pShaderErrors != NULL) pShaderErrors->Release();
		*_pIndex = m_InvalidIndex;
		return false;
	}

	if (pShaderErrors != NULL) pShaderErrors->Release();

	if (FAILED(m_pDevice->CreatePixelShader(
		pCompiledShader->GetBufferPointer(),
		pCompiledShader->GetBufferSize(),
		NULL,
		&pPixelShader)))
	{
		pCompiledShader->Release();
		*_pIndex = m_InvalidIndex;
		return false;
	}

	*_pIndex = m_pPixelShader.size();
	m_pPixelShader.push_back(pPixelShader);
	m_pCompiledPixelShader.push_back(pCompiledShader);

	return true;
}

void ShaderManager::ReleaseVertexShader(int _index)
{
	if (m_pVertexShader[_index] != NULL)
	{
		m_pVertexShader[_index]->Release();
		m_pVertexShader[_index] = NULL;
		m_pCompiledVertexShader[_index]->Release();
		m_pCompiledVertexShader[_index] = NULL;
	}
}

void ShaderManager::ReleasePixelShader(int _index)
{
	if (m_pPixelShader[_index] != NULL)
	{
		m_pPixelShader[_index]->Release();
		m_pPixelShader[_index] = NULL;
		m_pCompiledPixelShader[_index]->Release();
		m_pCompiledPixelShader[_index] = NULL;
	}
}
