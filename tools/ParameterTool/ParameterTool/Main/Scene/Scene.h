#ifndef SCENE_H
#define SCENE_H
#include <Windows.h>

class FieldManager;
class HouseManager;
class FieldMessenger;

class Scene
{
public:
	/**
	 * Sceneクラスのコンストラクタ
	 * @param[in] _hWnd 対応するウィンドウハンドル
	 * @param[in] _hInst 対応するインスタンスハンドル
	 */
	Scene(HWND _hWnd, HINSTANCE _hInst);

	/**
	 * Sceneクラスのデストラクタ 
	 */
	~Scene();

	/**
	 * Sceneクラスの実行関数
	 * @return Sceneが終了したらtrueが返る
	 */
	bool Run();

private:
	/**
	 * Sceneクラスの制御関数
	 * @return Sceneが終了したらtrueが返る(現在はfalseしか返さない)
	 */
	bool Control();

	/**
	 * Sceneクラスの描画関数
	 * @return Sceneが終了したらtrueが返る
	 */
	void Draw();

	HWND			m_hWnd;
	HINSTANCE		m_hInstance;
	FieldManager*	m_pFieldManager;
	FieldMessenger* m_pFieldMessenger;
	HouseManager*	m_pHouseManager;

};


#endif // !SCENE_H
