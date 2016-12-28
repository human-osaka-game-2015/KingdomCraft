/**
 * @file TitleBackground.h
 * @brief TitleBackgroundクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLEBACKGROUND_H
#define TITLEBACKGROUND_H
#include <D3DX11.h>
#include <D3DX10.h>

class Vertex2D;

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

	static const D3DXVECTOR2	m_Pos;		//!< 背景の座標
	static const D3DXVECTOR2	m_Size;		//!< 背景の矩形サイズ
	static const D3DXVECTOR2	m_Texel[4];	//!< 背景のテクスチャ座標
	Vertex2D*					m_pVertex2D;
	int							m_TextureIndex;

};


#endif
