/**
 * @file   UIManager.h
 * @brief  UIManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef UIMANAGER_H
#define UIMANAGER_H

class GameTimeWindow;
class KingdomStatusWindow;
class OperationWindow;
class KingdomWindow;
class GameEventLogWindow;

/**
 * UIを管理するクラス
 */
class UIManager
{
public:
	/**
	 * UIManagerのコンストラクタ
	 */
	UIManager();

	/**
	 * UIManagerのデストラクタ
	 */
	~UIManager();

	/**
	 * UIManagerの制御関数
	 */
	void Control();

	/**
	 * UIManagerの描画関数
	 */
	void Draw();

private:
	UIManager(const UIManager&);
	void operator=(const UIManager&);

	GameTimeWindow*			m_pGameTimeWindow;
	KingdomStatusWindow*	m_pKingdomStatusWindow;
	OperationWindow*		m_pOperationWindow;
	KingdomWindow*			m_pKingdomWindow;
	GameEventLogWindow*		m_pGameEventLogWindow;

};


#endif
