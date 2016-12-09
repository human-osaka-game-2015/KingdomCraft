/**
 * @file   HouseManager.h
 * @brief  HouseManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H

/**
 * 建物を管理するクラス
 */
class HouseManager
{
public:
	/**
	 * HouseManagerクラスのコンストラクタ
	 */
	HouseManager();

	/**
	 * HouseManagerクラスのデストラクタ
	 */
	~HouseManager();
	
	/**
	 * HouseManagerクラスの制御関数
	 */
	void Control();
	
	/**
	 * HouseManagerクラスの描画関数
	 */
	void Draw();

private:
	HouseManager(const HouseManager&);
	void operator=(const HouseManager&);

};


#endif
