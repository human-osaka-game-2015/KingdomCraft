/**
 * @file   GameTimeOperationUI.h
 * @brief  GameTimeOperationUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMETIMEOPERATIONUI_H
#define GAMETIMEOPERATIONUI_H
#include "Vertex2D\Vertex2D.h"

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
	 * @param[in] _pParentUIPos 親UIの座標
	 */
	GameTimeOperationUI(const D3DXVECTOR2* _pParentUIPos);

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
	D3DXVECTOR2					m_ParentUIPos;
	int							m_TextureIndex;

};


#endif
