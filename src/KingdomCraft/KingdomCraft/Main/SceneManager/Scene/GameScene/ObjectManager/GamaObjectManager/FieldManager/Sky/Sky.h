/**
 * @file   Sky.h
 * @brief  Skyクラスのヘッダファイル
 * @author kotani
 */
#ifndef SKY_H
#define SKY_H

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

	int m_ModelIndex;
	int m_TextureIndex;

};


#endif
