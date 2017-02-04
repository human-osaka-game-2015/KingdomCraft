/**
 * @file   SoldierCreater.h
 * @brief  SoldierCreaterクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERCREATER_H
#define SOLDIERCREATER_H
#include "..\SoldierManager.h"

class Soldier;

class SoldierCreater
{
public:
	/**
	 * SoldierCreaterクラスのコンストラクタ
	 */
	SoldierCreater();

	/**
	 * SoldierCreaterクラスのデストラクタ
	 */
	~SoldierCreater();

	/**
	 * 生成する兵士の種類を指定する関数
	 * @param[in] _type 生成する兵士の種類
	 */
	void SetSoldierType(SoldierManager::SOLDIER_TYPE _type);

	/**
	 * 兵士を生成する関数
	 * @return 生成したSoldierインスタンス
	 */
	Soldier* SoldierCreate();

private:
	SoldierManager::SOLDIER_TYPE m_SoldierType;

};


#endif
