/**
 * @file   RoadManager.h
 * @brief  RoadManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef ROADMANAGER_H
#define ROADMANAGER_H

/**
 * 道を管理するクラス
 */
class RoadManager
{
public:
	/**
	 * RoadManagerクラスのコンストラクタ
	 */
	RoadManager();

	/**
	 * RoadManagerクラスのデストラクタ
	 */
	~RoadManager();
	
	/**
	 * RoadManagerクラスの制御関数
	 */
	void Control();
	
	/**
	 * RoadManagerクラスの描画関数
	 */
	void Draw();

private:
	RoadManager(const RoadManager&);
	void operator=(const RoadManager&);

};


#endif
