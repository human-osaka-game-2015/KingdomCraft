/**
 * @file   BuildArea.h
 * @brief  BuildAreaクラスのヘッダファイル
 * @author kotani
 */
#ifndef BUILDAREA_H
#define BUILDAREA_H
#include <vector>
#include <D3DX11.h>
#include <D3DX10.h>

/**
 * 建物を建てることが出来るエリア
 */
class BuildArea
{
public:
	/**
	 * BuildAreaのコンストラクタ
	 */
	BuildArea(bool _isLeft, std::vector<D3DXVECTOR3>* _pRoadCenterLine);

	/**
	 * BuildAreaのデストラクタ
	 */
	~BuildArea();

	/**
	 * BuildAreaの制御関数
	 */
	void Control();

	/**
	 * BuildAreaの描画関数
	 */
	void Draw();

private:
	BuildArea(const BuildArea&);
	void operator=(const BuildArea&);

	/**
	 * 頂点構造体
	 */
	struct VERTEX
	{
		D3DXVECTOR3 Pos;	//!< 頂点座標
	};

	/**
	 * モデル用コンスタントバッファー
	 */
	struct MODEL_CONSTANT_BUFFER
	{
		D3DXMATRIX World;
	};

	/**
	 * 左のビルドエリアを作る
	 */
	void LeftCreate();

	/**
	 * 右のビルドエリアを作る
	 */
	void RightCreate();

	ID3D11Buffer*			 m_pConstantBuffer;
	ID3D11Buffer*			 m_pVertexBuffer;
	ID3D11InputLayout*		 m_pVertexLayout;
	ID3D11DepthStencilState* m_pDepthStencilState;
	int						 m_VertexShaderIndex;
	int						 m_PixelShaderIndex;

	std::vector<D3DXVECTOR3> m_CenterLinePos;
	float*					 m_pAngle;
	VERTEX**				 m_ppVertex;

	D3DXVECTOR3				 m_StartPos;
	D3DXVECTOR3				 m_ControlPos;
	D3DXVECTOR3				 m_EndPos;
	int						 m_BuildAreaNum;
	bool					 m_isLeft;
};


#endif
