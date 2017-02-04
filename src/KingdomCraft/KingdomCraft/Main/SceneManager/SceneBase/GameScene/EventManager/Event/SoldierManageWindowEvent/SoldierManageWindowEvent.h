/**
 * @file SoldierManageWindowEvent.h
 * @brief SoldierManageWindowEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERMANAGEWINDOWEVENT_H
#define SOLDIERMANAGEWINDOWEVENT_H
#include "..\Event.h"

/**
 * SoldierManagerWindowに関してのEventクラス
 */
class SoldierManageWindowEvent : public Event
{
public:
	/**
	 * イベントの種類を表す列挙子
	 */
	enum EVENT_TYPE
	{
		NONE,
		SOLDIER_MANAGE_WINDOW_BACK,
		SOLDIER_CREATE_BUTTON_CLICK,
		SOLDIER_DESTROY_BUTTON_CLICK,
		SOLDIER_DISPATCH_BUTTON_CLICK,
		EVENT_TYPE_MAX
	};

	/**
	 * SoldierManageWindowEventクラスのインスタンスを取得する関数
	 * @return SoldierManageWindowEventクラスのインスタンス
	 */
	static SoldierManageWindowEvent* GetInstance()
	{
		static SoldierManageWindowEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return SoldierManageWindowEventクラスのID
	 */
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * SoldierManageWindowEventクラスのイベント内容を取得する関数
	 * @return SoldierManageWindowEventクラスに設定されてるイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}

	/**
	 * SoldierManageWindowEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * SoldierManageWindowEventクラスのコンストラクタ
	 */
	SoldierManageWindowEvent();

	/**
	 * SoldierManageWindowEventクラスのデストラクタ
	 */
	~SoldierManageWindowEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;

};


#endif
