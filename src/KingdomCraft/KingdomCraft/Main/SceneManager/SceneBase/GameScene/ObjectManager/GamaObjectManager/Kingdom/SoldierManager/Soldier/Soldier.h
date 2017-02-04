/**
 * @file   Soldier.h
 * @brief  Soldierクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIER_H
#define SOLDIER_H

class Soldier
{
public:
	/**
	 * Soldierクラスのコンストラクタ
	 */
	Soldier();

	/**
	 * Soldierクラスのデストラクタ
	 */
	virtual ~Soldier();

	/**
	 * Soldierクラスの制御関数
	 */
	virtual void Control();

	/**
	 * Soldierクラスの描画関数
	 */
	virtual void Draw();

protected:
	int m_BasePointID;	//!< 兵士の所属地ID

};


#endif
