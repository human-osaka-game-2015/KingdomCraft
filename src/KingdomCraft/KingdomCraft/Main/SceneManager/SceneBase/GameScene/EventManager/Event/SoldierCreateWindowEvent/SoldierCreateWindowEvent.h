/**
 * @file SoldierCreateWindowEvent.h
 * @brief SoldierCreateWindowEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERCREATEWINDOWEVENT_H
#define SOLDIERCREATEWINDOWEVENT_H
#include "..\Event.h"

class SoldierCreateWindowEvent : public Event
{
public:
	/**
	 * イベントの種類を表す列挙子
	 */
	enum EVENT_TYPE
	{
		NONE,
		EVENT_TYPE_MAX
	};

	/**
	 * SoldierCreateWindowEventクラスのインスタンスを取得する関数
	 * @return SoldierCreateWindowEventクラスのインスタンス
	 */
	static SoldierCreateWindowEvent* GetInstance()
	{
		static SoldierCreateWindowEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return SoldierCreateWindowEventクラスのID
	*/
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * SoldierCreateWindowEventクラスのイベント内容を取得する関数
	 * @return SoldierCreateWindowEventクラスに設定されてるイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}

	/**
	 * SoldierCreateWindowEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * SoldierCreateWindowEventクラスのコンストラクタ
	 */
	SoldierCreateWindowEvent();

	/**
	 * SoldierCreateWindowEventクラスのデストラクタ
	 */
	~SoldierCreateWindowEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;

};


#endif
