/**
 * @file   WindowUI.h
 * @brief  WindowUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef WINDOWUI_H
#define WINDOWUI_H
#include "Vertex2D\Vertex2D.h"

/**
 * WindowUIクラス
 */
class WindowUI
{
public:
	/**
	 * WindowUIクラスのコンストラクタ
	 * @param[in] _pWindowPos ウィンドウの座標
	 * @param[in] _pWindowSize ウィンドウのサイズ
	 * @param[in] _isVisible ウィンドウの可視設定フラグ
	 */
	WindowUI(const D3DXVECTOR2* _pWindowPos, const D3DXVECTOR2* _pWindowSize, bool _isVisible = true);

	/**
	 * WindowUIクラスのデストラクタ
	 */
	virtual ~WindowUI();

	/**
	 * WindowUIクラスの制御関数
	 */
	virtual void Control();

	/**
	 * WindowUIクラスの描画関数
	 */
	virtual void Draw();

	/**
	 * WindowUIの可視設定を行う関数
	 * @param[in] _isVisible 可視状態にするかのフラグ
	 */
	void SetVisible(bool _isVisible)
	{
		m_IsVisible = _isVisible;
	}

protected:
	/**
	 * ウィンドウの描画関数
	 */
	void WindowDraw();

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

	WindowUI(const WindowUI&);
	void operator=(const WindowUI&);

	static const D3DXVECTOR2	m_WindowPartsTexel[4];					//!< ウィンドウパーツのテクスチャ座標
	static const D3DXVECTOR2	m_WindowPartsTexelOffset[PARTS_MAX];	//!< ウィンドウパーツのテクスチャ座標のスクロール値

	Vertex2D*					m_pWindowVertex;
	int							m_WindowTextureIndex;
	D3DXVECTOR2					m_WindowPartsSize;						//!< ウィンドウパーツのサイズ
	D3DXVECTOR2					m_WindowPartsPosOffset[PARTS_MAX];		//!< ウィンドウパーツの座標オフセット値

};


#endif
