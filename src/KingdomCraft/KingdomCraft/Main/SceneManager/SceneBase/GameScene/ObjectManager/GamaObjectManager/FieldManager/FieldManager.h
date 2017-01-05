/**
 * @file   FieldManager.h
 * @brief  FieldManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef FIELDMANAGER_H
#define FIELDMANAGER_H

class Ground;
class Sky;

/**
 * ゲームシーンの始まりのフィールドを管理するクラス
 */
class FieldManager
{
public:
	/**
	 * FieldManagerクラスのコンストラクタ
	 */
	FieldManager();

	/**
	 * FieldManagerクラスのデストラクタ
	 */
	~FieldManager();

	/**
	 * FieldManagerクラスの制御関数
	 */
	void Control();

	/**
	 * FieldManagerクラスの描画関数
	 */
	void Draw();

private:
	FieldManager(const FieldManager&);
	void operator=(const FieldManager&);

	Ground* m_pGround;
	Sky*	m_pSky;

};


#endif
