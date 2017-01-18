/**
 * @file   MainCamera.h
 * @brief  MainCameraクラスのヘッダファイル
 * @author kotani
 */
#ifndef MAINCAMERA_H
#define MAINCAMERA_H
#include <D3DX11.h>
#include <D3DX10.h>
#include "InputDeviceManager\InputDeviceManager.h"
#include "Camera\Camera.h"

/**
 * カメラを操作するクラス
 */
class MainCamera
{
public:
	/**
	 * インスタンスを生成する関数
	 */
	inline static void Create()
	{
		if (m_pMainCamera == NULL)
		{
			m_pMainCamera = new MainCamera();
		}
	}
	
	/**
	 * インスタンスを取得する関数
	 * @return MainCameraのインスタンス
	 */
	inline static MainCamera* GetInstance()
	{
		return m_pMainCamera;
	}

	/**
	 * インスタンスを破棄する
	 */
	inline static void Delete()
	{
		delete m_pMainCamera;
		m_pMainCamera = NULL;
	}

	/**
	 * MainCameraクラスの制御関数
	 */
	void Control();

	/**
	 * ビュー行列を取得する
	 */
	inline D3DXMATRIX GetViewMatrix()
	{
		return m_pCamera->GetViewMatrix();
	}

	/**
	 * 射影行列を取得する
	 */
	inline D3DXMATRIX GetProjectionMatrix()
	{
		return m_pCamera->GetProjectionMatrix();
	}

	static const float		   m_NearPoint;   //!< 最近点
	static const float		   m_FarPoint;    //!< 最遠点
	static const float		   m_ViewAngle;   //!< 視野角

private:
	/**
	 * カメラのコンスタントバッファ
	 */
	struct CAMERA_CONSTANT_BUFFER
	{
		D3DXMATRIX View;
		D3DXMATRIX Proj;
	};

	/**
	 * MainCameraクラスのコンストラクタ
	 */
	MainCamera();

	/**
	 * MainCameraクラスのデストラクタ
	 */
	~MainCamera();

	/**
	 * 移動処理
	 */
	void Move();

	/**
	 * 回転処理
	 */
	void Rotate();
	
	/**
	 * 回転の計算
	 */
	void RotateCalculate();

	/**
	 * ズームイン・アウト処理
	 */
	void Zoom();

	/**
	 * カメラを前に移動させる関数
	 */
	void MoveFront();
	
	/**
	 * カメラを左に移動させる関数
	 */
	void MoveLeft();
	
	/**
	 * カメラを後ろ移動させる関数
	 */
	void MoveBack();
	
	/**
	 * カメラを右に移動させる関数
	 */
	void MoveRight();

	/**
	 * カメラの動きを反映させる
	 */
	void Transform();

	/**
	 * コンスタントバッファ初期化関数
	 */
	void InitConstantBuffer();

	/**
	 * コンスタントバッファの開放関数
	 */
	void ReleaseConstantBuffer();

	/**
	 * コンスタントバッファへの書き込み関数
	 */
	void WriteConstantBuffer();

	static MainCamera*		   m_pMainCamera;
	static const float		   m_MaxAngle;	  //!< カメラの最大傾き
	static const float		   m_MinAngle;	  //!< カメラの最小傾き
	static const float		   m_MaxLength;	  //!< カメラと注視点の最大距離
	static const float		   m_MinLength;	  //!< カメラと注視点の最小距離
	static const float		   m_MoveSpeedWeight; //!< 移動速度を計算する際の重み
	static const float		   m_ZoomSpeedWeight; //!< ズーム速度を計算する際の重み
	static const float		   m_RotateSpeedWeight; //!< ズーム速度を計算する際の重み

	Camera*					   m_pCamera;
	D3DXVECTOR3				   m_Pos;
	D3DXVECTOR3				   m_LookPoint; //!< カメラの注視点
	D3DXVECTOR2				   m_CameraAngle;
	ID3D11Buffer*			   m_pConstantBuffer;
	MouseDevice::MOUSESTATE	   m_MouseState;
	const KeyDevice::KEYSTATE* m_pKeyState;
	float					   m_MoveSpeed;
	float					   m_ZoomSpeed;
	float					   m_CameraLength; //!< カメラの注視点の距離
	bool					   m_isCameraControl;

};


#endif
