/**
 * @file   LoadWindow.h
 * @brief  LoadWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef LOADWINDOW_H
#define LOADWINDOW_H
#include "..\..\WindowUI\WindowUI.h"

/**
 * ロードを管理するWindowクラス
 */
class LoadWindow : public WindowUI
{
public:
	/**
	 * LoadWindowクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	LoadWindow(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * LoadWindowクラスのデストラクタ
	 */
	virtual ~LoadWindow();

	/**
	 * LoadWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * LoadWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	LoadWindow(const LoadWindow&);
	void operator=(const LoadWindow&);

	static const D3DXVECTOR2	m_DefaultPos;
	static const D3DXVECTOR2	m_DefaultSize;

};


#endif
