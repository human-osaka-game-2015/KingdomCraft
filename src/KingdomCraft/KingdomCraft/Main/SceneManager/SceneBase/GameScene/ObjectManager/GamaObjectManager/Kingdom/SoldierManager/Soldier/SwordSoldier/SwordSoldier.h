/**
 * @file   SwordSoldier.h
 * @brief  SwordSoldierクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SWORDSOLDIER_H
#define SWORDSOLDIER_H
#include "..\Soldier.h"

class SwordSoldier : public Soldier
{
public:
	/**
	 * SwordSoldierクラスのコンストラクタ
	 */
	SwordSoldier();

	/**
	 * SwordSoldierクラスのデストラクタ
	 */
	virtual ~SwordSoldier();

	/**
	 * SwordSoldierクラスの制御関数
	 */
	virtual void Control();

	/**
	 * SwordSoldierクラスの描画関数
	 */
	virtual void Draw();

};


#endif
