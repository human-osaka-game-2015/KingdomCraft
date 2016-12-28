/**
 * @file   GameTimeUI.h
 * @brief  GameTimeUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMETIMEUI_H
#define GAMETIMEUI_H
#include "..\..\TextUI\TextUI.h"

/**
 * ゲーム内時間UIを管理するクラス
 */
class GameTimeUI : public TextUI
{
public:
	/** 
	 * GameTimeUIクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	GameTimeUI(const D3DXVECTOR2* _pParentUIPos);

	/**
	 * GameTimeUIクラスのデストラクタ
	 */
	virtual ~GameTimeUI();

	/**
	 * GameTimeUIクラスの制御関数
	 */
	virtual void Control();

	/**
	 * GameTimeUIクラスの描画関数
	 */
	virtual void Draw();

private:
	GameTimeUI(const GameTimeUI&);
	void operator=(const GameTimeUI&);

	static const D3DXVECTOR2	m_DefaultTextPos;	//!< ゲーム内時間テキストの初期座標
	static const D3DXVECTOR2	m_DefaultFontSize;	//!< ゲーム内時間テキストのフォント初期サイズ
	D3DXVECTOR2					m_ParentUIPos;		//!< 親UIの座標位置

};


#endif
