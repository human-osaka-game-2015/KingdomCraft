/**
 * @file TitleLogo.h
 * @brief TitleLogoクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLELOGO_H
#define TITLELOGO_H
#include "Vertex2D\Vertex2D.h"

/**
 * タイトルシーンのタイトルロゴを管理するクラス
 */
class TitleLogo
{
public:
	/**
	 * TitleLogoのコンストラクタ
	 */
	TitleLogo();

	/**
	 * TitleLogoのデストラクタ
	 */
	~TitleLogo();

	/**
	 * TitleLogoクラスの制御関数
	 */
	void Control();

	/**
	 * TitleLogoクラスの描画関数
	 */
	void Draw();

private:
	TitleLogo(const TitleLogo&);
	void operator=(const TitleLogo&);

	static const D3DXVECTOR2	m_TitleLogoPos;			//!< タイトルロゴの矩形サイズ
	static const D3DXVECTOR2	m_TitleLogoSize;		//!< タイトルロゴの座標
	static const D3DXVECTOR2	m_TitleLogoTexel[4];	//!< タイトルロゴのテクスチャ座標
	Vertex2D*					m_pVertex;
	int							m_TextureIndex;

};


#endif
