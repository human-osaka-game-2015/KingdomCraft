/**
 * @file TitleSaveDataButton.h
 * @brief TitleSaveDataButtonクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLESAVEDATABUTTON_H
#define TITLESAVEDATABUTTON_H
#include "Vertex2D\Vertex2D.h"

/**
 * タイトルメニュー内のセーブメニューのボタンクラス
 */
class TitleSaveDataButton
{
public:
	/**
	 * TitleSaveDataButtonのコンストラクタ
	 * @param[in] _pDrawPos ボタンの描画位置
	 * @param[in] _pDrawSize ボタンのサイズ
	 * @param[in] _textureName 描画するボタンの画像
	 */
	TitleSaveDataButton(const D3DXVECTOR2* const _pDrawPos, const D3DXVECTOR2* const _pDrawSize, LPCTSTR const _pTextureName);

	/**
	 * TitleSaveDataButtonのデストラクタ
	 */
	~TitleSaveDataButton();

	/**
	 * TitleSaveDataButtonの制御関数
	 *
	 * ボタンが押されたかのチェックだけしている\n
	 * SetVisibleでfalseを指定したらチェックせずfalseを返す
	 * @return ボタンが押されたらtrue
	 */
	bool Control();

	/**
	 * TitleSaveDataButtonの描画関数
	 */
	void Draw();

private:
	TitleSaveDataButton(const TitleSaveDataButton&);
	void operator=(const TitleSaveDataButton&);

	D3DXVECTOR2 m_DrawPos;
	D3DXVECTOR2 m_DrawSize;

};

#endif
