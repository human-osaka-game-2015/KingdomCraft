/**
 * @file   Road.h
 * @brief  Roadクラスのヘッダファイル
 * @author kotani
 */
#ifndef ROAD_H
#define ROAD_H
#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>

/**
 * 道のクラス
 */
class Road
{
public:
	/**
	 * Roadクラスのコンストラクタ
	 * @param[in] _vertexShaderIndex バーテックスシェーダーのインデックス
	 * @param[in] _pixelShaderIndex ピクセルシェーダーのインデックス
	 * @param[in] _pStartPos 道の始点
	 * @param[in] _pEndPos 道の終点
	 */
	Road(int _vertexShaderIndex, int _pixelShaderIndex, D3DXVECTOR3* _pStartPos, D3DXVECTOR3* _pEndPos);

	/**
	 * Roadクラスのデトラクタ
	 */
	~Road();

	/**
	 * Roadクラスの制御関数
	 */
	void Control();

	/**
	 * Roadクラスの描画関数
	 */
	void Draw();

	/**
	 * 道の始点を取得する関数
	 * @return 道の始点
	 */
	inline D3DXVECTOR3 GetStartPos()
	{
		return m_StartPos;
	}

	/**
	 * 道の終点を取得する関数
	 * @return EndPosではないのは道を引く際の長さで決まるから
	 */
	inline D3DXVECTOR3 GetEndPos()
	{
		return m_CenterLinePos[m_CenterLinePos.size() - 1];
	}

	/**
	 * 道の中線を取得する関数
	 * @return 道の中線
	 */
	inline std::vector<D3DXVECTOR3> GetCenterLine()
	{
		return m_CenterLinePos;
	}

private:
	Road(const Road&);
	void operator=(const Road&);

	/**
	 * 頂点構造体
	 */
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//!< 頂点座標
	};
	
	/**
	 * モデル用コンスタントバッファー
	 */
	struct MODEL_CONSTANT_BUFFER
	{
		D3DXMATRIX World;
	};

	/**
	 * 設定した中心点を元に頂点を作る
	 * @param[in] _dividNum 道の分割数
	 */
	void CreateVertex(int _dividNum);

	/**
	 * 道の分割する際の各始点と終点の中心点を作る
	 * @param[in] _dividNum 道の分割数
	 */
	void CreateCenterPos(int _dividNum);

	/**
	 * CenterPosからの各点から点の角度を作る
	 * @param[in] _dividNum 道の分割数
	 */
	void CreateAngle(int _dividNum);

	/**
	 * 頂点入力レイアウトの初期化関数
	 */
	void InitVertexLayout();
	
	/**
	 * 頂点バッファの初期化関数
	 */
	void InitVertexBuffer();

	/**
	 * 深度ステンシルステートの初期化関数
	 */
	void InitDepthStencilState();

	/**
	 * 定数バッファの初期化関数
	 */
	void InitConstantBuffer();

	/**
	 * 頂点入力レイアウトの開放関数
	 */
	void ReleaseVertexLayout();

	/**
	 * 頂点バッファの開放関数
	 */
	void ReleaseVertexBuffer();

	/**
	 * 深度ステンシルステートの開放関数
	 */
	void ReleaseDepthStencilState();

	/**
	 * コンスタントバッファの開放関数
	 */
	void ReleaseConstantBuffer();
	
	/**
	 * コンスタントバッファへの書き込み関数
	 */
	void WriteConstantBuffer();

	static const float m_RoadWidth;
	static const float m_RoadHeight;

	ID3D11Buffer*			 m_pConstantBuffer;
	ID3D11Buffer*			 m_pVertexBuffer;
	ID3D11InputLayout*		 m_pVertexLayout;
	ID3D11DepthStencilState* m_pDepthStencilState;
	int						 m_VertexShaderIndex;
	int						 m_PixelShaderIndex;
	
	std::vector<D3DXVECTOR3> m_CenterLinePos;
	VERTEX*					 m_pVertex;
	D3DXVECTOR3				 m_StartPos;
	D3DXVECTOR3				 m_ControlPos;
	D3DXVECTOR3				 m_EndPos;
	D3DXVECTOR3*			 m_pLeftLinePos;
	D3DXVECTOR3*			 m_pRightLinePos;
	float*					 m_pAngle;
	int						 m_VertexNum;

};


#endif
