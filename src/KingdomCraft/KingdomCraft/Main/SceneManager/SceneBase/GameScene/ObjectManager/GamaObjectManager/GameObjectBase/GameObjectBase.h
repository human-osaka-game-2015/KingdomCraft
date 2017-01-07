/**
 * @file   GameObjectBase.h
 * @brief  GameObjectBaseクラスのヘッダファイル
 * @author kotani
 */
#ifndef GAMEOBJECTBASE_H
#define GAMEOBJECTBASE_H
#include <D3DX11.h>
#include <D3DX10.h>

/**
 * GameObjectの基底クラス
 *
 * 主にGameObjectManagerの中の各Manager内の3Dモデルを持つクラスが継承している。
 */
class GameObjectBase
{
public:
	/**
	 * GameObjectBaseクラスのコンストラクタ
	 */
	GameObjectBase();

	/**
 	 * GameObjectBaseクラスのデストラクタ
 	 */
	virtual ~GameObjectBase();
	
	/**
	 * GameObjectBaseクラスの制御関数
	 */
	virtual void Control() = 0;

	/**
	 * GameObjectBaseクラスの描画関数
	 */
	virtual void Draw() = 0;

protected:
	/**
	 * コンスタントバッファの初期化関数
	 * @param[in] _constantBufferByteSize コンスタントバッファに書き込む構造体のバイトサイズ
	 * @param[out] _pConstantBuffer コンスタントバッファのポインタ
	 */
	void InitConstantBuffer(UINT _constantBufferByteSize, ID3D11Buffer** _ppConstantBuffer);

	/**
	 * 頂点入力レイアウトの初期化関数
	 */
	virtual void InitVertexLayout() = 0;

	/**
	 * コンスタントバッファへの書き込み関数
	 * @attention 構造体は16バイト区切りにしないとバッファ作成に失敗する。
				  行列を渡すときは転置行列を渡す。
	 */
	virtual void WriteConstantBuffer() = 0;
	
	/**
	 * 深度ステンシルステートの初期化関数
	 */
	void InitDepthStencilState();

	/**
	 * 深度ステンシルステートの開放関数
	 */
	void ReleaseDepthStencilState();

	/**
	 * バーテックスレイアウトの開放関数
	 */
	void ReleaseVertexLayout();

	/**
	 * コンスタントバッファの開放関数
	 */
	virtual void ReleaseConstantBuffer() = 0;

	ID3D11InputLayout*		 m_pVertexLayout;
	ID3D11DepthStencilState* m_pDepthStencilState;

};

#endif
