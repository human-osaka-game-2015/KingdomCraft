/**
 * @file   GameTimeWindow.h
 * @brief  GameTimeWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMETIMEWINDOW_H
#define GAMETIMEWINDOW_H
#include "..\UIWindow\UIWindow.h"

/**
 * ゲームタイムUIの管理クラス
 */
class GameTimeWindow : public UIWindow
{
public:
	/**
	 * GameTimeWindowクラスのコンストラクタ
	 */
	GameTimeWindow();

	/**
	 * GameTimeWindowクラスのデストラクタ
	 */
	virtual ~GameTimeWindow();

	/**
	 * GameTimeWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * GameTimeWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	GameTimeWindow(const GameTimeWindow&);
	void operator=(const GameTimeWindow&);

	static const D3DXVECTOR2	m_GameTimeWindowSize;
	static const D3DXVECTOR2	m_GameTimeWindowPos;
	int							m_TextureIndex;

};


#endif
