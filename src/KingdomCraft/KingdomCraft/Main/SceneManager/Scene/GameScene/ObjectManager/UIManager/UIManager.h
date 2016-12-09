/**
 * @file   UIManager.h
 * @brief  UIManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef UIMANAGER_H
#define UIMANAGER_H

class GameTimeWindow;
class KingdomWindow;
class OperationWindow;

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

	GameTimeWindow*		m_pGameTimeWindow;
	KingdomWindow*		m_pKingdomWindow;
	OperationWindow*	m_pOperationWindow;

};


#endif
