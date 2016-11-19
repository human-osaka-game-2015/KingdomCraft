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

void FbxModel::AddMeshData(MESH_DATA* _pMeshData)
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

	for (unsigned int i = 0; i < m_MeshData.size(); i++)
	{
		delete[] m_MeshData[i].pNormalData->pNormalVec;
		m_MeshData[i].pNormalData->pNormalVec = NULL;

		delete m_MeshData[i].pNormalData;
		m_MeshData[i].pNormalData = NULL;

		delete[] m_MeshData[i].pVertexData->pVertex;
		m_MeshData[i].pVertexData->pVertex = NULL;

		delete[] m_MeshData[i].pVertexData->pIndexAry;
		m_MeshData[i].pVertexData->pIndexAry = NULL;

		delete m_MeshData[i].pVertexData;
		m_MeshData[i].pVertexData = NULL;
	}
}

void FbxModel::Draw(int _meshNum)
{
	UINT stride = sizeof(FBXMODEL_VERTEX);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_ppVertexBuffer[_meshNum], &stride, &offset);
	m_pDeviceContext->IASetIndexBuffer(m_ppIndexBuffer[_meshNum], DXGI_FORMAT_R32_UINT, 0);
	m_pDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	m_pDeviceContext->DrawIndexed(m_MeshData[_meshNum].pVertexData->PolygonVertexNum, 0, 0);
}

void FbxModel::AnimationDraw()
{
	/// @todo アニメーション情報の取得がまだなので未実装
}

void FbxModel::SetAnimationFrame(int _setFrame)
{
	/// @todo アニメーション情報の取得がまだなので未実装
}

int FbxModel::GetAnimationFrame()
{
	/// @todo アニメーション情報の取得がまだなので未実装(とりあえず0だけ返す)
	return 0;
}

bool FbxModel::InitIndexBuffer()
{
	m_ppIndexBuffer = new ID3D11Buffer*[m_MeshData.size()];

	for (unsigned int MeshIndex = 0; MeshIndex < m_MeshData.size(); MeshIndex++)
	{
		int PolygonVertexNum = m_MeshData[MeshIndex].pVertexData->PolygonVertexNum;	// メッシュの総頂点数

		D3D11_BUFFER_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
		BufferDesc.ByteWidth = sizeof(int) * PolygonVertexNum;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.MiscFlags = 0;
		BufferDesc.StructureByteStride = 0;

		D3D11_SUBRESOURCE_DATA ResourceData;
		ZeroMemory(&ResourceData, sizeof(ResourceData));
		ResourceData.pSysMem = m_MeshData[MeshIndex].pVertexData->pIndexAry;
		ResourceData.SysMemPitch = 0;
		ResourceData.SysMemSlicePitch = 0;

		if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &ResourceData, &m_ppIndexBuffer[MeshIndex])))
		{
			OutputDebugString(TEXT("インデックスバッファの作成に失敗しました\n"));
			for (unsigned int i = 0; i < MeshIndex; i++)
			{
				m_ppIndexBuffer[i]->Release();
			}
			delete[] m_ppIndexBuffer;
			m_ppIndexBuffer = NULL;
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

	for (unsigned int MeshIndex = 0; MeshIndex < m_MeshData.size(); MeshIndex++)
	{
		int ControlPositionNum = m_MeshData[MeshIndex].pVertexData->ControlPositionNum;	// メッシュのインデックスバッファが指す総頂点数
		D3DXVECTOR3* pVertex = m_MeshData[MeshIndex].pVertexData->pVertex;				// メッシュが持つ頂点座標の配列
		D3DXVECTOR3* pNormal = m_MeshData[MeshIndex].pNormalData->pNormalVec;			// メッシュが持つ法線ベクトルの配列

		m_ppVertexData[MeshIndex] = new FBXMODEL_VERTEX[ControlPositionNum];

		for (int i = 0; i < ControlPositionNum; i++)
		{
			m_ppVertexData[MeshIndex][i].Pos = pVertex[i];
			m_ppVertexData[MeshIndex][i].Normal = pNormal[i];

			/// @todo インデックスバッファに対するテクスチャ座標の対応がまだなので空データを突っ込んでおく
			m_ppVertexData[MeshIndex][i].Texel.x = 0.0f;
			m_ppVertexData[MeshIndex][i].Texel.y = 0.0f;
		}
		
		D3D11_BUFFER_DESC BufferDesc;
		ZeroMemory(&BufferDesc, sizeof(D3D11_BUFFER_DESC));
		BufferDesc.ByteWidth = sizeof(FBXMODEL_VERTEX) * ControlPositionNum;
		BufferDesc.Usage = D3D11_USAGE_DEFAULT;
		BufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		BufferDesc.CPUAccessFlags = 0;
		BufferDesc.MiscFlags = 0;

		D3D11_SUBRESOURCE_DATA ResourceData;
		ZeroMemory(&ResourceData, sizeof(ResourceData));
		ResourceData.pSysMem = m_ppVertexData[MeshIndex];
		ResourceData.SysMemPitch = 0;
		ResourceData.SysMemSlicePitch = 0;

		if (FAILED(m_pDevice->CreateBuffer(&BufferDesc, &ResourceData, &m_ppVertexBuffer[MeshIndex])))
		{
			OutputDebugString(TEXT("頂点バッファの作成に失敗しました\n"));
			for (unsigned int i = 0; i < MeshIndex; i++)
			{
				m_ppVertexBuffer[i]->Release();
			}
			delete[] m_ppVertexBuffer;
			m_ppVertexBuffer = NULL;

			return false;
		}
	}

	OutputDebugString(TEXT("頂点バッファの作成に成功しました\n"));

	return true;
}

void FbxModel::ReleaseIndexBuffer()
{
	if (m_ppIndexBuffer != NULL)
	{
		for (unsigned int i = 0; i < m_MeshData.size(); i++)
		{
			m_ppIndexBuffer[i]->Release();
		}
		delete[] m_ppIndexBuffer;
		m_ppIndexBuffer = NULL;
	}
}

void FbxModel::ReleaseVertexBuffer()
{
	if (m_ppVertexBuffer != NULL)
	{
		for (unsigned int i = 0; i < m_MeshData.size(); i++)
		{
			delete m_ppVertexData[i];
			m_ppVertexData[i] = NULL;
		}
		delete[] m_ppVertexData;
		m_ppVertexData = NULL;
	}
	
	if (m_ppVertexBuffer != NULL)
	{
		for (unsigned int i = 0; i < m_MeshData.size(); i++)
		{
			m_ppVertexBuffer[i]->Release();
			delete[] m_ppVertexBuffer;
			m_ppVertexBuffer = NULL;
		}
	}
}
