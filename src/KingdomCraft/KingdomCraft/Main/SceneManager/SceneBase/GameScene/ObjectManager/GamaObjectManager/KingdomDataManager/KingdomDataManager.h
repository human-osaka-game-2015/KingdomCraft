﻿/**
 * @file   KingdomDataManager.h
 * @brief  KingdomDataManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMDATAMANAGER_H
#define KINGDOMDATAMANAGER_H

/**
 * 王国のデータ管理クラス
 */
class KingdomDataManager
{
public:
	/**
	 * 王国のデータ構造体
	 */
	struct KINGDOMDATA
	{
		KINGDOMDATA() : 
			Money(0),
			Industry(0),
			Commerce(0),
			Politics(0),
			Knowledge(0),
			History(0),
			Population(0),
			TaxRate(0.f)
		{
		}

		KINGDOMDATA(int _money, int _industry, int _commerce, int _politics, int _knowledge, int _history, int _population, float _taxRate) :
			Money(_money),
			Industry(_industry),
			Commerce(_commerce),
			Politics(_politics),
			Knowledge(_knowledge),
			History(_history),
			Population(_population),
			TaxRate(_taxRate)
		{
		}

		int		Money;		//!< 王国の資金
		int		Industry;	//!< 王国の工業力
		int		Commerce;	//!< 王国の商業力
		int		Politics;	//!< 王国の政治力
		int		Knowledge;	//!< 王国の知識力
		int		History;	//!< 王国の歴史
		int		Population;	//!< 王国の人口
		float	TaxRate;	//!< 王国の税金
	};

	/**
	 * KingdomDataManagerクラスのコンストラクタ
	 */
	KingdomDataManager();

	/**
	 * KingdomDataManagerクラスのデストラクタ
	 */
	~KingdomDataManager();

	/**
	 * KingdomDataManagerクラスの制御関数
	 */
	void Control();

	/**
	 * KingdomDataManagerクラスの描画関数
	 */
	void Draw();


private:
	/**
	 * 王国資金の制御関数
	 */
	void MoneyControl();

	KingdomDataManager(const KingdomDataManager&);
	void operator=(const KingdomDataManager&);

	KINGDOMDATA m_KingdomData;

};


#endif
