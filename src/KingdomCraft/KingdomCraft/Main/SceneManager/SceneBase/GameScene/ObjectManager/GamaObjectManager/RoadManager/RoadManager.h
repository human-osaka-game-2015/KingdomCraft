/**
 * @file   RoadManager.h
 * @brief  RoadManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef ROADMANAGER_H
#define ROADMANAGER_H
#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>
#include "InputDeviceManager\InputDeviceManager.h"

class BuildAreaManager;
class Road;

/**
 * 道を管理するクラス
 */
class RoadManager
{
public:
	/**
	 * RoadManagerクラスのコンストラクタ
	 */
	RoadManager();

	/**
	 * RoadManagerクラスのデストラクタ
	 */
	~RoadManager();
	
	/**
	 * RoadManagerクラスの制御関数
	 */
	void Control();
	
	/**
	 * RoadManagerクラスの描画関数
	 */
	void Draw();

	/**
	 * ビルドモード時の制御関数
	 */
	void BuildControl();

private:
	RoadManager(const RoadManager&);
	void operator=(const RoadManager&);
	
	/**
	* 始点をセットする時の処理
	*/
	void StartSetStep();

	/**
	* 終点をセットする時の処理
	*/
	void EndSetStep();

	/**
	* 曲線を敷く際の中点をセットする時の処理
	*/
	void MiddleSetStep();

	/**
	* 道の生成をするの処理
	*/
	void CreateStep();

	enum STEP
	{
		NONE,
		START_SET_STEP,
		END_SET_STEP,
		MIDDLE_SET_STEP,
		CREATE_STEP
	};

	BuildAreaManager*		m_pBuildAreaManager;
	std::vector<Road*>		m_pRoad;
	int						m_VertexShaderIndex;
	int						m_PixelShaderIndex;
	float					m_CreateAreaX; //<! 道を作ることが出来るx座標の範囲
	float					m_CreateAreaZ; //<! 道を作ることが出来るz座標の範囲
	STEP					m_Step;
	D3DXVECTOR3				m_StartPos;
	D3DXVECTOR3				m_ControlPos;
	D3DXVECTOR3				m_EndPos;
	MouseDevice::MOUSESTATE m_MouseState;

};


#endif
