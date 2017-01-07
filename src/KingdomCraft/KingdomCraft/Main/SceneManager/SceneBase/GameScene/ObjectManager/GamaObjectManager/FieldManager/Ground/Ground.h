/**
 * @file   Ground.h
 * @brief  Groundクラスのヘッダファイル
 * @author kotani
 */
#ifndef GROUND_H
#define GROUND_H
#include <D3DX11.h>
#include <D3DX10.h>

/**
 * 地面の管理をするクラス
 */
class Ground
{
public:
	/**
	 * Groundクラスのコンストラクタ
	 */
	Ground();

	/**
 	 * Groundクラスのデストラクタ
 	 */
	~Ground();

	/**
	 * Groundクラスの制御関数
	 */
	void Control();

	/**
	 * Groundクラスの描画関数
	 */
	void Draw();

private:
	Ground(const Ground&);
	void operator=(const Ground&);

	/**
	 * モデル用コンスタントバッファ
	 */
	struct MODEL_CONSTANT_BUFFER
	{
		D3DXMATRIX World;
	};

	/**
	 * 頂点入力レイアウトの初期化関数
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
	 * 頂点入力レイアウトの開放関数
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
	int m_TextureIndex;

	ID3D11InputLayout*		 m_pVertexLayout;
	ID3D11DepthStencilState* m_pDepthStencilState;
	ID3D11Buffer*			 m_pConstantBuffer;

};


#endif
