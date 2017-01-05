/**
 * @file   Sky.h
 * @brief  Skyクラスのヘッダファイル
 * @author kotani
 */
#ifndef SKY_H
#define SKY_H
#include <D3DX11.h>
#include <D3DX10.h>

/**
 * 空の管理クラス
 */
class Sky
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
	void Control();

	/**
	 * Skyクラスの描画関数
	 */
	void Draw();

private:
	Sky(const Sky&);
	void operator=(const Sky&);

	/**
	 * シェーダー用コンスタントバッファ
	 */
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX World;
	};

	/**
	 * 頂点入力レイアウトの初期化関数
	 */
	void InitVertexLayout();

	/**
	 * コンスタントバッファの初期化関数
	 */
	void InitConstantBuffer();

	/**
	 * コンスタントバッファへの書き込み関数
	 */
	void WriteConstantBuffer();

	/**
	 * バーテックスレイアウトの開放関数
	 */
	void ReleaseVertexLayout();

	/**
	 * コンスタントバッファの開放関数
	 */
	void ReleaseConstantBuffer();

	int m_ModelIndex;
	int m_VertexShaderIndex;
	int m_PixelShaderIndex;

	ID3D11InputLayout* m_pVertexLayout;
	ID3D11Buffer*	   m_pConstantBuffer;

};


#endif
