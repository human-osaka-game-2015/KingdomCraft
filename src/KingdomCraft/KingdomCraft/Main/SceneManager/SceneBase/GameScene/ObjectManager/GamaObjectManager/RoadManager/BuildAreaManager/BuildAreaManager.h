/**
 * @file   BuildAreaManager.h
 * @brief  BuildAreaManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef BUILDAREAMANAGER_H
#define BUILDAREAMANAGER_H
#include <vector>

class BuildArea;

/**
 * 建物等を建てる事が出来るエリアを管理するクラス
 */
class BuildAreaManager
{
public:
	/**
	 * BuildAreaManagerのコンストラクタ
	 */
	BuildAreaManager();

	/**
	 * BuildAreaManagerのデストラクタ
	 */
	~BuildAreaManager();
	
	/**
	 * BuildAreaManagerクラスの制御関数
	 */
	void Control();

	/**
	 * BuildAreaManagerクラスの描画関数
	 */
	void Draw();

private:
	BuildAreaManager(const BuildAreaManager&);
	void operator=(const BuildAreaManager&);
	std::vector<BuildArea*> m_pBuildArea;

};


#endif
