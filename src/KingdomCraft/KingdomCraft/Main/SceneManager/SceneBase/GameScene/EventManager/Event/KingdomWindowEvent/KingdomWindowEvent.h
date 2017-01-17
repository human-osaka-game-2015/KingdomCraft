/**
 * @file KingdomWindowEvent.h
 * @brief KingdomWindowEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMWINDOWEVENT_H
#define KINGDOMWINDOWEVENT_H
#include "..\Event.h"

/**
 * KingdomWindowに関してのEventクラス
 */
class KingdomWindowEvent : public Event
{
public:
	enum EVENT_TYPE
	{
		NONE,
		PUSH_BUTTON,
		EVENT_TYPE_MAX
	};

	/**
	 * KingdomWindowEventクラスのインスタンスを取得する関数
	 * @return KingdomWindowEventのインスタンス
	 */
	static KingdomWindowEvent* GetInstance()
	{
		static KingdomWindowEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return KingdomWindowEventクラスのID
	 */
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * KingdomWindowEventクラスのイベント内容を取得する関数
	 * @return KingdomWindowEventに設定されているイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}

	/**
	 * KingdomWindowEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * KingdomWindowEventクラスのコンストラクタ
	 */
	KingdomWindowEvent();

	/**
	 * KingdomWindowEventクラスのデストラクタ
	 */
	~KingdomWindowEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;

};


#endif
