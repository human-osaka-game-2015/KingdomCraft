/**
 * @file   FbxModel.h
 * @brief  FbxModelクラスのヘッダファイル
 * @author morimoto
 */
#ifndef FBXMODEL_H
#define FBXMODEL_H
#include <D3DX11.h>
#include <D3DX10.h>
#include <vector>

/**
 * Fbxファイルのモデル情報を管理するクラス
 */
class FbxModel
{
public:
	/**
	 * Fbxの描画の際に利用する頂点構造体
	 */
	struct FBXMODEL_VERTEX
	{
		D3DXVECTOR3 Pos;	//!< 頂点座標 
		D3DXVECTOR3	Normal;	//!< 法線ベクトル
		D3DXVECTOR2 Texel;	//!< テクスチャ座標
	};

	/**
	 * Fbxファイルから取得する頂点情報構造体
	 */
	struct VERTEX_DATA
	{
		int				PolygonNum;			//!< ポリゴンの数
		int				PolygonVertexNum;	//!< Meshの総頂点数
		int*			pIndexAry;			//!< インデックスバッファ
		int				ControlPositionNum;	//!< インデックスバッファが指す頂点の数
		D3DXVECTOR3*	pVertex;			//!< インデックスが参照する頂点
	};

	/**
	 * Fbxファイルから取得する法線情報構造体
	 */
	struct NORMAL_DATA
	{
		D3DXVECTOR3* pNormalVec; //!< 法線ベクトルの配列
	};

	/**
	 * メッシュの描画に利用するマテリアル構造体
	 */
	struct MATERIAL
	{
		D3DXCOLOR	Diffuse;	//!< ディフューズ反射
		D3DXCOLOR	Ambient;	//!< アンビエント反射
		D3DXCOLOR	Specular;	//!< スペキュラ反射
		D3DXCOLOR	Emissive;	//!< エミッシブ
		float		Power;		//!< スペキュラ強度
	};

	struct TEXTURE_UV_DATA
	{
		LPCTSTR			pUVSetName;	//!< UVセットの名前(テクスチャ座標とテクスチャを紐づける)
		D3DXVECTOR2*	pTextureUV;	//!< テクスチャ座標
	};

	/**
	 * Fbxファイルから取得するテクスチャ構造体
	 */
	struct TEXTURE_DATA
	{
		TEXTURE_UV_DATA* pTextureUVData;
		int TextureUVCount;
	};

	/**
	 * Fbxから取得するマテリアル構造体
	 */
	struct MATERIAL_DATA
	{
		MATERIAL					pMaterial;			//!< メッシュのマテリアル
		int							TextureCount;		//!< マテリアルに紐づいているテクスチャの数
		LPCTSTR*					pTextureName;		//!< マテリアルに紐づいているテクスチャの名前が格納された配列
		LPCTSTR*					pTextureUVSetName;	//!< マテリアルに紐づいているテクスチャとUVを結びつける文字列が格納された配列
		ID3D11ShaderResourceView**	pTextureView;		//!< マテリアルに紐づいているテクスチャのビューが格納された配列
	};
	
	/**
	 * Fbxから取得するメッシュのデータ構造体
	 */
	struct MESH_DATA
	{
		VERTEX_DATA*	pVertexData;	//!< メッシュの頂点情報
		NORMAL_DATA*	pNormalData;	//!< メッシュの法線情報
		TEXTURE_DATA*	pTextureData;	//!< テクスチャの情報
		MATERIAL_DATA*	pMaterialData;	//!< マテリアルの情報
	};

	FbxModel(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext);
	~FbxModel();

	/**
	 * メッシュデータを追加する
	 * @param[in] _pMeshData 追加するメッシュデータ
	 */
	void AddMeshData(MESH_DATA* _pMeshData);

	/**
	 * 追加されたメッシュデータをもとに初期化を行う
	 * @return 初期化に成功したらtrue
	 */
	bool Init();

	/**
	 * モデルデータを解放する
	 */
	void Release();

	/**
	 * オブジェクト描画
	 * @param[in] _meshNum 描画するメッシュの番号
	 */
	void Draw(int _meshNum = 0);

	/**
	 * アニメーション描画
	 */
	void AnimationDraw();

	/**
	 * アニメーションフレームをセットする
	 * @param[in] _setFrame セットするフレーム
	 */
	void SetAnimationFrame(int _setFrame);

	/**
	 * アニメーションの最大フレームを取得する
	 * @return 最大フレーム
	 */
	int GetAnimationFrame();

	/**
	 * モデル内のメッシュ数を取得する
	 * @return モデル内のメッシュ数
	 */
	int GetMeshNum();

private:
	/**
	 * インデックスバッファを初期化する
	 * @return 初期化に成功したらtrue
	 */
	bool InitIndexBuffer();
	
	/**
	 * 頂点バッファを初期化する
	 * @return 初期化に成功したらtrue
	 */
	bool InitVertexBuffer();

	/**
	 * サンプラステートの初期化する
	 * @return 初期化に成功したらtrue
	 */
	bool InitSamplerState();

	/**
	 * インデックスバッファの解放
	 */
	void ReleaseIndexBuffer();

	/**
	 * 頂点バッファの解放
	 */
	void ReleaseVertexBuffer();

	/**
	 * サンプラステートの解放
	 */
	void ReleaseSamplerState();

	ID3D11Device* const			m_pDevice;
	ID3D11DeviceContext* const	m_pDeviceContext;
	std::vector<MESH_DATA>		m_MeshData;
	ID3D11Buffer**				m_ppIndexBuffer;
	ID3D11Buffer**				m_ppVertexBuffer;
	FBXMODEL_VERTEX**			m_ppVertexData;
	ID3D11SamplerState*			m_pSamplerState;

};


#endif
