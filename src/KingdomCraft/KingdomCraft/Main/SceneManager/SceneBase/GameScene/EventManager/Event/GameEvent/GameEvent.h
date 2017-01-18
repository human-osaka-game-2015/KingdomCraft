/**
 * @file GameEvent.h
 * @brief GameEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMEEVENT_H
#define GAMEEVENT_H
#include "..\Event.h"

/**
 * ゲーム内で起きた物事に関してのEventクラス
 */
class GameEvent : public Event
{
public:
	/**
	 * イベントの種類を表す列挙子
	 */
	enum EVENT_TYPE
	{
		NONE,
		VICTORY_EVENT,
		DEFEAT_EVENT,
		EVENT_TYPE_MAX
	};

	/**
	 * GameTimeEventクラスのインスタンスを取得する関数
	 * @return GameTimeEventクラスのインスタンス
	 */
	static GameEvent* GetInstance()
	{
		static GameEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return GameEventクラスのID
	 */
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * GameEventクラスのイベント内容を取得する関数
	 * @return GameEventクラスに設定されてるイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}

	/**
	 * GameEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * GameEventクラスのコンストラクタ
	 */
	GameEvent();

	/**
	 * GameEventクラスのデストラクタ
	 */
	~GameEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;

};


#endif
