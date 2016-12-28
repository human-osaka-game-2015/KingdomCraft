/**
 * @file TitleLogo.h
 * @brief TitleLogoクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLELOGO_H
#define TITLELOGO_H
#include <D3DX11.h>
#include <D3DX10.h>

class Vertex2D;

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

	static const D3DXVECTOR2	m_Pos;			//!< タイトルロゴの矩形サイズ
	static const D3DXVECTOR2	m_Size;			//!< タイトルロゴの座標
	static const D3DXVECTOR2	m_Texel[4];		//!< タイトルロゴのテクスチャ座標
	Vertex2D*					m_pVertex2D;
	int							m_TextureIndex;

};


#endif
