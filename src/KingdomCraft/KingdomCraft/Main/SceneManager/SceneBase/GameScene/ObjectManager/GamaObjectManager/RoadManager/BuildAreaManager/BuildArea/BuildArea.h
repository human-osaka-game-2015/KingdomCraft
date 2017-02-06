/**
 * @file   BuildArea.h
 * @brief  BuildAreaクラスのヘッダファイル
 * @author kotani
 */
#ifndef BUILDAREA_H
#define BUILDAREA_H

/**
 * 建物を建てることが出来るエリア
 */
class BuildArea
{
public:
	/**
	 * BuildAreaのコンストラクタ
	 */
	BuildArea();

	/**
	 * BuildAreaのデストラクタ
	 */
	~BuildArea();

	/**
	 * BuildAreaの制御関数
	 */
	void Control();

	/**
	 * BuildAreaの描画関数
	 */
	void Draw();

private:
	BuildArea(const BuildArea&);
	void operator=(const BuildArea&);

};


#endif
