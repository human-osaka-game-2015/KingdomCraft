/**
 * @file   EnemyManager.h
 * @brief  EnemyManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

/**
 * 敵の管理をするクラス
 */
class EnemyManager
{
public:
	/**
	 * EnemyManagerクラスのコンストラクタ
	 */
	EnemyManager();

	/**
	 * EnemyManagerクラスのデストラクタ
	 */
	~EnemyManager();

	/**
	 * EnemyManagerクラスの制御関数
	 */
	void Control();

	/**
	 * EnemyManagerクラスの描画関数
	 */
	void Draw();

private:
	EnemyManager(const EnemyManager&);
	void operator=(const EnemyManager&);

};


#endif
