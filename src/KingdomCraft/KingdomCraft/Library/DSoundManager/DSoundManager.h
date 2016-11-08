/**
 * @file   DSoundManager.h
 * @brief  DSoundManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef DXSOUNDMANAGER_H
#define DXSOUNDMANAGER_H
#include <windows.h>
#include <dsound.h>
#include <map>

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
	void Release(){ m_pDSound8->Release(); };

	/**
	 * 音声の読み込み
	 * @param[in] _key 格納先のキー
	 * @param[in] _filename 読み込むファイルの名前
	 * @return 成功したらtrue
	 */
	bool SoundLoad(int _key, char* _filename);
	
	/**
	 * 音声の開放
	 * @param[in] _key 開放先のキー
	 */
	void ReleaseSound(int _key);

	/**
	 * サウンドの操作関数
	 * @param[in] _key 操作するサウンドの格納先のキー
	 * @param[in] operation どのような操作をするか
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
	 * @return インスタンスが返る
	 */
	static DSoundManager* GetInstance()
	{
		return m_pSoundManager;
	}

private:
	DSoundManager(HWND _hWnd);
	~DSoundManager();
	HWND								m_hWnd;
	IDirectSound8*						m_pDSound8;
	std::map<int, LPDIRECTSOUNDBUFFER8> m_SoundMap;
	static DSoundManager*				m_pSoundManager;
	bool								OpenWave(TCHAR* _filename, WAVEFORMATEX &_wFmt, char** _pWaveData, DWORD &_waveSize);
};
#endif