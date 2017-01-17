/**
 * @file   SaveWindow.h
 * @brief  SaveWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SAVEWINDOW_H
#define SAVEWINDOW_H
#include "..\..\WindowUI\WindowUI.h"

/**
 * セーブを管理するWindowクラス
 */
class SaveWindow : public WindowUI
{
public:
	/**
	 * SaveWindowクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	SaveWindow(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * SaveWindowクラスのデストラクタ
	 */
	virtual ~SaveWindow();

	/**
	 * SaveWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * SaveWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	SaveWindow(const SaveWindow&);
	void operator=(const SaveWindow&);

	static const D3DXVECTOR2	m_DefaultPos;
	static const D3DXVECTOR2	m_DefaultSize;

};


#endif
