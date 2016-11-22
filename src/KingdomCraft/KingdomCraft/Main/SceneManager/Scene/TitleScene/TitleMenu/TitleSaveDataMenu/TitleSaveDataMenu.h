/**
 * @file TitleSaveDataMenu.h
 * @brief TitleSaveDataMenuクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TITLESAVEDATAMENU_H
#define TITLESAVEDATAMENU_H
#include <vector>

class TitleSaveDataButton;

/**
 * タイトルメニュー内のセーブメニューの管理クラス
 */
class TitleSaveDataMenu
{
public:
	/**
	 * タイトルセーブデータメニューのID
	 */
	enum MENU_ID
	{
		NONE_ID,		//!< なにも押されていない
		STARTGAME_ID,	//!< セーブデータスロットが押された
		CANCEL_ID		//!< 右クリックが押された
	};

	/**
	 * TitleSaveDataMenuのコンストラクタ
	 */
	TitleSaveDataMenu();

	/**
	 * TitleSaveDataMenuのデストラクタ
	 */
	~TitleSaveDataMenu();

	/**
	 * TitleSaveDataMenuの制御関数
	 * @return TitleSaveDataMenuの状態
	 */
	MENU_ID Control();

	/**
	 * TitleSaveDataMenuの描画関数
	 */
	void Draw();

	/**
	 * TitleSaveDataMenuの可視設定を行う関数
	 *
	 * falseを指定したらControlとDrawは動作しなくなる
	 * trueを指定したらそのまま動作
	 * @param[in] _isVisible 可視設定するかのフラグ
	 */
	inline void SetVisible(bool _isVisible)
	{
		m_IsVisible = _isVisible;
	}

private:
	TitleSaveDataMenu(const TitleSaveDataMenu&);
	void operator=(const TitleSaveDataMenu&);

	static const int					m_SaveDataMenuButtonNum;
	std::vector<TitleSaveDataButton*>	m_pSaveDataButton;
	bool								m_IsVisible;

};


#endif
