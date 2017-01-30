/**
 * @file   BasePoint.h
 * @brief  BasePointクラスのヘッダファイル
 * @author kotani
 */
#ifndef BASEPOINT_H
#define BASEPOINT_H
#include <D3DX11.h>
#include <D3DX10.h>

class BasePoint
{
public:
	/**
	 * BasePointクラスのコンストラクタ
	 * @param[in] _pPos BasePointの座標
	 */
	BasePoint(const D3DXVECTOR3* _pPos);

	/**
	 * BasePointクラスのデストラクタ
	 */
	~BasePoint();

	/**
	 * BasePointクラスの制御関数
	 */
	void Control();

	/**
	 * BasePointクラスの描画関数
	 */
	void Draw();

private:
	BasePoint(const BasePoint&);
	void operator=(const BasePoint&);

	/**
	 * シェーダー用コンスタントバッファ
	 */
	struct MODEL_CONSTANT_BUFFER
	{
		D3DXMATRIX World;
	};

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

	/**
	 * モデルの描画関数
	 */
	void ModelDraw();


	int							m_ModelIndex;
	int							m_VertexShaderIndex;
	int							m_PixelShaderIndex;
	ID3D11InputLayout*			m_pVertexLayout;
	ID3D11DepthStencilState*	m_pDepthStencilState;
	ID3D11Buffer*				m_pConstantBuffer;
	D3DXVECTOR3					m_Pos;

};


#endif
