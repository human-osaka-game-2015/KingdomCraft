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

class DSoundManager
{
public:
	/**
	* 音声の読み込み
	* @param[in] _filename 読み込むファイルの名前
	* @param[in] _Key 格納先のキー
	*/
	int SoundLoad(int _Key, char* _filename);
	
	/**
	* 音声の開放
	* @param[in] _Key 開放先のキー
	*/
	void ReleaseSound(int _Key);

	/**
	* サウンドの操作関数
	* @param[in] _Key 操作するサウンドの格納先のキー
	* @param[in] operation どのような操作をするか
	*/
	void SoundOperation(int _Key, SOUND_OPERATION _operation);

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

	static void Destroy()
	{
		if (m_pSoundManager != NULL)
		{
			delete m_pSoundManager;
			m_pSoundManager = NULL;
		}
	}

	/**
	* インスタンス取得関数
	*/
	static DSoundManager* getInstance()
	{
		return m_pSoundManager;
	}

private:
	DSoundManager(HWND _hWnd);
	~DSoundManager();

	IDirectSound8*						m_pDSound8;
	std::map<int, LPDIRECTSOUNDBUFFER8> m_SoundMap;
	static DSoundManager*				m_pSoundManager;
	bool								OpenWave(TCHAR* _filename, WAVEFORMATEX &_wFmt, char** _pWaveData, DWORD &_waveSize);
};
#endif