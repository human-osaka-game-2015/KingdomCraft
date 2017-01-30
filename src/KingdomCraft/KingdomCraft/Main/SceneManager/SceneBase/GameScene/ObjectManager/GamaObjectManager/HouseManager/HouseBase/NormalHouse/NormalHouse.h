/**
 * @file   NormalHouse.h
 * @brief  NormalHouseクラスのヘッダファイル
 * @author morimoto
 */
#ifndef NORMALHOUSE_H
#define NORMALHOUSE_H
#include "..\HouseBase.h"

/**
 * 通常の建物クラス
 */
class NormalHouse : public HouseBase
{
public:
	/**
	 * NormalHouseクラスのコンストラクタ
	 * @param[in] _pHousePos 建物を描画する座標
	 * @param[in] _houseAngle 建物の角度
	 */
	NormalHouse(const D3DXVECTOR3* _pHousePos, float _houseAngle, int _modelIndex, int _vertexShaderIndex, int _pixelShaderIndex);

	/**
	 * NormalHouseクラスのデストラクタ
	 */
	virtual ~NormalHouse();

	/**
	 * NoramlHouseクラスの制御関数
	 */
	virtual void Control();

	/**
	 * NormalHouseクラスの描画関数
	 */
	virtual void Draw();

private:
	/**
	 * シェーダー用コンスタントバッファ
	 */
	struct MODEL_CONSTANT_BUFFER
	{
		D3DXMATRIX World;
	};

	NormalHouse(const NormalHouse&);
	void operator=(const NormalHouse&);


	/**
	 * 頂点レイアウトの初期化関数
	 */
	void InitVertexLayout();

	/**
	 * 深度ステンシルステートの初期化関数
	 */
	void InitDepthStencilState();

	/**
	 * コンスタントバッファの初期化関数
	 */
	void InitConstantBuffer();

	/**
	 * コンスタントバッファへの書き込み関数
	 */
	void WriteConstantBuffer();

	/**
	 * 頂点レイアウトの開放関数
	 */
	void ReleaseVertexLayout();

	/**
	 * 深度ステンシルステートの開放関数
	 */
	void ReleaseDepthStencilState();

	/**
	 * コンスタントバッファの開放関数
	 */
	void ReleaseConstantBuffer();

	int m_ModelIndex;
	int m_VertexShaderIndex;
	int m_PixelShaderIndex;

	ID3D11InputLayout*		 m_pVertexLayout;
	ID3D11DepthStencilState* m_pDepthStencilState;
	ID3D11Buffer*			 m_pConstantBuffer;

};


#endif
