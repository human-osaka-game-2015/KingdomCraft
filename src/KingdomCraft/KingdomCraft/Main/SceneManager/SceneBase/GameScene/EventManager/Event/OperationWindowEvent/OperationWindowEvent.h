/**
 * @file OperationWindowEvent.h
 * @brief OperationWindowEventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef OPERATIONWINDOWEVENT_H
#define OPERATIONWINDOWEVENT_H
#include "..\Event.h"

/**
 * OperationWindowに関してのEventクラス
 */
class OperationWindowEvent : public Event
{
public:
	/**
	 * イベントの種類を表す列挙子
	 */
	enum EVENT_TYPE
	{
		NONE,
		OPERATION_WINDOW_BACK,		//!< OperationWindowに処理を戻すイベント
		BUILD_BUTTON_CLICK,			//!< BuildButtonのクリックイベント
		POLITICS_BUTTON_CLICK,		//!< PoliticsButtonのクリックイベント
		SAVE_BUTTON_CLICK,			//!< SaveButtonのクリックイベント
		LOAD_BUTTON_CLICK,			//!< LoadButtonのクリックイベント
		BACK_TO_TITLE_BUTTON_CLICK,	//!< BackToTitleButtonのクリックイベント
		EVENT_TYPE_MAX
	};

	/**
	 * OperationWindowEventクラスのインスタンスを取得する関数
	 * @return OperationWindowEventクラスのインスタンス
	 */
	static OperationWindowEvent* GetInstance()
	{
		static OperationWindowEvent Instance;
		return &Instance;
	}

	/**
	 * EventのIDを取得する関数
	 * @return OperationWindowEventクラスのID
	 */
	inline virtual int GetEventID()
	{
		return m_EventID;
	}

	/**
	 * OperationWindowEventクラスのイベント内容を取得する関数
	 * @return OperationWindowEventクラスに設定されてるイベント
	 */
	inline EVENT_TYPE GetEventType()
	{
		return m_EventType;
	}

	/**
	 * OperationWindowEventクラスのイベント内容を設定する関数
	 * @param[in] _eventType 設定するイベント
	 */
	inline void SetEventType(EVENT_TYPE _eventType)
	{
		m_EventType = _eventType;
	}

private:
	/**
	 * OperationWindowEventクラスのコンストラクタ
	 */
	OperationWindowEvent();
	
	/**
	 * OperationWindowEventクラスのデストラクタ
	 */
	~OperationWindowEvent();

	int			m_EventID;
	EVENT_TYPE	m_EventType;

};


#endif
