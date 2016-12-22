/**
 * @file   MainCamera.h
 * @brief  MainCameraクラスのヘッダファイル
 * @author kotani
 */
#ifndef MAINCAMERA_H
#define MAINCAMERA_H
#include <D3DX11.h>
#include <D3DX10.h>

class Camera;

/**
 * カメラを操作するクラス
 */
class MainCamera
{
public:
	/**
	 * MainCameraクラスのコンストラクタ
	 */
	MainCamera();
	
	/**
	 * MainCameraクラスのデストラクタ
	 */
	~MainCamera();

	/**
	 * MainCameraクラスの制御関数
	 */
	void Control();

private:
	MainCamera(const MainCamera&);
	void operator=(const MainCamera&);

	/**
	 * シェーダー用コンスタントバッファ
	 */
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX View;
		D3DXMATRIX Proj;
	};

	/**
	 * カメラを移動させる関数
	 */
	void Move();

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

	static const float		 m_NearPoint;   //!< カメラの最近点
	static const float		 m_FarPoint;    //!< カメラの最遠点
	static const float		 m_ViewAngle;   //!< カメラの視野角

	Camera*					 m_pCamera;
	D3DXVECTOR3				 m_LookPoint; //!< カメラの注視点
	D3DXVECTOR3				 m_Pos;
	ID3D11Buffer*			 m_pConstantBuffer;

};


#endif
