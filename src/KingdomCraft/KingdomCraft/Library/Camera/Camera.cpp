/**
 * @file   Camera.cpp
 * @brief  Cameraクラスの実装
 * @author morimoto
 */
#include "Camera.h"


//----------------------------------------------------------------------------------------------------
// Constructor	Destructor
//----------------------------------------------------------------------------------------------------

Camera::Camera(float _windowWidth, float _windowHeight, float _nearZ, float _farZ)
{
	m_WindowWidth = _windowWidth;
	m_WindowHeight = _windowHeight;
	m_NearZ = _nearZ;
	m_FarZ = _farZ;
}

Camera::~Camera()
{
}


//----------------------------------------------------------------------------------------------------
// Public Functions
//----------------------------------------------------------------------------------------------------

void Camera::TransformView(D3DXVECTOR3 _eyePos, D3DXVECTOR3 _lookPos, float _viewAngle)
{
	// ビュー座標変換行列の作成
	D3DXVECTOR3 UpVec = D3DXVECTOR3(0, 1, 0);
	D3DXMatrixLookAtLH(&m_MatView, &_eyePos, &_lookPos, &UpVec);

	// プロジェクション座標変換行列の作成
	float Aspect = m_WindowWidth / m_WindowHeight;
	D3DXMatrixPerspectiveFovLH(&m_MatProj, static_cast<float>(D3DXToRadian(_viewAngle)), Aspect, m_NearZ, m_FarZ);
}
