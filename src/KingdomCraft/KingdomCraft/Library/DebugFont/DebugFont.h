/**
 * @file   DebugFont.h
 * @brief  DebugFontクラスのヘッダファイル
 * @author morimoto
 */
#ifndef DEBUGFONT_H
#define DEBUGFONT_H
#include <d3d11.h>
#include <d3dx10.h>

/**
 * デバッグ情報を表示するクラス
 */
class DebugFont
{
public:
	/**
	 * DebugFontクラスのコンストラクタ
	 * @param[in] _pDevice DirectX11のデバイス
	 * @param[in] _pDeviceContext DirectX11のデバイスコンテキスト
	 */
	DebugFont(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, HWND _hWnd);

	/**
	 * DebugFontクラスのデストラクタ
	 */
	~DebugFont();

	/**
	 * DebugFontクラスの初期化関数
	 * @param[in] _hWnd DebugFontクラスが対応するWindowのハンドル
	 * @return 初期化に成功したらtrueが返る
	 */
	bool Init();

	/**
	 * DebugFontクラスの解放関数
	 */
	void Release();

	/**
	 * フォントの初期化
	 * @param[in] _fontHeight フォントの高さ
	 * @param[in] _fontWidth フォントの幅
	 * @param[in] _fontColor フォントの色
	 * @return 初期化に成功したらtrueが返る
	 */
	bool InitFont(float _fontHeight, float _fontWidth, D3DXCOLOR _fontColor);

	/**
	 * フォント描画関数
	 * @param[in] _DrawPos フォントを表示する位置
	 * @param[in] _pStr 表示する文字列
	 */
	void DrawFont(const D3DXVECTOR2* _pDrawPos, LPCTSTR _pStr);

private:
	/**
	 * フォント表示のための頂点構造体
	 */
	struct FONT_VERTEX
	{
		D3DXVECTOR3 Pos;	//!< 頂点座標
		D3DXCOLOR	Color;	//!< 頂点カラー
		D3DXVECTOR2	Texel;	//!< テクスチャ座標
	};

	/**
	 * シェーダーに渡す定数バッファ構造体
	 */
	struct CONSTANT_BUFFER
	{
		D3DXMATRIX MatWVP;		//!< ワールド変換行列
		D3DXVECTOR4 TexelOffset;//!< テクスチャ座標のオフセット
		D3DXVECTOR4 PosOffset;	//!< 頂点座標のオフセット
	};

	/**
	 * リソースビューの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitResourceView();

	/**
	 * 定数バッファの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitConstantBuffer();

	/**
	 * シェーダーの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitShader();

	/**
	 * 頂点シェーダーの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitVertexShader();

	/**
	 * ピクセルシェーダーの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitPixelShader();

	/**
	 * サンプラステートの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitSamplerState();

	/**
	 * ブレンドステートの初期化関数
	 * @return 初期化に成功したらtrue
	 */
	bool InitBlendState();

	/**
	 * 深度ステンシルバッファの作成
	 * @return 初期化に成功したらtrue
	 */
	bool InitDepthStencilState();

	/**
	 * リソースビューの解放関数
	 */
	void ReleaseResourceView();

	/**
	 * 定数バッファの解放関数
	 */
	void ReleaseConstantBuffer();

	/**
	 * シェーダーの解放関数
	 */
	void ReleaseShader();

	/**
	 * 頂点シェーダーの解放関数
	 */
	void ReleaseVertexShader();

	/**
	 * ピクセルシェーダーの解放関数
	 */
	void ReleasePixelShader();

	/**
	 * サンプラステートの解放関数
	 */
	void ReleaseSamplerState();

	/**
	 * ブレンドステートの解放関数
	 */
	void ReleaseBlendState();

	/**
	 * 深度ステンシルバッファの解放関数
	 */
	void ReleaseDepthStencilState();


	static const float m_DebugFontTu;
	static const int m_SpaceAsciiCode;
	ID3D11Device* const			m_pDevice;
	ID3D11DeviceContext* const	m_pDeviceContext;
	ID3D11ShaderResourceView*	m_pResourceView;
	ID3D11Buffer*				m_pConstantBuffer;
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11VertexShader*			m_pVertexShader;
	ID3D11InputLayout*			m_pLayout;
	ID3D11PixelShader*			m_pPixelShader;
	ID3D11SamplerState*			m_pSamplerState;
	ID3D11BlendState*			m_pBlendState;
	ID3D11DepthStencilState*	m_pDepthStencilState;
	HWND const					m_hWnd;
	float						m_FontHeight;
	float						m_FontWidth;
	float						m_WindowWidth;
	float						m_WindowHeight;

};

#endif
