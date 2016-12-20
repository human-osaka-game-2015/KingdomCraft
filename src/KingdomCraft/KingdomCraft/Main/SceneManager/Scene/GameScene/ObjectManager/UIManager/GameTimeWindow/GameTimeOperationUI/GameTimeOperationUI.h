/**
 * @file   GameTimeOperationUI.h
 * @brief  GameTimeOperationUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMETIMEOPERATIONUI_H
#define GAMETIMEOPERATIONUI_H

class DecelerateOfTimeButtonUI;
class AccelerateOfTimeButtonUI;
class NormalTimeButtonUI;
class GameTimeSpeedUI;

/**
 * ゲーム内時間の速度変更ボタンを管理するクラス
 */
class GameTimeOperationUI
{
public:
	/**
	 * GameTimeOperationUIクラスのコンストラクタ
	 */
	GameTimeOperationUI();

	/**
	 * GameTimeOperationUIクラスのデストラクタ
	 */
	~GameTimeOperationUI();

	/**
	 * GameTimeOperationUIクラスの制御関数
	 */
	void Control();
	
	/**
	 * GameTimeOperationUIクラスの描画関数
	 */
	void Draw();

private:
	GameTimeOperationUI(const GameTimeOperationUI&);
	void operator=(const GameTimeOperationUI&);

	DecelerateOfTimeButtonUI*	m_pDecelerateButton;
	AccelerateOfTimeButtonUI*	m_pAccelerateButton;
	NormalTimeButtonUI*			m_pNormalButton;
	GameTimeSpeedUI*			m_pGameTimeSpeed;

};


#endif
