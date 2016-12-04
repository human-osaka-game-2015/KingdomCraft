#ifndef HOUSEMANAGER_H
#define HOUSEMANAGER_H
#include <Windows.h>
#include <vector>

class House;
class HouseBuildManager;
class FieldMessenger;

class HouseManager
{
public:
	/**
	 * HouseManagerクラスのコンストラクタ
	 * @param[in] _pFieldManager HouseManagerクラスと対応させるFieldManagerクラスのインスタンス
	 * @param[in] _hInst HouseManagerクラスと対応するインスタンスハンドル
	 */
	HouseManager(FieldMessenger* _pFieldMessenger, HINSTANCE _hInst);

	/**
	 * HouseManagerクラスのデストラクタ
	 */
	~HouseManager();

	/**
	 * HouseManagerクラスの制御関数
	 */
	void Control();

	/**
	 * HouseManagerクラスの描画関数
	 */
	void Draw();

private:
	std::vector<House*>	m_pHouse;
	HouseBuildManager*	m_pHouseBuildManager;
	FieldMessenger*		m_pFieldMessenger;
	HINSTANCE			m_hInstance;

};


#endif // !HOUSEMANAGER_H
