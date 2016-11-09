/**
　* @file   ShaderManager.cpp
　* @brief  ShaderManagerクラスの実装
　* @author morimoto
　*/
#include "ShaderManager.h"
#include "d3dx11.h"


ShaderManager* ShaderManager::m_pShaderManager = NULL;

ShaderManager::ShaderManager(ID3D11Device* _pDevice) :
m_pDevice(_pDevice)
{
}

ShaderManager::~ShaderManager()
{
}

bool ShaderManager::LoadVertexShader(LPCTSTR _fileName, LPCTSTR _funcName, int* _pOutKey)
{
	ID3D11VertexShader* pVertexShader = NULL;
	ID3DBlob* pShaderErrors = NULL;
	ID3DBlob* pCompiledShader = NULL;
	if (FAILED(D3DX11CompileFromFile(
		_fileName,
		NULL,
		NULL,
		_funcName,
		"vs_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pShaderErrors,
		NULL)))
	{
		if (pShaderErrors != NULL) pShaderErrors->Release();
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
		return false;
	}

	*_pOutKey = m_pVertexShader.size();
	m_pVertexShader.push_back(pVertexShader);
	m_pCompiledVertexShader.push_back(pCompiledShader);

	return true;
}

bool ShaderManager::LoadPixelShader(LPCTSTR _fileName, LPCTSTR _funcName, int* _pOutKey)
{
	ID3D11PixelShader* pPixelShader = NULL;
	ID3DBlob* pShaderErrors = NULL;
	ID3DBlob* pCompiledShader = NULL;
	if (FAILED(D3DX11CompileFromFile(
		_fileName,
		NULL,
		NULL,
		_funcName,
		"ps_5_0",
		D3D10_SHADER_DEBUG | D3D10_SHADER_SKIP_OPTIMIZATION,
		0,
		NULL,
		&pCompiledShader,
		&pShaderErrors,
		NULL)))
	{
		if (pShaderErrors != NULL) pShaderErrors->Release();
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
		return false;
	}

	*_pOutKey = m_pPixelShader.size();
	m_pPixelShader.push_back(pPixelShader);
	m_pCompiledPixelShader.push_back(pCompiledShader);

	return true;
}
