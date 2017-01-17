/**
 * @file HouseBuildWindowEvent.h
 * @brief HouseBuildWindowEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef HOUSEBUILDWINDOWEVENT_H
#define HOUSEBUILDWINDOWEVENT_H
#include "..\Event.h"

class HouseBuildWindowEvent : public Event
{
public:
	/**
	 * イベントの種類を表す列挙子
	 */
	enum EVENT_TYPE
	{
		NONE,
		NORMAL_HOUSE_BUILD_BUTTON_CLICK,
		EVENT_TYPE_MAX
	};

	/**
	 * HouseBuildWindowEventクラスのインスタンスを取得する関数
	 * @return HouseBuildWindowEventクラスのインスタンス
	 */
	static HouseBuildWindowEvent* GetInstance()
	{
		static HouseBuildWindowEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return HouseBuildWindowEventクラスのID
	 */
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * HouseBuildWindowEventクラスのイベント内容を取得する関数
	 * @return HouseBuildWindowEventクラスに設定されてるイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}

	/**
	 * HouseBuildWindowEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * HouseBuildWindowEventクラスのコンストラクタ
	 */
	HouseBuildWindowEvent();

	/**
	 * HouseBuildWindowEventクラスのデストラクタ
	 */
	~HouseBuildWindowEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;
};


#endif
