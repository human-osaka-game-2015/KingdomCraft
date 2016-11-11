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
 * @brief テクスチャを貼って矩形を描画するクラス
 */
class Vertex2D
{
public:
	Vertex2D(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext, HWND _hwnd);
	~Vertex2D();
	
	/**
	 * 初期化
	 * @param[in] _pRectSize 矩形のサイズ 
	 * @param[in] _pUV テクスチャの4頂点分のUV値
	 * @return 成功したらtrue
	 */
	bool Init(RECT* _pRectSize, D3DXVECTOR2* _pUV);

	/**
	 * 描画処理
	 * @param[in] _pDrawPos 描画するスクリーン座標位置
	 * @param[in] _alpha アルファ値
	 * @param[in] _scale スケール
	 * @param[in] _angle 角度
	 */
	void Draw(D3DXVECTOR2* _pDrawPos,float _alpha = 1.f,D3DXVECTOR3* _pScale = &D3DXVECTOR3(1.f, 1.f, 1.f), float _angle = 0.f);

	/**
	* テクスチャをセットする
	* @param[in] _pTextureResourceView セットするテクスチャ
	*/
	void SetTexture(ID3D11ShaderResourceView* _pTextureResourceView){ m_pTextureResourceView = _pTextureResourceView; }

	/**
	 * 開放処理
	 */
	void Release();
private:
	struct Vertex
	{
		D3DXVECTOR3 pos;
		D3DXVECTOR2 UV;
	};

	//コンスタントバッファは16バイト区切りじゃないとCreateBufferに失敗する
	struct SHADER_CONSTANT_BUFFER
	{
		D3DXMATRIX  matWorld;
		D3DXCOLOR   alpha; //アルファ値しか使わない
		D3DXVECTOR4 viewPort;
	};

	bool InitVertexShader();
	void ReleaseVertexShader();

	bool InitPixelShader();
	void ReleasePixelShader();

	bool InitVertexBuffer(RECT* _pRectSize, D3DXVECTOR2* _pUV);
	void ReleaseVertexBuffer();

	bool InitConstantBuffer();
	void ReleaseConstantBuffer();

	bool InitBlendState();
	void ReleaseBlendState();

	bool InitSamplerState();
	void ReleaseSamplerState();

	bool CreateVertexLayout();
	void ReleaseVertexLayout();

	ID3D11Device*			  m_pDevice;
	ID3D11DeviceContext*	  m_pDeviceContext;
	ID3D11PixelShader*		  m_pPixelShader;
	ID3D11VertexShader*		  m_pVertexShader;
	ID3D11Buffer*			  m_pConstantBuffer;
	ID3D11Buffer*			  m_pVertexBuffer;
	ID3D11BlendState*		  m_pBlendState;
	ID3D11SamplerState*		  m_pSampler;
	ID3D11ShaderResourceView* m_pTextureResourceView;
	HWND					  m_hWnd;

	float					  m_WindowWidth;
	float					  m_WindowHeight;

	//頂点レイアウトの設定に使う
	ID3DBlob*		   m_pVertexCompiledShader;
	ID3D11InputLayout* m_pVertexLayout;
};
#endif