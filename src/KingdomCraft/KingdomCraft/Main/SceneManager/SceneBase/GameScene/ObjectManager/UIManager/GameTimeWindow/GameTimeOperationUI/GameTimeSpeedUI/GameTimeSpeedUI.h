/**
 * @file   GameTimeSpeedUI.h
 * @brief  GameTimeSpeedUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMETIMESPEEDUI_H
#define GAMETIMESPEEDUI_H
#include "..\..\..\TextUI\TextUI.h"

/**
 * ゲームの進行スピード表示を管理するクラス
 */
class GameTimeSpeedUI : public TextUI
{
public:
	/**
	 * GameTimeSpeedUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	GameTimeSpeedUI(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * GameTimeSpeedUIクラスのデストラクタ
	 */
	~GameTimeSpeedUI();

	/**
	 * GameTimeSpeedUIクラスの制御関数
	 */
	void Control();

	/**
	 * GameTimeSpeedUIクラスの描画関数
	 */
	void Draw();

private:
	GameTimeSpeedUI(const GameTimeSpeedUI&);
	void operator=(const GameTimeSpeedUI&);

	static const D3DXVECTOR2	m_DefaultTextPos;	//!< テキストの初期座標
	static const D3DXVECTOR2	m_DefaultFontSize;	//!< テキストのフォント初期サイズ
	D3DXVECTOR2					m_ParentUIPos;

};



#endif