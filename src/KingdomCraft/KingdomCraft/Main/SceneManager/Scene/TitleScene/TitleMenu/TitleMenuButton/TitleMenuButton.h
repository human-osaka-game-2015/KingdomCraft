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
 * @todo 削除してUIButtonクラスに差し替える予定
 */
class TitleMenuButton
{
public:
	/**
	 * TitleMenuButtonのコンストラクタ
	 * @param[in] _pButtonPos ボタンの描画位置
	 * @param[in] _pButtonSize ボタンのサイズ
	 * @param[in] _pTextureName 描画するボタンの画像
	 */
	TitleMenuButton(const D3DXVECTOR2* _pButtonPos, const D3DXVECTOR2* _pButtonSize, LPCTSTR _pTextureName);

	/**
	 * TitleMenuButtonのデストラクタ
	 */
	~TitleMenuButton();

	/**
	 * TitleMenuButtonの制御関数
	 * @return ボタンが押されたらtrue
	 */
	bool Control();

	/**
	 * ボタンクラスの描画関数
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

private:
	TitleMenuButton(const TitleMenuButton&);
	void operator=(const TitleMenuButton&);

	/**
	 * ボタンの描画関数
	 */
	void ButtonDraw();

	/**
	 * ボタンがクリックされたかをチェックする関数
	 * @return クリックされたらtrue
	 */
	bool IsClicked();

	static const D3DXVECTOR2	m_ButtonTexel[4];	//!< ボタンのテクスチャ座標
	const D3DXVECTOR2			m_ButtonPos;
	const D3DXVECTOR2			m_ButtonSize;
	Vertex2D*					m_pVertex;
	bool						m_IsMouseOver;
	bool						m_IsVisible;
	int							m_TextureIndex;

};


#endif
