/**
 * @file Event.h
 * @brief Eventクラスのヘッダファイル
 * @author morimoto
 */
#ifndef EVENT_H
#define EVENT_H

/**
 * イベントクラス
 */
class Event
{
public:
	/**
	 * Eventクラスのコンストラクタ
	 */
	Event();

	/**
	 * Eventクラスのデストラクタ
	 */
	~Event();

	/**
	 * EventクラスのIDを取得する関数
	 * @return EventクラスのID
	 */
	virtual int GetEventID() = 0;

protected:
	static const int	m_ErrorID;
	static int			m_EventNum;

};


#endif
