/**
 * @file   BackToTitleWindow.h
 * @brief  BackToTitleWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef BACKTOTITLEWINDOW_H
#define BACKTOTITLEWINDOW_H
#include "..\..\WindowUI\WindowUI.h"

/**
 * タイトルバックを管理するWindowクラス
 */
class BackToTitleWindow : public WindowUI
{
public:
	/**
	 * BackToTitleWindowクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	BackToTitleWindow(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * BackToTitleWindowクラスのデストラクタ
	 */
	virtual ~BackToTitleWindow();

	/**
	 * BackToTitleWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * BackToTitleWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	BackToTitleWindow(const BackToTitleWindow&);
	void operator=(const BackToTitleWindow&);

	static const D3DXVECTOR2	m_DefaultPos;
	static const D3DXVECTOR2	m_DefaultSize;

};


#endif
