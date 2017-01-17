/**
 * @file TitleStartButton.h
 * @brief TitleStartButtonクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLESTARTBUTTON_H
#define TITLESTARTBUTTON_H
#include "Vertex2D\Vertex2D.h"

class TitleStartButton
{
public:
	/**
	 * TitleStartButtonのコンストラクタ
	 * @param[in] _pButtonPos ボタンの描画位置
	 * @param[in] _pButtonSize ボタンのサイズ
	 * @param[in] _textureIndex 描画するボタンの画像インデックス
	 */
	TitleStartButton(const D3DXVECTOR2* _pButtonPos, const D3DXVECTOR2* _pButtonSize, int _textureIndex);

	/**
	 * TitleStartButtonのデストラクタ
	 */
	~TitleStartButton();

	/**
	 * TitleStartButtonの制御関数
	 * @return ボタンが押されたらtrue
	 */
	bool Control();

	/**
	 * ボタンクラスの描画関数
	 */
	void Draw();

	/**
	 * ボタンの可視設定を行う関数
	 * @param[in] _isVisible 可視設定するかのフラグ
	 */
	inline void SetVisible(bool _isVisible)
	{
		m_IsVisible = _isVisible;
	}

private:
	TitleStartButton(const TitleStartButton&);
	void operator=(const TitleStartButton&);

	/**
	 * ボタンの描画関数
	 */
	void ButtonDraw();

	/**
	 * ボタンがクリックされたかをチェックする関数
	 * @return クリックされたらtrue
	 */
	bool IsClicked();

	static const D3DXVECTOR2	m_DefaultTexel[4];		//!< ボタンのテクスチャ座標
	const D3DXVECTOR2			m_Pos;
	const D3DXVECTOR2			m_Size;
	Vertex2D*					m_pVertex2D;
	bool						m_IsMouseOver;
	bool						m_IsVisible;
	int							m_TextureIndex;

};


#endif
