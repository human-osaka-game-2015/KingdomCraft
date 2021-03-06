﻿/**
 * @file   TextUI.h
 * @brief  TextUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef TEXTUI_H
#define TEXTUI_H
#include <D3DX11.h>
#include <D3DX10.h>

class DebugFont;

/**
 * UIのテキストクラス
 */
class TextUI
{
public:
	/**
	 * TextUIクラスのコンストラクタ
	 * @param[in] _pTextPos テキストの描画位置
	 * @param[in] _pFontSize テキストのフォントサイズ
	 * @param[in] _isVisible テキストの可視設定
	 */
	TextUI(const D3DXVECTOR2* _pTextPos, const D3DXVECTOR2* _pFontSize, bool _isVisible = true);

	/**
	 * TextUIクラスのデストラクタ
	 */
	~TextUI();

	/**
	 * TextUIクラスの制御関数
	 */
	virtual void Control();

	/**
	 * TextUIクラスの描画関数
	 */
	virtual void Draw();

	/**
	 * テキストの可視設定を行う関数
	 * @param[in] _isVisible 可視設定するかのフラグ
	 */
	inline void SetVisible(bool _isVisible)
	{
		m_IsVisible = _isVisible;
	}

protected:
	/**
	 * テキストの描画関数
	 * @param[in] _pStr 描画するテキスト
	 */
	void TextDraw(LPCTSTR _pStr);

	D3DXVECTOR2		m_TextPos;		//!< テキストの座標
	D3DXVECTOR2 	m_FontSize;		//!< テキストのフォントサイズ
	bool			m_IsVisible;	//!< テキストが可視状態か

private:
	DebugFont*		m_pDebugFont;	//!< テキスト描画用クラス

};


#endif
