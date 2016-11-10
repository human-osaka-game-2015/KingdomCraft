/**
 * @file   DSoundManager.cpp
 * @brief  DSoundManagerクラスのcppファイル
 * @author kotani
 */
#include "DSoundManager.h"
#include <mmsystem.h>

DSoundManager* DSoundManager::m_pSoundManager = NULL;

DSoundManager::DSoundManager(HWND _hWnd) :
m_hWnd(_hWnd)
{
}

DSoundManager::~DSoundManager()
{
}

bool DSoundManager::Init()
{
	if (FAILED(DirectSoundCreate8(NULL, &m_pDSound8, NULL)))
	{
		MessageBox(m_hWnd, TEXT("サウンドデバイスの生成に失敗しました"), TEXT("Error"), MB_ICONSTOP);
		return false;
	}

	if (FAILED(m_pDSound8->SetCooperativeLevel(m_hWnd, DSSCL_PRIORITY)))
	{
		MessageBox(m_hWnd, TEXT("協調レベルの設定に失敗しました"), TEXT("Error"), MB_ICONSTOP);
		return false;
	}
	return true;
}

bool DSoundManager::OpenWave(TCHAR* _filename, WAVEFORMATEX &_wFmt, char** _pWaveData, DWORD &_waveSize)
{
	if (_filename == NULL)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO mmioInfo;

	ZeroMemory(&mmioInfo, sizeof(MMIOINFO));
	hMmio = mmioOpen(_filename, &mmioInfo, MMIO_READ);
	if (!hMmio)
	{
		return false;
	}


	// RIFFチャンク検索
	MMRESULT mmRes;
	MMCKINFO riffChunk;
	riffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmRes = mmioDescend(hMmio, &riffChunk, NULL, MMIO_FINDRIFF);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}


	// フォーマットチャンク検索
	MMCKINFO formatChunk;
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmRes = mmioDescend(hMmio, &formatChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}


	DWORD fmsize = formatChunk.cksize;
	DWORD size = mmioRead(hMmio, (HPSTR)&_wFmt, fmsize);
	if (size != fmsize)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &formatChunk, 0);


	// データチャンク検索
	MMCKINFO dataChunk;
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmRes = mmioDescend(hMmio, &dataChunk, &riffChunk, MMIO_FINDCHUNK);
	if (mmRes != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	*_pWaveData = new char[dataChunk.cksize];
	size = mmioRead(hMmio, (HPSTR)*_pWaveData, dataChunk.cksize);
	if (size != dataChunk.cksize)
	{
		delete[] * _pWaveData;
		return false;
	}

	_waveSize = size;

	mmioClose(hMmio, 0);

	return true;
}

void DSoundManager::SoundOperation(int _key, SOUND_OPERATION _operation)
{
	switch (_operation)
	{
	case SOUND_PLAY:
		m_pSound[_key]->Play(0, 0, 0);
		break;
	case SOUND_LOOP:
		m_pSound[_key]->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case SOUND_STOP:
		m_pSound[_key]->Stop();
		break;
	case SOUND_RESET:
		m_pSound[_key]->SetCurrentPosition(0);
		break;
	case SOUND_STOP_RESET:
		m_pSound[_key]->Stop();
		m_pSound[_key]->SetCurrentPosition(0);
		break;
	}
}

bool DSoundManager::LoadSound(char* _filename, int* _pKey)
{
	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
	WAVEFORMATEX wFmt;
	char *pWaveData = 0;
	DWORD waveSize = 0;

	if (!OpenWave(_filename, wFmt, &pWaveData, waveSize))
	{
		MessageBox(m_hWnd, TEXT("waveファイルが開けませんでした"), TEXT("Error"), MB_ICONSTOP);
		return false;
	}

	DSBUFFERDESC DSBufferDesc;
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = 0;
	DSBufferDesc.dwBufferBytes = waveSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &wFmt;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;

	IDirectSoundBuffer *ptmpBuf = 0;
	m_pDSound8->CreateSoundBuffer(&DSBufferDesc, &ptmpBuf, NULL);
	ptmpBuf->QueryInterface(IID_IDirectSoundBuffer8, (void**)&pDSBuffer);

	ptmpBuf->Release();
	if (pDSBuffer == NULL)
	{
		m_pDSound8->Release();
		return false;
	}


	// セカンダリバッファにWaveデータ書き込み
	//音声データ
	LPVOID lpvWrite = 0;
	//音声データの大きさ
	DWORD dwLength = 0;
	if (DS_OK == pDSBuffer->Lock(0, 0, &lpvWrite, &dwLength, NULL, NULL, DSBLOCK_ENTIREBUFFER))
	{
		memcpy(lpvWrite, pWaveData, dwLength);
		pDSBuffer->Unlock(lpvWrite, dwLength, NULL, 0);
	}

	delete[] pWaveData;

	*_pKey = m_pSound.size();
	m_pSound.push_back(pDSBuffer);

	return true;
}