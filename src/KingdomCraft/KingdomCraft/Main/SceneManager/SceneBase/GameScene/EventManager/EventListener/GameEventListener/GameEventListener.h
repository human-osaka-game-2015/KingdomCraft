/**
 * @file GameEventListener.h
 * @brief GameEventListenerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMEEVENTLISTENER_H
#define GAMEEVENTLISTENER_H
#include <vector>
#include "..\EventListener.h"

/**
 * GameEventのイベントメッセージを受け取るクラス
 */
class GameEventListener : public EventListener
{
public:
	/**
	 * GameEventListenerクラスのコンストラクタ
	 */
	GameEventListener();

	/**
	 * GameEventListenerクラスのデストラクタ
	 */
	virtual ~GameEventListener();

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

	static const int m_EventMessageMax;		//!< イベントの最大数

private:
	std::vector<int> m_EventTypeContainer;

};


#endif
