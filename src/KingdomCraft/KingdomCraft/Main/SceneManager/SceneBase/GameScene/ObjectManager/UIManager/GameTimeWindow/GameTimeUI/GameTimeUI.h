/**
 * @file   GameTimeUI.h
 * @brief  GameTimeUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMETIMEUI_H
#define GAMETIMEUI_H
#include "Vertex\Vertex.h"
#include "..\..\TextUI\TextUI.h"
#include "..\..\..\..\GameDataManager\GameDataManager.h"

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
	/**
	 * 年の描画
	 */
	void YearTextDraw();

	/**
	 * 月の描画
	 */
	void MonthTextDraw();

	/**
	 * 日付の描画
	 */
	void DayTextDraw();

	/**
	 * 時間の描画
	 */
	void HourTextDraw();

	GameTimeUI(const GameTimeUI&);
	void operator=(const GameTimeUI&);

	static const D3DXVECTOR2	m_DefaultTextPos;	//!< ゲーム内時間テキストの初期座標
	static const D3DXVECTOR2	m_DefaultFontSize;	//!< ゲーム内時間テキストのフォント初期サイズ
	static const D3DXVECTOR2	m_YearTextPos;		//!< 年の描画位置
	static const D3DXVECTOR2	m_MonthTextPos;		//!< 月の描画位置
	static const D3DXVECTOR2	m_DayTextPos;		//!< 日付の描画位置
	static const D3DXVECTOR2	m_HourTextPos;		//!< 時間の描画位置
	static const Vertex::VERTEX m_DefaultVertexData[4];
	D3DXVECTOR2					m_ParentUIPos;		//!< 親UIの座標位置
	Vertex*						m_pVertex;
	int							m_TextureIndex;
	GameTimeManager::GAMETIME	m_GameTime;

};


#endif
