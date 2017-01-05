/**
 * @file GameTimeEvent.h
 * @brief GameTimeEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMETIMEEVENT_H
#define GAMETIMEEVENT_H
#include "..\Event.h"

/**
 * GameTimeに関してのEventクラス
 */
class GameTimeEvent : public Event
{
public:
	/**
	 * イベントの種類を表す列挙子
	 */
	enum EVENT_TYPE
	{
		NONE,
		NORMAL_TIME,		// 時間の通常化
		ACCELERATE_TIME,	// 時間の加速
		DECELERATE_TIME,	// 時間の減速
		EVENT_TYPE_MAX
	};

	/**
	 * GameTimeEventクラスのインスタンスを取得する関数
	 * @return GameTimeEventクラスのインスタンス
	 */
	static GameTimeEvent* GetInstance()
	{
		static GameTimeEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return GameTimeEventクラスのID
	 */
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * GameTimeEventクラスのイベント内容を取得する関数
	 * @return GameTimeEventクラスに設定されてるイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}
	
	/**
	 * GameTimeEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * GameTimeEventクラスのコンストラクタ
	 */
	GameTimeEvent();

	/**
	 * GameTimeEventクラスのデストラクタ
	 */
	~GameTimeEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;

};


#endif
