/**
 * @file   MainCamera.cpp
 * @brief  MainCameraクラスの実装
 * @author kotani
 */
#include "MainCamera.h"
#include "Camera\Camera.h"
#include "DX11Manager\DX11Manager.h"

const float MainCamera::m_NearPoint = 1.f;
const float MainCamera::m_FarPoint = 5000.f;
const float MainCamera::m_ViewAngle = static_cast<float>(D3DXToRadian(50));


MainCamera::MainCamera() :
m_Pos(D3DXVECTOR3(0.f,0.f,0.f)),
m_LookPoint(D3DXVECTOR3(0.f, 0.f, 1.f))
{
	RECT ClientRect;
	GetClientRect(DX11Manager::GetInstance()->GetWindowHandle(), &ClientRect);
	m_pCamera = new Camera(static_cast<float>(ClientRect.right), static_cast<float>(ClientRect.bottom), m_NearPoint, m_FarPoint);
	
	InitConstantBuffer();
	m_pCamera->TransformView(m_Pos, m_LookPoint, m_ViewAngle);
	WriteConstantBuffer();
}

MainCamera::~MainCamera()
{
	ReleaseConstantBuffer();
	delete m_pCamera;
}

void MainCamera::Control()
{
	DX11Manager::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_pConstantBuffer);
}

void MainCamera::Move()
{
	/// @todo どう動くかは仕様を聞いてから実装する
}

void MainCamera::InitConstantBuffer()
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ConstantBufferDesc.ByteWidth = sizeof(SHADER_CONSTANT_BUFFER);
	ConstantBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	ConstantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	ConstantBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	ConstantBufferDesc.MiscFlags = 0;
	ConstantBufferDesc.StructureByteStride = 0;
	DX11Manager::GetInstance()->GetDevice()->CreateBuffer(&ConstantBufferDesc, NULL, &m_pConstantBuffer);
}

void MainCamera::ReleaseConstantBuffer()
{
	if (m_pConstantBuffer != NULL)
	{
		m_pConstantBuffer->Release();
		m_pConstantBuffer = NULL;
	}
}

void MainCamera::WriteConstantBuffer()
{
	D3D11_MAPPED_SUBRESOURCE SubResourceData;
	if (SUCCEEDED(DX11Manager::GetInstance()->GetDeviceContext()->Map(m_pConstantBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &SubResourceData)))
	{
		SHADER_CONSTANT_BUFFER ConstantBuffer;
		ConstantBuffer.Proj = m_pCamera->GetProjectionMatrix();
		ConstantBuffer.View = m_pCamera->GetViewMatrix();

		D3DXMatrixTranspose(&ConstantBuffer.View, &ConstantBuffer.View);
		D3DXMatrixTranspose(&ConstantBuffer.Proj, &ConstantBuffer.Proj);
		memcpy_s(SubResourceData.pData, SubResourceData.RowPitch, static_cast<void*>(&ConstantBuffer), sizeof(ConstantBuffer));
		DX11Manager::GetInstance()->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);
	}
}
