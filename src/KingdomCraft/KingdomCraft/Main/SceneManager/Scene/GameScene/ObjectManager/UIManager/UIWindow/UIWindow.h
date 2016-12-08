/**
 * @file   UIWindow.h
 * @brief  UIWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef UIWINDOW_H
#define UIWINDOW_H
#include "Vertex2D\Vertex2D.h"

/**
 * UIWindowクラス
 */
class UIWindow
{
public:
	/**
	 * UIWindowクラスのコンストラクタ
	 * @param[in] _pWindowPos ウィンドウの座標
	 * @param[in] _pWindowSize ウィンドウのサイズ
	 * @param[in] _isVisible ウィンドウの可視設定フラグ
	 */
	UIWindow(const D3DXVECTOR2* _pWindowPos, const D3DXVECTOR2* _pWindowSize, bool _isVisible = true);

	/**
	 * UIWindowクラスのデストラクタ
	 */
	virtual ~UIWindow();

	/**
	 * UIWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * UIWindowクラスの描画関数
	 */
	virtual void Draw();

	/**
	 * UIWindowの可視設定を行う関数
	 * @param[in] _isVisible 可視状態にするかのフラグ
	 */
	void SetVisible(bool _isVisible)
	{
		m_IsVisible = _isVisible;
	}

protected:
	D3DXVECTOR2		m_WindowPos;	//!< ウィンドウの座標
	D3DXVECTOR2 	m_WindowSize;	//!< ウィンドウのサイズ
	bool			m_IsVisible;	//!< ウィンドウの可視状態

private:
	/**
	 * ウィンドウのパーツID
	 */
	enum WINDOW_PARTS
	{
		LEFT_TOP,		//!< ウインドウの左上
		CENTER_TOP,		//!< ウィンドウの中央上	
		RIGHT_TOP,		//!< ウインドウの右上
		LEFT,			//!< ウィンドウの左
		CENTER,			//!< ウィンドウの中央
		RIGHT,			//!< ウィンドウの右
		LEFT_BOTTOM,	//!< ウインドウの左下
		CENTER_BOTTOM,	//!< ウィンドウの中央下
		RIGHT_BOTTOM,	//!< ウインドウの右下
		PARTS_MAX		//!< ウィンドウのパーツ数
	};

	UIWindow(const UIWindow&);
	void operator=(const UIWindow&);

	static const D3DXVECTOR2	m_WindowPartsUV[PARTS_MAX][4];
	Vertex2D*					m_pWindowVertex;
	int							m_TextureIndex;

};


#endif
