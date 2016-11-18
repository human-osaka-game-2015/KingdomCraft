/**
 * @file TitleButton.h
 * @brief TitleButtonクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLEBUTTON_H
#define TITLEBUTTON_H
#include "Vertex2D\Vertex2D.h"

/**
 * タイトルメニュー内のボタンクラス
 */
class TitleMenuButton
{
public:
	/**
	 * TitleMenuButtonのコンストラクタ
	 *
	 * @param[in] _pDrawPos ボタンの描画位置
	 * @param[in] _pDrawSize ボタンのサイズ
	 * @param[in] _textureName 描画するボタンの画像
	 */
	TitleMenuButton(const D3DXVECTOR2* const _pDrawPos, const D3DXVECTOR2* const _pDrawSize, LPCTSTR const _pTextureName);

	/**
	 * TitleMenuButtonのデストラクタ
	 */
	~TitleMenuButton();

	/**
	 * TitleMenuButtonの制御関数
	 *
	 * ボタンが押されたかのチェックだけしている\n
	 * SetVisibleでfalseを指定したらチェックせずfalseを返す
	 * @return ボタンが押されたらtrue
	 */
	bool Control();

	/**
	 * ボタンクラスの描画関数
	 *
	 * マウスの座標を見てボタンを拡縮してそれっぽく描画する\n
	 * SetVisibleでfalseを指定したら描画しない
	 */
	void Draw();

	/**
	 * ボタンの可視設定を行う関数
	 *
	 * falseを指定したらControlとDrawは動作しなくなる
	 * trueを指定したらそのまま動作
	 * @param[in] _isVisible 可視設定するかのフラグ
	 */
	inline void SetVisible(bool _isVisible)
	{
		m_IsVisible = _isVisible;
	}

protected:
	TitleMenuButton(const TitleMenuButton&);
	void operator=(const TitleMenuButton&);

	bool OnClick();

	D3DXVECTOR2 m_DrawPos;
	D3DXVECTOR2 m_DrawSize;
	Vertex2D*	m_pVertex;
	bool		m_IsMouseOver;
	bool		m_IsVisible;
	int			m_TextureIndex;

};

#endif
