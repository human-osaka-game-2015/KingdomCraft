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
 * @brief  Fbxファイルのモデル情報を管理するクラス
 */
class FbxModel
{
public:
	struct FBXMODEL_VERTEX
	{
		D3DXVECTOR3 Pos;
		D3DXVECTOR3	Normal;
		float		tu;
		float		tv;
	};

	struct VertexData
	{
		int				PolygonNum;			// ポリゴンの数
		int				PolygonVertexNum;	// Meshの総頂点数
		int*			pIndexAry;			// Indexデータ
		int				ControlPositionNum;	// インデックスバッファが指す頂点の数
		D3DXVECTOR3*	pVertex;			// インデックスが参照する頂点
	};

	struct NormalData
	{
		D3DXVECTOR3* pNormalVec;	// 法線ベクトル
	};

	struct Material
	{
		D3DXCOLOR	Diffuse;
		D3DXCOLOR	Ambient;
		D3DXCOLOR	Specular;
		D3DXCOLOR	Emissive;
		float		Power;
	};

	struct TextureData
	{
		LPCTSTR			pUVSetName;		// テクスチャとテクスチャ座標を結びつける文字列が格納されている
		D3DXVECTOR2*	pTextureUV;		// テクスチャ座標
	};

	struct MaterialData
	{
		Material*					Mat;				// メッシュのマテリアル
		int							TextureCount;		// マテリアルに紐づいているテクスチャの数
		LPCTSTR*					TextureName;		// マテリアルに紐づいているテクスチャの名前が格納された配列
		LPCTSTR*					TextureUVSetName;	// マテリアルに紐づいているテクスチャとUVを結びつける文字列が格納された配列
		ID3D11ShaderResourceView**	pTextureView;		// マテリアルに紐づいているテクスチャのビューが格納された配列
	};
	
	struct MeshData
	{
		VertexData*		pVertex;	// メッシュの頂点情報
		NormalData*		pNormal;	// メッシュの法線情報
	};

	FbxModel(ID3D11Device* _pDevice, ID3D11DeviceContext* _pDeviceContext);
	~FbxModel();

	/**
	 * メッシュデータを追加する
	 * @param[in] _pMeshData 追加するメッシュデータ
	 */
	void AddMeshData(MeshData* _pMeshData);

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
	 * インデックスバッファの解放
	 */
	void ReleaseIndexBuffer();

	/**
	 * 頂点バッファの解放
	 */
	void ReleaseVertexBuffer();

	ID3D11Device*			m_pDevice;
	ID3D11DeviceContext*	m_pDeviceContext;
	std::vector<MeshData>	m_MeshData;
	ID3D11Buffer**			m_ppIndexBuffer;
	ID3D11Buffer**			m_ppVertexBuffer;
	FBXMODEL_VERTEX**		m_ppVertexData;
};


#endif