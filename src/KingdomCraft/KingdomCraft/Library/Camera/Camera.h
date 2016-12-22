/**
 * @file   Camera.h
 * @brief  Cameraクラスのヘッダファイル
 * @author morimoto
 */
#ifndef CAMERA_H
#define CAMERA_H
#include <D3DX10.h>

/**
 * カメラ情報を管理するクラス
 */
class Camera
{
public:
	/**
	 * Cameraクラスのコンストラクタ
	 * @param[in] _windowWidth ウィンドウの幅
	 * @param[in] _windowHeight ウィンドウの高さ
	 * @param[in] _nearZ カメラの最近点
	 * @param[in] _farZ カメラの最遠点
	 */
	Camera(float _windowWidth, float _windowHeight, float _nearZ, float _farZ);

	/**
	 * Cameraクラスのデストラクタ
	 */
	~Camera();

	/**
	 * 座標変換用の行列を作成する関数
	 * @param[in] _eyePos カメラの座標
	 * @param[in] _lookPos カメラの注視座標
	 * @param[in] _viewAngle カメラの視野角
	 */
	void TransformView(D3DXVECTOR3 _eyePos, D3DXVECTOR3 _lookPos, float _viewAngle);

	/**
	 * Cameraクラスが持つビュー座標変換行列を取得する関数
	 * @return ビュー座標変換用行列
	 */
	inline D3DXMATRIX GetViewMatrix()
	{
		return m_MatView;
	}

	/**
	 * Cameraクラスが持つプロジェクション座標変換行列を取得する関数
	 * @return プロジェクション座標変換用行列
	 */
	inline D3DXMATRIX GetProjectionMatrix()
	{
		return m_MatProj;
	}

private:
	D3DXMATRIX	m_MatView;
	D3DXMATRIX	m_MatProj;
	float		m_WindowWidth;
	float		m_WindowHeight;
	float		m_NearZ;
	float		m_FarZ;

};


#endif
