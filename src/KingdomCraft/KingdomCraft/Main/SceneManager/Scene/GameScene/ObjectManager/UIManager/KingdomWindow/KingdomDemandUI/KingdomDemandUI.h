/**
 * @file   KingdomDemandUI.h
 * @brief  KingdomDemandUIクラスのヘッダファイル
 * @author morimoto
 */
#ifndef KINGDOMDEMAND_H
#define KINGDOMDEMAND_H

/**
 * 国内の需要UIを管理するクラス
 */
class KingdomDemandUI
{
public:
	/**
	 * KingdomDemandUIクラスのコンストラクタ
	 */
	KingdomDemandUI();

	/**
	 * KingdomDemandUIクラスのデストラクタ
	 */
	~KingdomDemandUI();

	/**
	 * KingdomDemandUIクラスの制御関数
	 */
	void Control();

	/**
	 * KingdomDemandUIクラスの描画関数
	 */
	void Draw();

private:
	KingdomDemandUI(const KingdomDemandUI&);
	void operator=(const KingdomDemandUI&);

};


#endif
