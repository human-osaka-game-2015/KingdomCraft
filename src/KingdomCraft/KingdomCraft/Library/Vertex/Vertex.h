/**
 * @file   Vertex.h
 * @brief  Vertexクラスのヘッダファイル
 * @author morimoto
 */
#ifndef VERTEX_H
#define VERTEX_H
#include <D3DX11.h>
#include <D3DX10.H>

class Vertex
{
public:
	/**
	 * 2Dポリゴンの描画に利用する頂点構造体
	 */
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//!< 頂点座標
		D3DXVECTOR2 UV;		//!< テクスチャ座標
		D3DXCOLOR Color;	//!< 頂点カラー値
	};

	/**
	 * Vertexクラスのコンストラクタ
	 * @param[in] _pDevice バッファ作成時などに使用するDirectX11のデバイス
	 * @param[in] _pDeviceContext 描画などに利用するDirectX11のデバイスコンテキスト
	 * @param[in] _hWnd ポリゴンを描画するウィンドウのハンドル
	 */
	Vertex(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, HWND _hWnd);

	/**
	 * Vertexクラスのデストラクタ
	 */
	~Vertex();

	/**
	 * Vertexクラスの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool Init();

	/**
	 * Vertexクラスの解放関数
	 */
	void Release();

	/**
	 * 頂点バッファの生成関数
	 * @param[in] _pVertex 頂点バッファに格納する頂点情報
	 * @param[in] _vertexNum 作成するポリゴンの頂点数
	 * @return 初期化に成功したらtrue
	 */
	bool CreateVertexBuffer(const VERTEX* _pVertex, int _vertexNum);

	/**
	 * 頂点バッファの解放関数
	 */
	void ReleaseVertexBuffer();

	/**
	 * 頂点バッファにデータを書き込む関数
	 * @param[in] _pVertex バッファに書き込む頂点情報
	 * @return 書き込みに成功したらtrue
	 */
	bool WriteVertexBuffer(const VERTEX* _pVertex);

	/**
	 * 定数バッファにデータを書き込む関数
	 * @param[in] _pDrawPos 描画する2Dポリゴンの座標
	 * @param[in] _pScale 描画する2Dポリゴンの拡縮率
	 * @param[in] _angle 描画する2Dポリゴンの傾き
	 * @return 書き込みに成功したらtrue
	 */
	bool WriteConstantBuffer(
		const D3DXVECTOR2* _pDrawPos, 
		const D3DXVECTOR2* _pScale = &D3DXVECTOR2(1.f, 1.f), 
		float _angle = 0.f);

	/**
	 * Vertexクラスの描画関数
	 */
	void Draw();

	/**
	 * 描画するテクスチャをセットする関数
	 * @param[in] _pTextureResourceView テクスチャのリソースビュー
	 */
	inline void SetTexture(ID3D11ShaderResourceView* _pTextureResourceView)
	{
		m_pTextureResourceView = _pTextureResourceView;
	}

private:
	/**
	 * シェーダーに渡す定数バッファ
	 */
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX  MatWorld;	//!< ワールド変換行列
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
	 * 定数バッファの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitConstantBuffer();

	/**
	 * 頂点シェーダーの解放関数
	 */
	void ReleaseVertexShader();

	/**
	 * 頂点入力レイアウトの解放関数 
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
	 * サンプラステートの解放関数
	 */
	void ReleaseSamplerState();

	/**
	 * 定数バッファの解放関数
	 */
	void ReleaseConstantBuffer();


	ID3D11Device* const			m_pDevice;
	ID3D11DeviceContext* const	m_pDeviceContext;
	HWND						m_hWnd;
	ID3D11VertexShader*			m_pVertexShader;
	ID3DBlob*					m_pVertexCompiledShader;
	ID3D11InputLayout*			m_pVertexLayout;
	ID3D11PixelShader*			m_pPixelShader;
	ID3DBlob*					m_pPixelCompiledShader;
	ID3D11BlendState*			m_pBlendState;
	ID3D11SamplerState*			m_pSamplerState;
	ID3D11Buffer*				m_pConstantBuffer;
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11ShaderResourceView*	m_pTextureResourceView;
	VERTEX*						m_pVertex;
	int							m_VertexNum;
	float						m_ClientWidth;
	float						m_ClientHeight;

};


#endif
