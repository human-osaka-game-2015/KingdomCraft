/**
 * @file   DSoundManager.h
 * @brief  DSoundManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef DXSOUNDMANAGER_H
#define DXSOUNDMANAGER_H
#include <windows.h>
#include <dsound.h>
#include <vector>

enum SOUND_OPERATION
{
	SOUND_PLAY,
	SOUND_STOP,
	SOUND_LOOP,
	SOUND_RESET,
	SOUND_STOP_RESET
};

/**
 * @brief サウンドの再生をするクラス
 *
 * ここでサウンドのリソースを管理し実体は一つで良いのでシングルトンクラスにしている
 */
class DSoundManager
{
public:
	
	/**
	 * 初期化処理
	 * @return 成功したらtrue
	 */
	bool Init();

	/**
	 * 解放処理
	 */
	inline void Release(){ m_pDSound8->Release(); }

	/**
	 * 音声の読み込み
	 * @param[in]  _filename 読み込むファイルの名前
	 * @param[out] _pKey データの格納先のキー
	 * @return	   成功したらtrue
	 */
	bool LoadSound(char* _filename, int* _pKey);
	
	/**
	 * 音声の開放
	 * @param[in] _key 開放先のキー
	 */
	inline void ReleaseSound(int _key){ m_pSound[_key]->Release(); }

	/**
	 * サウンドの操作関数
	 * @param[in] _key 操作するサウンドの格納先のキー
	 * @param[in] _operation どのような操作をするか
	 */
	void SoundOperation(int _key, SOUND_OPERATION _operation);

	/**
	 * インスタンス生成関数
	 * @param[in] _hWnd ウィンドウハンドル。コンストラクタ内で使う
	 */
	static void Create(HWND _hWnd)
	{
		if (m_pSoundManager == NULL)
		{
			m_pSoundManager = new DSoundManager(_hWnd);
		}
	}

	/**
	 * サウンドのバッファーを開放する
	 */
	inline void ClearBuffer(){ m_pSound.clear(); }
	
	/**
	 * インスタンスの破棄
	 */
	static void Destroy()
	{
		if (m_pSoundManager != NULL)
		{
			delete m_pSoundManager;
			m_pSoundManager = NULL;
		}
	}

	/**
	 * インスタンスを取得する
	 * @return インスタンスが返る
	 */
	static DSoundManager* GetInstance()
	{
		return m_pSoundManager;
	}

private:
	DSoundManager(HWND _hWnd);
	~DSoundManager();
	HWND							  m_hWnd;
	IDirectSound8*					  m_pDSound8;
	std::vector<LPDIRECTSOUNDBUFFER8> m_pSound;
	static DSoundManager*			  m_pSoundManager;
	bool							  OpenWave(TCHAR* _filename, WAVEFORMATEX &_wFmt, char** _pWaveData, DWORD &_waveSize);
};
#endif