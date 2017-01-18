/**
 * @file   MousePosConverter.cpp
 * @brief  MousePosConverterクラスの実装
 * @author kotani
 */
#include "MousePosConverter.h"
#include "..\MainCamera\MainCamera.h"
#include "Camera\Camera.h"
#include "DX11Manager\DX11Manager.h"
#include "InputDeviceManager\InputDeviceManager.h"

MousePosConverter* MousePosConverter::m_pMousePosConverter = NULL;


MousePosConverter::MousePosConverter() :
m_ConvertPos(D3DXVECTOR3(0.f, 0.f, 0.f))
{
	RECT ClientRect;
	GetClientRect(DX11Manager::GetInstance()->GetWindowHandle(), &ClientRect);
	m_ClientWidth = static_cast<float>(ClientRect.right);
	m_ClientHeight = static_cast<float>(ClientRect.bottom);
}

MousePosConverter::~MousePosConverter()
{
}

void MousePosConverter::Control()
{
	D3DXVECTOR3 NearPos;
	D3DXVECTOR3 FarPos;

	NearPos.x = static_cast<float>(InputDeviceManager::GetInstance()->GetMouseState().CursorPos.x);
	NearPos.y = static_cast<float>(InputDeviceManager::GetInstance()->GetMouseState().CursorPos.y);

	FarPos = NearPos;
	NearPos.z = 0.f;
	FarPos.z = 1.f;

	Transform2D(&NearPos);
	Transform2D(&FarPos);

	//近い場合と遠い場合の点から線を作る
	D3DXVECTOR3 Ray = FarPos - NearPos;
	D3DXVec3Normalize(&Ray, &Ray);

	float Dot0 = D3DXVec3Dot(&-NearPos, &D3DXVECTOR3(0.f, 1.f, 0.f));
	float Dot1 = D3DXVec3Dot(&Ray, &D3DXVECTOR3(0.f, 1.f, 0.f));

	m_ConvertPos = NearPos + (Dot0 / Dot1) * Ray;
}

void MousePosConverter::Transform2D(D3DXVECTOR3* _pConvertPos)
{
	//マウス座標×逆ポート×逆射影行列×逆ビュー行列で2d座標を3dに変換出来る
	D3DXMATRIX InvView, InvProjection, InvViewport;
	D3DXMATRIX ViewPort;

	D3DXMatrixInverse(&InvView, NULL, &MainCamera::GetInstance()->GetViewMatrix());
	D3DXMatrixInverse(&InvProjection, NULL, &MainCamera::GetInstance()->GetProjectionMatrix());
	D3DXMatrixIdentity(&ViewPort);
	ViewPort._11 = m_ClientWidth / 2.f;
	ViewPort._22 = -m_ClientHeight / 2.f;
	ViewPort._41 = m_ClientWidth / 2.f;
	ViewPort._42 = m_ClientHeight / 2.f;
	D3DXMatrixInverse(&InvViewport, NULL, &ViewPort);

	D3DXMATRIX InvMat = InvViewport * InvProjection * InvView;
	D3DXVec3TransformCoord(_pConvertPos, _pConvertPos, &InvMat);
}
