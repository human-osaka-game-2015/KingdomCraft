/**
 * @file   GameEventLogWindow.h
 * @brief  GameEventLogWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMEEVENTLOGWINDOW_H
#define GAMEEVENTLOGWINDOW_H
#include <vector>
#include "..\WindowUI\WindowUI.h"
#include "EventListener\GameEventListener\GameEventListener.h"
#include "Event\GameEvent\GameEvent.h"

/**
 * ゲーム内イベントログ表示の管理クラス
 */
class GameEventLogWindow : public WindowUI
{
public:
	/**
	 * GameEventLogWindowクラスのコンストラクタ
	 */
	GameEventLogWindow();

	/**
	 * GameEventLogWindowクラスのデストラクタ
	 */
	virtual ~GameEventLogWindow();

	/**
	 * GameEventLogWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * GameEventLogWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	GameEventLogWindow(const GameEventLogWindow&);
	void operator=(const GameEventLogWindow&);

	/**
	 * イベントの制御関数
	 */
	void EventMessageControl();

	/**
	 * イベントログの制御関数
	 */
	void EventLogControl();

	/**
	 * イベントログの描画関数
	 */
	void EventLogDraw();

	static const D3DXVECTOR2			m_DefaultPos;			//!< 表示するイベントログの初期座標
	static const D3DXVECTOR2			m_DefaultSize;			//!< 表示するイベントログの初期サイズ
	static const float					m_DefaultAlpha;			//!< 表示するイベントログの初期アルファ値
	static const D3DXVECTOR2			m_DefaultTexel[4];		//!< デフォルトのテクスチャ座標
	static const D3DXVECTOR2			m_VictoryTexelOffset;	//!< 勝利イベントのテクスチャオフセット値
	static const D3DXVECTOR2			m_DefeatTexelOffset;	//!< 敗北インベントのテクスチャオフセット値
	static const int					m_EventLogMax;			//!< イベントログの最大数
	static const float					m_EventLogMoveSpeed;	//!< イベントログの移動速度
	static const float					m_EventLogAlphaSpeed;	//!< イベントログの透過度変化速度

	Vertex2D*							m_pVertex2D;
	int									m_TextureIndex;
	GameEventListener*					m_pEventListener;
	std::vector<GameEvent::EVENT_TYPE>	m_EventLogs;
	std::vector<D3DXVECTOR2>			m_EventLogsPos;
	std::vector<float>					m_EventLogsAlpha;
	
};


#endif
