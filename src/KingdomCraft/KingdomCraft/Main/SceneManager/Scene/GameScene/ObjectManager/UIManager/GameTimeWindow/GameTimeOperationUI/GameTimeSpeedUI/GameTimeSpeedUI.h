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

	static const D3DXVECTOR2	m_TextPos;	//!< テキストの座標
	static const D3DXVECTOR2	m_FontSize;	//!< テキストのフォントサイズ
	D3DXVECTOR2					m_ParentUIPos;

};



#endif