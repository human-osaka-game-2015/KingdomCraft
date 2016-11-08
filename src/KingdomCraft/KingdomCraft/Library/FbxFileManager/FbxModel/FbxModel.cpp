/**
 * @file   FbxModel.cpp
 * @brief  FbxModelクラスの実装
 * @author morimoto
 */
#include "FbxModel.h"


FbxModel::FbxModel(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext) :
m_pDevice(_pDevice),
m_pDeviceContext(_pDeviceContext)
{
}

FbxModel::~FbxModel()
{
}

void FbxModel::AddMeshData(MeshData* _pMeshData)
{
	m_MeshData.push_back(*_pMeshData);
}

bool FbxModel::Init()
{
	if (!InitIndexBuffer())
	{
		OutputDebugString(TEXT("インデックスバッファの初期化に失敗しました\n"));
		return false;
	}

	if (!InitVertexBuffer())
	{
		OutputDebugString(TEXT("頂点バッファの初期化に失敗しました\n"));
		return false;
	}

	return true;
}

void FbxModel::Release()
{
	ReleaseVertexBuffer();
	ReleaseIndexBuffer();

	for (int i = 0; i < m_MeshData.size(); i++)
	{
		delete[] m_MeshData[i].pNormal->pNormalVec;
		delete m_MeshData[i].pNormal;

		delete[] m_MeshData[i].pVertex->pVertex;
		delete[] m_MeshData[i].pVertex->pIndexAry;
		delete m_MeshData[i].pVertex;
	}
	
}

void FbxModel::Draw(int _meshNum)
{
	UINT stride = sizeof(FBXMODEL_VERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_ppVertexBuffer[_meshNum], &stride, &offset);
	m_pDeviceContext->IASetIndexBuffer(m_ppIndexBuffer[_meshNum], DXGI_FORMAT_R32_UINT, 0);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_pDeviceContext->DrawIndexed(m_MeshData[_meshNum].pVertex->PolygonVertexNum, 0, 0);
}

void FbxModel::AnimationDraw()
{

}

void FbxModel::SetAnimationFrame(int _setFrame)
{

}

int FbxModel::GetAnimationFrame()
{
	return 0;
}

bool FbxModel::InitIndexBuffer()
{
	m_ppIndexBuffer = new ID3D11Buffer*[m_MeshData.size()];
	for (int i = 0; i < m_MeshData.size(); i++)
	{
		D3D11_BUFFER_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
		BufferDesc.ByteWidth = sizeof(int) * m_MeshData[i].pVertex->PolygonVertexNum;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.MiscFlags = 0;
		BufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA ResourceData;
		ZeroMemory(&ResourceData, sizeof(ResourceData));
		ResourceData.pSysMem = m_MeshData[i].pVertex->pIndexAry;
		ResourceData.SysMemPitch = 0;
		ResourceData.SysMemSlicePitch = 0;

		if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &ResourceData, &m_ppIndexBuffer[i])))
		{
			OutputDebugString(TEXT("インデックスバッファの作成に失敗しました\n"));
			for (int n = 0; n < i; n++)
			{
				m_ppIndexBuffer[n]->Release();
			}
			delete[] m_ppIndexBuffer;
			return false;
		}
	}

	OutputDebugString(TEXT("インデックスバッファの作成に成功しました\n"));

	return true;
}

bool FbxModel::InitVertexBuffer()
{
	m_ppVertexBuffer = new ID3D11Buffer*[m_MeshData.size()];
	m_ppVertexData = new FBXMODEL_VERTEX*[m_MeshData.size()];
	for (int i = 0; i < m_MeshData.size(); i++)
	{
		m_ppVertexData[i] = new FBXMODEL_VERTEX[m_MeshData[i].pVertex->ControlPositionNum];

		for (int n = 0; n < m_MeshData[i].pVertex->ControlPositionNum; n++)
		{
			m_ppVertexData[i][n].Pos = m_MeshData[i].pVertex->pVertex[n];
			m_ppVertexData[i][n].Normal = m_MeshData[i].pNormal->pNormalVec[n];

			/// @todo インデックスバッファに対するテクスチャ座標の対応がまだなので空データを突っ込んでおく
			m_ppVertexData[i][n].tu = 0.0f;
			m_ppVertexData[i][n].tv = 0.0f;
		}

		D3D11_BUFFER_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
		BufferDesc.ByteWidth = sizeof(FBXMODEL_VERTEX) * m_MeshData[i].pVertex->ControlPositionNum;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA ResourceData;
		ZeroMemory(&ResourceData, sizeof(ResourceData));
		ResourceData.pSysMem = m_ppVertexData[i];
		ResourceData.SysMemPitch = 0;
		ResourceData.SysMemSlicePitch = 0;

		if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &ResourceData, &m_ppVertexBuffer[i])))
		{
			OutputDebugString(TEXT("頂点バッファの作成に失敗しました\n"));
			for (int n = 0; n < i; n++)
			{
				m_ppVertexBuffer[n]->Release();
			}
			delete[] m_ppVertexBuffer;
			return false;
		}
	}

	OutputDebugString(TEXT("頂点バッファの作成に成功しました\n"));

	return true;
}

void FbxModel::ReleaseIndexBuffer()
{
	for (int i = 0; i < m_MeshData.size(); i++)
	{
		m_ppIndexBuffer[i]->Release();
	}
	delete[] m_ppIndexBuffer;
}

void FbxModel::ReleaseVertexBuffer()
{
	for (int i = 0; i < m_MeshData.size(); i++)
	{
		m_ppVertexBuffer[i]->Release();
		delete m_ppVertexData[i];
	}
	delete[] m_ppVertexData;
	delete[] m_ppVertexBuffer;
}
