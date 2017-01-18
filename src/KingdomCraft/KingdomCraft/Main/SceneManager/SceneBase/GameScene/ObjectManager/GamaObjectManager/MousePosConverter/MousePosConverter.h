/**
 * @file   MousePosConverter.h
 * @brief  MousePosConverterクラスのヘッダファイル
 * @author kotani
 */
#ifndef MOUSEPOSCONVERTER_H
#define MOUSEPOSCONVERTER_H
#include <D3DX11.h>
#include <D3DX10.h>

/**
 * カメラ座標を地面の座標に変換するクラス
 */
class MousePosConverter
{
public:
	/**
	 * インスタンスを生成する関数
	 */
	inline static void Create()
	{
		if (m_pMousePosConverter == NULL)
		{
			m_pMousePosConverter = new MousePosConverter();
		}
	}

	/**
	 * インスタンスを取得する関数
	 * @return MousePosConverterのインスタンス
	 */
	inline static MousePosConverter* GetInstance()
	{
		return m_pMousePosConverter;
	}

	/**
	 * インスタンスを破棄する
	 */
	inline static void Delete()
	{
		delete m_pMousePosConverter;
		m_pMousePosConverter = NULL;
	}

	/**
	 * 地面の座標に変換した座標を取得する
	 * @return 変換後の座標
	 */
	inline D3DXVECTOR3 GetConvertPos()
	{
		return m_ConvertPos;
	}

	/**
	 * MousePosConverterクラスの制御関数
	 */
	void Control();

	
private:
	/**
	 * MousePosConverterクラスのコンストラクタ
	 */
	MousePosConverter();

	/**
	 * MousePosConverterクラスのコンストラクタ
	 */
	~MousePosConverter();

	/**
	 * マウス座標を3D座標に変換する
	 * @param[in,out] _pConvertPos 変換するマウス座標(z座標入り)が3d座標に変換される
	 */
	void Transform2D(D3DXVECTOR3* _pConvertPos);

	static MousePosConverter* m_pMousePosConverter;
	float					  m_ClientWidth;
	float					  m_ClientHeight;

	D3DXVECTOR3				  m_ConvertPos;

};


#endif
