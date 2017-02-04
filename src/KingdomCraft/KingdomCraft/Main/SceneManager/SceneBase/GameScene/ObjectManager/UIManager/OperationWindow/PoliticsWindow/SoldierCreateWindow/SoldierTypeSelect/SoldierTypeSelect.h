/**
 * @file   SoldierTypeSelect.h
 * @brief  SoldierTypeSelectクラスのヘッダファイル
 * @author morimoto
 */
#ifndef SOLDIERTYPESELECT_H
#define SOLDIERTYPESELECT_H
#include "Vertex2D\Vertex2D.h"

class SelectLeftButtonUI;
class SelectRightButtonUI;

/**
 * 生成する兵士の種類を管理するクラス
 */
class SoldierTypeSelect
{
public:
	/**
	 * 選択される兵士の種類
	 */
	enum SELECT_SOLDIER_TYPE
	{
		SWORD_TYPE,			//!< 剣士
		ARCHER_TYPE,		//!< 弓兵
		WITCH_TYPE,			//!< 魔法使い
		SELECT_SOLDIER_MAX	//!< 種類の最大数
	};

	/**
	 * SoldierTypeSelectクラスのコンストラクタ
	 * @param[in] _pParentUIPos 親UIの座標
	 * @param[in] _textureIndex 使用するテクスチャのインデックス番号
	 */
	SoldierTypeSelect(const D3DXVECTOR2* _pParentUIPos, int _textureIndex);
	~SoldierTypeSelect();
	void Control();
	void Draw();

private:
	/**
	 * 左移動が選択された際の処理を行う関数
	 */
	void SelectMoveToLeft();

	/**
	 * 右移動が選択された際の処理を行う関数
	 */
	void SelectMoveToRight();

	/**
	 * 選択された兵科を描画する関数
	 */
	void SelectTypeDraw();

	static const D3DXVECTOR2	m_DefaultPos;
	static const D3DXVECTOR2	m_DefaultSize;
	static const D3DXVECTOR2	m_DefaultTexel[4];
	static const D3DXVECTOR2	m_TexelOffset;
	D3DXVECTOR2					m_Pos;
	const D3DXVECTOR2*			m_pParentUIPos;
	SelectLeftButtonUI*			m_pLeftButton;
	SelectRightButtonUI*		m_pRightButton;
	SELECT_SOLDIER_TYPE			m_SelectType;
	Vertex2D*					m_pVertex2D;
	int							m_TextureIndex;

};


#endif
