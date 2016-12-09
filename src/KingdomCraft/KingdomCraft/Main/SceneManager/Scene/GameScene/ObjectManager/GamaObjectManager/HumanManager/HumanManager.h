/**
 * @file   HumanManager.h
 * @brief  HumanManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef HUMANMANAGER_H
#define HUMANMANAGER_H

/**
 * 人を管理するクラス
 */
class HumanManager
{
public:
	/**
	 * HumanManagerクラスのコンストラクタ
	 */
	HumanManager();

	/**
	 * HumanManagerクラスのデストラクタ
	 */
	~HumanManager();
	
	/**
	 * HumanManagerクラスの制御関数
	 */
	void Control();
	
	/**
	 * HumanManagerクラスの描画関数
	 */
	void Draw();

private:
	HumanManager(const HumanManager&);
	void operator=(const HumanManager&);

};


#endif
