/**
 * @file   OperationWindow.h
 * @brief  OperationWindowクラスのヘッダファイル
 * @author morimoto
 */
#ifndef OPERATIONWINDOW_H
#define OPERATIONWINDOW_H
#include "..\UIWindow\UIWindow.h"

/**
 * プレイヤーの操作UIを管理するクラス
 */
class OperationWindow : public UIWindow
{
public:
	/**
	 * OperationWindowクラスのコンストラクタ
	 */
	OperationWindow();

	/**
	 * OperationWindowクラスのデストラクタ
	 */
	virtual ~OperationWindow();

	/**
	 * OperationWindowクラスの制御関数
	 */
	virtual void Control();

	/**
	 * OperationWindowクラスの描画関数
	 */
	virtual void Draw();

private:
	/**
	 * 操作ウィンドウ内にあるUIの種類 
	 */
	enum  OPERATION_TYPE
	{
		BUILD_TYPE,			//!< 建築UI
		POLITICS_TYPE,		//!< 政治UI
		SAVE_TYPE,			//!< セーブUI
		LOAD_TYPE,			//!< ロードUI
		TITLEBACK_TYPE,		//!< タイトルバックUI
		OPERATION_MAX		//!< OperationWindowのUI数
	};

	OperationWindow(const OperationWindow&);
	void operator=(const OperationWindow&);

	static const D3DXVECTOR2	m_OperationUISize;						//!< UIの矩形サイズ
	static const D3DXVECTOR2	m_OperationUIPos[OPERATION_MAX];		//!< UIの座標
	static const D3DXVECTOR2	m_OperationUITexel[4];					//!< UIのテクスチャ座標
	static const D3DXVECTOR2	m_OperationUITexelOffset[OPERATION_MAX];//!< UIのテクスチャ座標のスクロール値

};


#endif
