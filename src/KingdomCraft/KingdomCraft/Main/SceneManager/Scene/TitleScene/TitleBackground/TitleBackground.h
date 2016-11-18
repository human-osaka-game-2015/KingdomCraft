/**
 * @file TitleBackground.h
 * @brief TitleBackgroundクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLEBACKGROUND_H
#define TITLEBACKGROUND_H
#include "Vertex2D\Vertex2D.h"

/**
 * タイトルシーン内の背景を管理するクラス
 */
class TitleBackground
{
public:
	/**
	 * TitleBackgroundのコンストラクタ
	 */
	TitleBackground();

	/**
	 * TitleBackgroundのデストラクタ
	 */
	~TitleBackground();

	/**
	 * TitleBackgroundの制御関数
	 */
	void Control();

	/**
	 * TitleBackgroundの描画関数
	 */
	void Draw();

private:
	TitleBackground(const TitleBackground&);
	void operator=(const TitleBackground&);

	static const D3DXVECTOR2	m_TitleBackgroundPos;
	static const D3DXVECTOR2	m_TitleBackgroundSize;
	Vertex2D*					m_pVertex;
	int							m_TextureIndex;

};

#endif
