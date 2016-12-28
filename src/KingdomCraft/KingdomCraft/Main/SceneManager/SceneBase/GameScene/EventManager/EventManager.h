/**
 * @file EventManager.h
 * @brief EventManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include <vector>

class EventListener;
class Event;

/**
 * EventとEventListenerを管理するクラス
 */
class EventManager
{
public:
	/**
	 * インスタンスを生成する関数
	 */
	inline static void Create()
	{
		if (m_pEventManager == NULL)
		{
			m_pEventManager = new EventManager();
		}
	}

	/**
	 * インスタンスを取得する関数
	 * @return EventManagerクラスのインスタンス
	 */
	inline static EventManager* GetInstance()
	{
		return m_pEventManager;
	}

	/**
	 * インスタンスを破棄する関数
	 */
	inline static void Delete()
	{
		delete m_pEventManager;
		m_pEventManager = NULL;
	}

	/**
	 * EventListenerを登録する関数
	 * @param[in] _pEventListener 登録するEventListenerのポインタ
	 */
	void AddEventListener(EventListener* _pEventListener);

	/**
	 * EventListenerを削除する関数
	 * @param[in] _pEventListener 削除するEventListenerのポインタ
	 */
	void RemoveEventListener(EventListener* _pEventListener);

	/**
	 * イベントをEventListenerに送信する関数
	 * @param[in] _pEvent 送信するEventのポインタ
	 */
	void SendEventMessage(Event* _pEvent);

private:
	/**
	 * EventManagerクラスのコンストラクタ
	 */
	EventManager();

	/**
	 * EventManagerクラスのデストラクタ
	 */
	~EventManager();

	static EventManager*		m_pEventManager;
	std::vector<EventListener*> m_EventListeners;

};


#endif
