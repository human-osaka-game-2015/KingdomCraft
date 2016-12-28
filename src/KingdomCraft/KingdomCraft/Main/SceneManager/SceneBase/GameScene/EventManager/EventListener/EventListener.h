/**
 * @file EventListener.h
 * @brief EventListenerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

class Event;

/**
 * イベントが発生したかどうかを聞くクラス
 */
class EventListener
{
public:
	/**
	 * EventListenerクラスのコンストラクタ
	 */
	EventListener();

	/**
	 * EventListenerクラスのデストラクタ
	 */
	virtual ~EventListener();

	/**
	 * イベントメッセージを受け取る関数
	 * @param[in] _pEvent 受け取るEventクラスのポインタ
	 */
	virtual void EventMessage(Event* _pEvent);

	/**
	 * EventListenerクラスのIDを取得する関数
	 * @return EventListenerクラスのID
	 */
	int GetEventListenerID()
	{
		return m_EventListenerID;
	}

private:
	static int	m_EventListenerNum;
	int			m_EventListenerID;

};


#endif
