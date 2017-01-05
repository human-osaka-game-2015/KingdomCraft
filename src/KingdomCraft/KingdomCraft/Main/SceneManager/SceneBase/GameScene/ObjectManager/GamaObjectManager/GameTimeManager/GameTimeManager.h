/**
 * @file GameTimeManager.h
 * @brief GameTimeManagerクラスのヘッダファイル
 * @author morimoto
 */
#ifndef GAMETIMEMANAGER_H
#define GAMETIMEMANAGER_H

class GameTimeEventListener;

/**
 * ゲーム内の時間を管理するクラス
 */
class GameTimeManager
{
public:
	/**
	 * ゲーム内時間構造体
	 */
	struct GAMETIME
	{
		GAMETIME(int _year, int _month, int _day, int _hour) :
			Year(_year),
			Month(_month),
			Day(_day),
			Hour(_hour)
		{
		}

		GAMETIME() :
			Year(0),
			Month(0),
			Day(0),
			Hour(0)
		{
		}

		int Year;	
		int Month;	
		int Day;	
		int Hour;	
	};

	/**
	 * GameTimeManagerクラスのコンストラクタ
	 */
	GameTimeManager();
	
	/**
	 * GameTimeManagerクラスのデストラクタ
	 */
	~GameTimeManager();

	/**
	 * GameTimeManagerクラスの制御関数
	 */
	void Control();

	/**
	 * GameTimeManagerクラスの描画関数
	 */
	void Draw();

private:
	/**
	 * KingdomStateクラスの状態を表す列挙子
	 * @todo 名前が思いつかなかったのでとりあえずでつけてる
	 */
	enum SPEED_STATE
	{
		NORMAL_SPEED,			// 1倍速
		ONE_POINT_FIVE_SPEED,	// 1.5倍速
		TWO_SPEED,				// 2倍速
		FOUR_SPEED,				// 4倍速
		SIX_SPEED,				// 6倍速
		PAUSE_STATE,			// 停止状態
		STATE_MAX				// STATEの数
	};


	GameTimeManager(const GameTimeManager&);
	void operator=(const GameTimeManager&);

	/**
	 * 状態の制御を行う関数
	 */
	void StateControl();

	/**
	 * 時間の進む速度を一段階加速する関数
	 */
	void AccelerateTime();

	/**
	 * 時間の進む速度を一段階減速する関数
	 */
	void DecelerateTime();

	/**
	 * ゲーム内時間を進める関数
	 */
	void AdvanceTime();

	/**
	 * 時間を進める関数
	 */
	void AdvanceHour();

	/**
	 * 日付を進める関数
	 */
	void AdvanceDay();

	/**
	 * 月を進める関数
	 */
	void AdvanceMonth();

	/**
	 * 年を進める関数
	 */
	void AdvanceYear();


	static const float	m_TimeSpeed[STATE_MAX];	//!< STATEごとのゲーム内時間のスピード
	static const int	m_YearMax;				//!< 年数の上限
	static const int	m_MonthMax;				//!< 月数の上限
	static const int	m_DayMax;				//!< 日数の上限
	static const int	m_HourMax;				//!< 時間の上限

	float					m_Time;				//!< 時間の進行状態を格納する変数
	GAMETIME				m_GameTime;			//!< ゲーム内の時間を格納する変数
	SPEED_STATE				m_SpeedState;		//!< ゲーム内時間の状態を格納する変数
	GameTimeEventListener*	m_pEventListener;
};


#endif
