/**
 * @file   SoldierManager.h
 * @brief  SoldierManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERMANAGER_H
#define SOLDIERMANAGER_H
#include <vector>

class Soldier;

class SoldierManager
{
public:
	enum SOLDIER_TYPE
	{
		SWORDSOLDIER_TYPE,
		SOLDIER_TYPE_MAX
	};

	SoldierManager();
	~SoldierManager();
	void Control();
	void Draw();

private:
	std::vector<Soldier*> m_pSoldiers;

};


#endif
