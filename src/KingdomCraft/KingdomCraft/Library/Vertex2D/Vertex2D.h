/**
 * @file   Vertex2D.h
 * @brief  Vertex2Dクラスのヘッダファイル
 * @author kotani
 */
#ifndef VERTEX2D_H
#define VERTEX2D_H
#include <D3DX11.h>
#include <d3dx10.h>

/**
 * 2Dの矩形を描画するクラス
 */
class Vertex2D
{
public:
	/**
	 * Vertex2Dクラスのコンストラクタ
	 * @param[in] _pDevice バッファ作成などのために利用するDirectX11のデバイス
	 * @param[in] _pDeviceContext 描画などに利用するDirectX11のデバイスコンテキスト
	 * @param[in] _hWnd 2dの矩形を描画するウィンドウのハンドル
	 */
	Vertex2D(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, HWND _hWnd);

	/**
	 * Vertex2Dクラスのデストラクタ
	 */
	~Vertex2D();
	
	/**
	 * Vertex2Dクラスの初期化関数
	 * @param[in] _pRectSize 矩形のサイズ 
	 * @param[in] _pUV テクスチャの4頂点分のUV値 テクスチャ座標の指定順番(左上->右上->左下->右下)
	 * @return 初期化に成功したらtrue
	 */
	bool Init(const D3DXVECTOR2* _pRectSize, const D3DXVECTOR2* _pUV);

	/**
	 * Vertex2Dクラスの解放関数
	 */
	void Release();

	/**
	 * 2Dの矩形を描画する関数
	 * @param[in] _pDrawPos 矩形を描画するスクリーン座標位置
	 * @param[in] _alpha 描画する矩形のアルファ値
	 * @param[in] _pScale 描画する矩形の拡縮率
	 * @param[in] _angle 描画する矩形の傾き
	 */
	void Draw(
		const D3DXVECTOR2* _pDrawPos, 
		float _alpha = 1.f, 
		const D3DXVECTOR3* _pScale = &D3DXVECTOR3(1.f, 1.f, 1.f), 
		float _angle = 0.f);

	/**
	 * 描画するテクスチャをセットする関数
	 * @param[in] _pTextureResourceView セットするテクスチャ
	 */
	void SetTexture(ID3D11ShaderResourceView* _pTextureResourceView)
	{ 
		m_pTextureResourceView = _pTextureResourceView; 
	}

private:
	/**
	 * 2D矩形の描画に利用する頂点構造体
	 */
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//!< 頂点座標
		D3DXVECTOR2 UV;		//!< テクスチャ座標
	};

	/**
	 * シェーダーに渡す定数バッファ
	 *
	 * 定数バッファは16バイト区切りじゃないとバッファ作成に失敗する
	 */
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX  MatWorld;	//!< ワールド変換行列
		D3DXCOLOR   Color;		//!< 頂点カラー値
		D3DXVECTOR4 WindowSize;	//!< ウィンドウの縦横サイズ
	};

	/**
	 * 頂点シェーダーの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitVertexShader();

	/**
	 * 頂点入力レイアウトの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitVertexLayout();

	/**
	 * ピクセルシェーダーの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitPixelShader();

	/**
	 * ブレンドステートの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitBlendState();

	/**
	 * サンプラステートの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitSamplerState();

	/**
	 * 頂点バッファの初期化関数
	 * @param[in] _pRectSize 矩形の大きさ
	 * @param[in] _pUV テクスチャ座標
	 * @return 初期化に成功したらtrue
	 */
	bool InitVertexBuffer(const D3DXVECTOR2* _pRectSize, const D3DXVECTOR2* _pUV);

	/**
	 * 定数バッファの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitConstantBuffer();

	/**
	 * 頂点シェーダーの解放関数
	 */
	void ReleaseVertexShader();

	/**
	 * 頂点インプットレイアウトの解放関数
	 */
	void ReleaseVertexLayout();

	/**
	 * ピクセルシェーダーの解放関数
	 */
	void ReleasePixelShader();

	/**
	 * ブレンドステートの解放関数
	 */
	void ReleaseBlendState();

	/**
	 * サンプラの解放関数
	 */
	void ReleaseSamplerState();

	/**
	 * 頂点バッファの解放関数
	 */
	void ReleaseVertexBuffer();

	/**
	 * 定数バッファの解放関数
	 */
	void ReleaseConstantBuffer();


	static const int			m_VertexNum;
	static const UINT			m_ColorMask;

	ID3D11Device* const			m_pDevice;
	ID3D11DeviceContext* const	m_pDeviceContext;
	ID3D11PixelShader*			m_pPixelShader;
	ID3D11VertexShader*			m_pVertexShader;
	ID3DBlob*					m_pVertexCompiledShader;
	ID3D11InputLayout*			m_pVertexLayout;
	ID3D11Buffer*				m_pConstantBuffer;
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11BlendState*			m_pBlendState;
	ID3D11SamplerState*			m_pSampler;
	ID3D11ShaderResourceView*	m_pTextureResourceView;
	HWND						m_hWnd;
	float						m_ClientWidth;
	float						m_ClientHeight;

};


#endif
