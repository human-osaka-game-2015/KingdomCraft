/**
 * @file   Ground.h
 * @brief  Groundクラスのヘッダファイル
 * @author kotani
 */
#ifndef GROUND_H
#define GROUND_H
#include <D3DX11.h>
#include <D3DX10.h>
#include "..\..\GameObjectBase\GameObjectBase.h"

/**
 * 地面の管理をするクラス
 */
class Ground : public GameObjectBase
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
	virtual void Control();

	/**
	 * Groundクラスの描画関数
	 */
	virtual void Draw();

private:
	Ground(const Ground&);
	void operator=(const Ground&);

	/**
	 * モデルのコンスタントバッファ
	 */
	struct MODEL_CONSTANT_BUFFER
	{
		D3DXMATRIX World;
	};

	/**
	 * 頂点入力レイアウトの初期化関数
	 */
	virtual void InitVertexLayout();

	/**
	 * コンスタントバッファへの書き込み関数
	 */
	virtual void WriteConstantBuffer();

	/**
 	 * コンスタントバッファの開放関数
 	 */
	virtual void ReleaseConstantBuffer();

	int m_ModelIndex;
	int m_VertexShaderIndex;
	int m_PixelShaderIndex;
	int m_TextureIndex;

	ID3D11InputLayout* m_pVertexLayout;
	ID3D11Buffer*	   m_pConstantBuffer;

};


#endif
