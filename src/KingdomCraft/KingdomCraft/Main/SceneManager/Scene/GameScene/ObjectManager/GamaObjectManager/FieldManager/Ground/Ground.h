/**
 * @file   Ground.h
 * @brief  Groundクラスのヘッダファイル
 * @author kotani
 */
#ifndef GROUND_H
#define GROUND_H

/**
 * 地面の管理クラス
 */
class Ground
{
public:
	/**
	 * Groundクラスのコンストラクタ
	 */
	Ground();

	/**
 	 * Groundクラスのデストラクタ
 	 */
	~Ground();

	/**
	 * Groundクラスの制御関数
	 */
	void Control();

	/**
	 * Groundクラスの描画関数
	 */
	void Draw();

private:
	Ground(const Ground&);
	void operator=(const Ground&);

	int m_ModelIndex;
	int m_TextureIndex;

};


#endif
