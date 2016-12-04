/**
 * @file TitleMenu.h
 * @brief TitleMenuクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLEMENU_H
#define TITLEMENU_H
#include "Vertex2D\Vertex2D.h"

class TitleMenuButton;
class TitleSaveDataMenu;

/**
 * タイトルシーン内のメニューを管理するクラス
 */
class TitleMenu
{
public:
	/**
	 * タイトルメニューのボタンID
	 */
	enum MENU_ID
	{
		NONE_ID,	//!< なにも押されていない
		START_ID,	//!< はじめからが押されてゲームが開始した
		CONTINUE_ID	//!< 続きからが押されてゲームが開始した
	};

	/**
	 * TitleMenuのコンストラクタ
	 */
	TitleMenu();

	/**
	 * TitleMenuのデストラクタ
	 */
	~TitleMenu();

	/**
	 * TitleMenuの制御関数
	 * @return TitleMenuの状態が返ってくる
	 */
	MENU_ID Control();

	/**
	 * TitleMenuの描画関数
	 */
	void Draw();

private:
	TitleMenu(const TitleMenu&);
	void operator=(const TitleMenu&);

	static D3DXVECTOR2	m_StartButtonVertex;
	static D3DXVECTOR2	m_StartButtonPos;
	static D3DXVECTOR2	m_ContinueButtonVertex;
	static D3DXVECTOR2	m_ContinueButtonPos;
	TitleSaveDataMenu*	m_pTitleSaveDataMenu;	// 続きからを押した後に出るセーブデータメニュー
	TitleMenuButton*	m_pStartButton;			// 初めからのボタン
	TitleMenuButton*	m_pContinueButton;		// 続きからのボタン

};


#endif
