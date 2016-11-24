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

/**
 * サウンドの再生をするクラス
 *
 * ここでサウンドのリソースを管理し実体は一つで良いのでシングルトンクラスにしている
 */
class DSoundManager
{
public:
	/**
	 * サウンドを操作するためのenum
	 */
	enum SOUND_OPERATION
	{
		SOUND_PLAY,		//!< サウンドを再生する
		SOUND_STOP,		//!< サウンドを停止する
		SOUND_LOOP,		//!< サウンドをループ再生する
		SOUND_RESET,	//!< サウンドをリセットする
		SOUND_STOP_RESET//!< サウンドを停止してリセットする
	};

	/**
	 * インスタンス生成関数
	 */
	static void Create()
	{
		if (m_pSoundManager == NULL)
		{
			m_pSoundManager = new DSoundManager();
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

	/**
	 * インスタンスの破棄
	 */
	static void Delete()
	{
		if (m_pSoundManager != NULL)
		{
			delete m_pSoundManager;
			m_pSoundManager = NULL;
		}
	}

	/**
	 * DSoundManagerクラスの初期化関数
	 * @param[in] _hWnd ウィンドウハンドル。コンストラクタ内で使う
	 * @return 成功したらtrue
	 */
	bool Init(HWND _hWnd);

	/**
	 * DSoundManagerクラスの解放関数
	 */
	void Release();

	/**
	 * 音声の読み込み
	 * @param[in] _pFileName 読み込むファイルの名前
	 * @param[out] _pIndex データの格納先のインデックス
	 * @return 成功したらtrue
	 */
	bool LoadSound(LPSTR _pFileName, int* _pIndex);

	/**
	 * 音声の開放
	 * @param[in] _index 開放先のインデックス
	 */
	void ReleaseSound(int _index);

	/**
	 * サウンドの操作関数
	 * @param[in] _index 操作するサウンドの格納先のインデックス
	 * @param[in] _operation どのような操作をするか
	 */
	void SoundOperation(int _index, SOUND_OPERATION _operation);

	/**
	 * サウンドのバッファーを開放する
	 */
	inline void ClearBuffer()
	{
		m_pSound.clear();
	}

private:
	/**
	 * DSoundManagerクラスのコンストラクタ
	 * @param[in] _hWnd 音声を鳴らすウィンドウのハンドル
	 */
	DSoundManager();

	/**
	 * DSoundManagerクラスのデストラクタ
	 */
	~DSoundManager();

	/**
	 * waveファイル内のデータを読み出す関数
	 * @param[in] _pFileName 開くファイルの名前
	 * @param[out] _pWaveFormat 読み込んだwaveファイルのフォーマット
	 * @param[out] _pWaveData 読み込んだwaveファイルのデータ
	 * @param[out] _pWaveSize 読み込んだwaveファイルのサイズ
	 */
	bool ReadWave(LPSTR _pFileName, WAVEFORMATEX* _pWaveFormat, BYTE** _pWaveData, DWORD* _pWaveSize);

	IDirectSound8*					  m_pDSound8;
	HWND							  m_hWnd;
	std::vector<LPDIRECTSOUNDBUFFER8> m_pSound;
	static DSoundManager*			  m_pSoundManager;

};


#endif
