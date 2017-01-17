/**
 * @file BuildWindowEvent.h
 * @brief BuildWindowEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef BUILDWINDOWEVENT_H
#define BUILDWINDOWEVENT_H
#include "..\Event.h"

/**
 * BuildWindowに関してのイベントクラス
 */
class BuildWindowEvent : public Event
{
public:
	/**
	 * イベントの種類を表す列挙子
	 */
	enum EVENT_TYPE
	{
		NONE,
		BUILD_WINDOW_BACK,			//!< BuildWindowに処理を戻すイベント
		HOUSE_BUILD_BUTTON_CLICK,	//!< HouseBuildButtonのクリックイベント
		HOUSE_DESTROY_BUTTON_CLICK,	//!< HouseDestroyButtonのクリックイベント
		ROAD_LAYING_BUTTON_CLICK,	//!< RoadLayingButtonのクリックイベント
		EVENT_TYPE_MAX
	};

	/**
	 * BuildWindowEventクラスのインスタンスを取得する関数
	 * @return BuildWindowEventクラスのインスタンス
	 */
	static BuildWindowEvent* GetInstance()
	{
		static BuildWindowEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return BuildWindowEventクラスのID
	 */
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * BuildWindowEventクラスのイベント内容を取得する関数
	 * @return BuildWindowEventクラスに設定されてるイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}

	/**
	 * BuildWindowEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * BuildWindowEventクラスのコンストラクタ
	 */
	BuildWindowEvent();

	/**
	 * BuildWindowEventクラスのデストラクタ
	 */
	~BuildWindowEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;

};


#endif
