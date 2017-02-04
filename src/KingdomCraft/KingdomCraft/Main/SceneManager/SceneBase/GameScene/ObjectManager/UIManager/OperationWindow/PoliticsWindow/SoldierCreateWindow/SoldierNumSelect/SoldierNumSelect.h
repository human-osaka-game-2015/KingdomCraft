#ifndef SOLDIERNUMSELECT_H
#define SOLDIERNUMSELECT_H

class SoldierNumSelect
{
public:
	SoldierNumSelect();
	~SoldierNumSelect();

	/**
	 * SoldierNumSelectクラスの制御関数
	 */
	void Control();

	/**
	 * SoldierNumSelectクラス描画関数
	 */
	void Draw();

private:
	static const int m_SoldierMax;		//!< 一つの部隊の最大人数
	static const int m_SoldierOffset;	//!< 部隊の人数増減の基準値


};


#endif
