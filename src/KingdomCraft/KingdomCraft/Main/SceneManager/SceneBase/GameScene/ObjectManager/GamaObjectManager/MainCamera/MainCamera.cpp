/**
 * @file   MainCamera.cpp
 * @brief  MainCameraクラスの実装
 * @author kotani
 */
#include "MainCamera.h"
#include "DX11Manager\DX11Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"

MainCamera* MainCamera::m_pMainCamera = NULL;

const float MainCamera::m_NearPoint = 1.f;
const float MainCamera::m_FarPoint = 5000.f;
const float MainCamera::m_ViewAngle = static_cast<float>(D3DXToRadian(50));
const float MainCamera::m_MaxAngle = 70.f;
const float MainCamera::m_MinAngle = 10.f;
const float MainCamera::m_MaxLength = 3000.f;
const float MainCamera::m_MinLength = 500.f;
const float MainCamera::m_MoveSpeedWeight = 0.001f;
const float MainCamera::m_ZoomSpeedWeight = 0.1f;
const float MainCamera::m_RotateSpeedWeight = 0.22f;


MainCamera::MainCamera() :
m_LookPoint(D3DXVECTOR3(0.f, 0.f, 0.f)),
m_MoveSpeed(0.f),
m_ZoomSpeed(0.f),
m_CameraAngle(0.f, 50.f),
m_CameraLength(1000.f),
m_isCameraControl(false)
{
	RECT ClientRect;
	GetClientRect(DX11Manager::GetInstance()->GetWindowHandle(), &ClientRect);
	m_pCamera = new Camera(static_cast<float>(ClientRect.right), static_cast<float>(ClientRect.bottom), m_NearPoint, m_FarPoint);
	m_pKeyState = InputDeviceManager::GetInstance()->GetKeyState();
	InitConstantBuffer();
	RotateCalculate();

	m_pCamera->TransformView(m_Pos, m_LookPoint, m_ViewAngle);
	WriteConstantBuffer();
	DX11Manager::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_pConstantBuffer);
}

MainCamera::~MainCamera()
{
	ReleaseConstantBuffer();
	delete m_pCamera;
}

void MainCamera::Control()
{
	m_isCameraControl = false;
	m_MouseState = InputDeviceManager::GetInstance()->GetMouseState();
	m_MoveSpeed = m_Pos.y * m_MoveSpeedWeight;
	m_ZoomSpeed = m_Pos.y * m_ZoomSpeedWeight;
	Move();
	Rotate();
	Zoom();

	//カメラが操作されていたらコンスタントバッファを更新する
	if (m_isCameraControl)
	{
		Transform();
	}
}

void MainCamera::Transform()
{
	m_pCamera->TransformView(m_Pos, m_LookPoint, m_ViewAngle);
	WriteConstantBuffer();
	DX11Manager::GetInstance()->GetDeviceContext()->VSSetConstantBuffers(1, 1, &m_pConstantBuffer);
	DX11Manager::GetInstance()->GetDeviceContext()->PSSetConstantBuffers(1, 1, &m_pConstantBuffer);
}

void MainCamera::Move()
{
	if (m_pKeyState[DIK_W] == KeyDevice::KEYSTATE::KEY_ON)
	{
		MoveFront();
		m_isCameraControl = true;
	}
	if (m_pKeyState[DIK_A] == KeyDevice::KEYSTATE::KEY_ON)
	{
		MoveLeft();
		m_isCameraControl = true;
	}
	if (m_pKeyState[DIK_S] == KeyDevice::KEYSTATE::KEY_ON)
	{
		MoveBack();
		m_isCameraControl = true;
	}
	if (m_pKeyState[DIK_D] == KeyDevice::KEYSTATE::KEY_ON)
	{
		MoveRight();
		m_isCameraControl = true;
	}
}

void MainCamera::Rotate()
{
	if (m_MouseState.rgbButtons[1] == MouseDevice::MOUSEBUTTONSTATE::MOUSEBUTTON_ON)
	{

		m_CameraAngle.x += static_cast<float>(m_MouseState.lX * m_RotateSpeedWeight);
		m_CameraAngle.y += static_cast<float>(m_MouseState.lY * m_RotateSpeedWeight);

		//xはカメラを回していると増え続けたり減り続けたりするので一周すると0に戻す
		if (fabs(m_CameraAngle.x) >= 360)
		{
			m_CameraAngle.x = 0;
		}
		
		//カメラの角度制限チェック---------------
		if (m_CameraAngle.y >= m_MaxAngle)
		{
			m_CameraAngle.y = m_MaxAngle;
		}

		if (m_CameraAngle.y <= m_MinAngle)
		{
			m_CameraAngle.y = m_MinAngle;
		}
		//------------------------------------
		RotateCalculate();
		m_isCameraControl = true;
	}
}

void MainCamera::RotateCalculate()
{
	m_Pos.x = m_LookPoint.x + -m_CameraLength * sin(static_cast<float>(D3DXToRadian(m_CameraAngle.x)));
	m_Pos.z = m_LookPoint.z + -m_CameraLength * cos(static_cast<float>(D3DXToRadian(m_CameraAngle.x)));
	m_Pos.y = m_LookPoint.y + -m_CameraLength * sin(static_cast<float>(D3DXToRadian(-m_CameraAngle.y)));
}

void MainCamera::Zoom()
{
	if (m_MouseState.lZ > 0)
	{
		m_CameraLength -= m_ZoomSpeed;
		if (m_CameraLength < m_MinLength)
		{
			m_CameraLength = m_MinLength;
		}
		RotateCalculate();
		m_isCameraControl = true;
	}
	else if (m_MouseState.lZ < 0)
	{
		m_CameraLength += m_ZoomSpeed;
		if (m_CameraLength > m_MaxLength)
		{
			m_CameraLength = m_MaxLength;
		}
		RotateCalculate();
		m_isCameraControl = true;
	}
}

void MainCamera::MoveFront()
{
	float moveX = m_MoveSpeed * sin(static_cast<float>(D3DXToRadian(m_CameraAngle.x)));
	float moveZ = m_MoveSpeed * cos(static_cast<float>(D3DXToRadian(m_CameraAngle.x)));
	m_Pos.x += moveX;
	m_Pos.z += moveZ;
	m_LookPoint.x += moveX;
	m_LookPoint.z += moveZ;
}

void MainCamera::MoveLeft()
{
	float moveX = m_MoveSpeed * sin(static_cast<float>(D3DXToRadian(m_CameraAngle.x - 90)));
	float moveZ = m_MoveSpeed * cos(static_cast<float>(D3DXToRadian(m_CameraAngle.x - 90)));
	m_Pos.x += moveX;
	m_Pos.z += moveZ;
	m_LookPoint.x += moveX;
	m_LookPoint.z += moveZ;
}

void MainCamera::MoveBack()
{
	float moveX = m_MoveSpeed * sin(static_cast<float>(D3DXToRadian(m_CameraAngle.x + 180)));
	float moveZ = m_MoveSpeed * cos(static_cast<float>(D3DXToRadian(m_CameraAngle.x + 180)));
	m_Pos.x += moveX;
	m_Pos.z += moveZ;
	m_LookPoint.x += moveX;
	m_LookPoint.z += moveZ;
}

void MainCamera::MoveRight()
{
	float moveX = m_MoveSpeed * sin(static_cast<float>(D3DXToRadian(m_CameraAngle.x + 90)));
	float moveZ = m_MoveSpeed * cos(static_cast<float>(D3DXToRadian(m_CameraAngle.x + 90)));
	m_Pos.x += moveX;
	m_Pos.z += moveZ;
	m_LookPoint.x += moveX;
	m_LookPoint.z += moveZ;
}

void MainCamera::InitConstantBuffer()
{
	D3D11_BUFFER_DESC ConstantBufferDesc;
	ConstantBufferDesc.ByteWidth = sizeof(CAMERA_CONSTANT_BUFFER);
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
		CAMERA_CONSTANT_BUFFER ConstantBuffer;
		ConstantBuffer.Proj = m_pCamera->GetProjectionMatrix();
		ConstantBuffer.View = m_pCamera->GetViewMatrix();

		D3DXMatrixTranspose(&ConstantBuffer.View, &ConstantBuffer.View);
		D3DXMatrixTranspose(&ConstantBuffer.Proj, &ConstantBuffer.Proj);
		memcpy_s(SubResourceData.pData, SubResourceData.RowPitch, static_cast<void*>(&ConstantBuffer), sizeof(ConstantBuffer));
		DX11Manager::GetInstance()->GetDeviceContext()->Unmap(m_pConstantBuffer, 0);
	}
}
