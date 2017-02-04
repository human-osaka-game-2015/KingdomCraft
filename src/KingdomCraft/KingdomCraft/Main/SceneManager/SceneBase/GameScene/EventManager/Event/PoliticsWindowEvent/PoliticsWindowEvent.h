/**
 * @file PoliticsWindowEvent.h
 * @brief PoliticsWindowEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef POLITICSWINDOWEVENT_H
#define POLITICSWINDOWEVENT_H
#include "..\Event.h"

/**
 * PoliticsWindowに関するEventクラス
 */
class PoliticsWindowEvent : public Event
{
public:
	/**
	 * イベントの種類を表す列挙子
	 */
	enum EVENT_TYPE
	{
		NONE,
		POLITICS_WINDOW_BACK,			//!< PoliticsWindowに処理を戻すイベント
		SOLDIER_MANAGE_BUTTON_CLICK,	//!< SoldierManagerButtonのクリックイベント
		EVENT_TYPE_MAX
	};

	/**
	 * PoliticsWindowEventクラスのインスタンスを取得する関数
	 * @return PoliticsWindowEventクラスのインスタンス
	 */
	static PoliticsWindowEvent* GetInstance()
	{
		static PoliticsWindowEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return PoliticsWindowEventクラスのID
	 */
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * PoliticsWindowEventクラスのイベント内容を取得する関数
	 * @return PoliticsWindowEventクラスに設定されてるイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}

	/**
	 * PoliticsWindowEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * PoliticsWindowEventクラスのコンストラクタ
	 */
	PoliticsWindowEvent();

	/**
	 * PoliticsWindowEventクラスのデストラクタ
	 */
	~PoliticsWindowEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;

};


#endif
