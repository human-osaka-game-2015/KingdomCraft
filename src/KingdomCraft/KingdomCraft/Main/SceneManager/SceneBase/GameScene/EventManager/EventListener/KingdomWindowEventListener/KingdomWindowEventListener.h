/**
 * @file KingdomWindowEventListener.h
 * @brief KingdomWindowEventListenerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMWINDOWEVENTLISTENER_H
#define KINGDOMWINDOWEVENTLISTENER_H
#include "..\EventListener.h"
#include <vector>

/**
 * KingdomWindowEventのListenerクラス
 */
class KingdomWindowEventListener : public EventListener
{
public:
	/**
	 * KingdomWindowEventListenerクラスのコンストラクタ
	 */
	KingdomWindowEventListener();

	/**
	 * KingdomWindowEventListenerクラスのデストラクタ
	 */
	~KingdomWindowEventListener();

	/**
	 * イベントメッセージを受け取る関数
	 * @param[in] _pEvent 受け取るEventクラスのポインタ
	 */
	virtual void EventMessage(Event* _pEvent);

	/**
	 * 最新のイベント情報を取得する関数
	 * @return 最新のイベント情報
	 */
	int GetEventType();

	/**
	 * イベント情報を格納しているコンテナの中身を破棄する
	 */
	void ClearEventType();

private:
	std::vector<int> m_EventTypeContainer;

};


#endif
