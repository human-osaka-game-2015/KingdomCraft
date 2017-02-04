#ifndef SOLDIERCREATEWINDOWEVENTLISTENER_H
#define SOLDIERCREATEWINDOWEVENTLISTENER_H
#include <vector>
#include "..\EventListener.h"

class SoldierCreateWindowEventListener : public EventListener
{
public:
	/**
	 * SoldierManageWindowEventListenerクラスのコンストラクタ
	 */
	SoldierCreateWindowEventListener();

	/**
	 * SoldierManageWindowEventListenerクラスのデストラクタ
	 */
	virtual ~SoldierCreateWindowEventListener();

	/**
	 * イベントメッセージを受け取る関数
	 * @param[in] _pEvent 受け取るEventクラスのポインタ
	 */
	virtual void EventMessage(Event* _pEvent);

	/**
	 * 最新のイベント情報を取得する関数
	 * @return 最新のイベントの種類
	 */
	int GetEventType();

	/**
	 * イベント情報を格納しているコンテナの中身を破棄する
	 */
	void ClearEventType();

private:
	std::vector<int>	m_EventTypeContainer;

};


#endif
