/**
 * @file   Sky.h
 * @brief  Skyクラスのヘッダファイル
 * @author kotani
 */
#ifndef SKY_H
#define SKY_H
#include <D3DX11.h>
#include <D3DX10.h>
#include "..\..\GameObjectBase\GameObjectBase.h"

/**
 * 空の管理クラス
 */
class Sky : public GameObjectBase
{
public:
	/**
	 * Skyクラスのコンストラクタ
	 */
	Sky();

	/**
	 * Skyクラスのデストラクタ
	 */
	~Sky();

	/**
	 * Skyクラスの制御関数
	 */
	virtual void Control();

	/**
	 * Skyクラスの描画関数
	 */
	virtual void Draw();

private:
	Sky(const Sky&);
	void operator=(const Sky&);

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

	MODEL_CONSTANT_BUFFER m_ModelConstantBuffer;
	ID3D11Buffer*	   m_pConstantBuffer;

};


#endif
