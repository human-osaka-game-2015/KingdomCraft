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
		m_pDSound8->Release();
		return false;
	}
	return true;
}

void DSoundManager::Release()
{
	m_pDSound8->Release();
}

void DSoundManager::SoundOperation(int _index, SOUND_OPERATION _operation)
{
	switch (_operation)
	{
	case SOUND_PLAY:
		m_pSound[_index]->Play(0, 0, 0);
		break;
	case SOUND_LOOP:
		m_pSound[_index]->Play(0, 0, DSBPLAY_LOOPING);
		break;
	case SOUND_STOP:
		m_pSound[_index]->Stop();
		break;
	case SOUND_RESET:
		m_pSound[_index]->SetCurrentPosition(0);
		break;
	case SOUND_STOP_RESET:
		m_pSound[_index]->Stop();
		m_pSound[_index]->SetCurrentPosition(0);
		break;
	}
}

bool DSoundManager::LoadSound(LPSTR _pFileName, int* _pIndex)
{
	WAVEFORMATEX WaveFormat;
	BYTE* pWaveData = 0;
	DWORD WaveSize = 0;

	if (!ReadWave(_pFileName, &WaveFormat, &pWaveData, &WaveSize))
	{
		MessageBox(m_hWnd, TEXT("waveファイルが開けませんでした"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	DSBUFFERDESC DSBufferDesc;
	DSBufferDesc.dwSize = sizeof(DSBUFFERDESC);
	DSBufferDesc.dwFlags = 0;
	DSBufferDesc.dwBufferBytes = WaveSize;
	DSBufferDesc.dwReserved = 0;
	DSBufferDesc.lpwfxFormat = &WaveFormat;
	DSBufferDesc.guid3DAlgorithm = GUID_NULL;

	LPDIRECTSOUNDBUFFER8 pDSBuffer = NULL;
	LPDIRECTSOUNDBUFFER pTmpBuf = NULL;
	m_pDSound8->CreateSoundBuffer(&DSBufferDesc, &pTmpBuf, NULL);
	pTmpBuf->QueryInterface(IID_IDirectSoundBuffer8, reinterpret_cast<void**>(&pDSBuffer));
	pTmpBuf->Release();

	if (pDSBuffer == NULL)
	{
		m_pDSound8->Release();
		MessageBox(m_hWnd, TEXT("サウンドバッファ作成に失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	LPVOID pWriteData = 0;
	DWORD WriteDataLength = 0;
	if (FAILED(pDSBuffer->Lock(0, 0, &pWriteData, &WriteDataLength, NULL, NULL, DSBLOCK_ENTIREBUFFER)))
	{
		m_pDSound8->Release();
		delete[] pWaveData;
		MessageBox(m_hWnd, TEXT("サウンドバッファのロックに失敗しました"), TEXT("エラー"), MB_ICONSTOP);
		return false;
	}

	memcpy(pWriteData, pWaveData, WriteDataLength);
	pDSBuffer->Unlock(pWriteData, WriteDataLength, NULL, 0);
	delete[] pWaveData;

	*_pIndex = m_pSound.size();
	m_pSound.push_back(pDSBuffer);

	return true;
}

void DSoundManager::ReleaseSound(int _index)
{
	if (m_pSound[_index] != NULL)
	{
		m_pSound[_index]->Release();
		m_pSound[_index] = NULL;
	}
}

bool DSoundManager::ReadWave(LPSTR _pFileName, WAVEFORMATEX* _pWaveFormat, BYTE** _pWaveData, DWORD* _pWaveSize)
{
	if (_pFileName == NULL)
	{
		return false;
	}

	HMMIO hMmio = NULL;
	MMIOINFO MmioInfo;
	ZeroMemory(&MmioInfo, sizeof(MMIOINFO));
	hMmio = mmioOpen(_pFileName, &MmioInfo, MMIO_READ);
	if (!hMmio)
	{
		return false;
	}

	// RIFFチャンク検索
	MMRESULT Result;
	MMCKINFO RiffChunk;
	RiffChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	Result = mmioDescend(hMmio, &RiffChunk, NULL, MMIO_FINDRIFF);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	// fmtチャンク検索
	MMCKINFO FormatChunk;
	FormatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	Result = mmioDescend(hMmio, &FormatChunk, &RiffChunk, MMIO_FINDCHUNK);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	DWORD FormatSize = FormatChunk.cksize;
	DWORD WaveDataSize = mmioRead(hMmio, reinterpret_cast<HPSTR>(_pWaveFormat), FormatSize);
	if (WaveDataSize != FormatSize)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	mmioAscend(hMmio, &FormatChunk, 0);

	// dataチャンク検索
	MMCKINFO DataChunk;
	DataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	Result = mmioDescend(hMmio, &DataChunk, &RiffChunk, MMIO_FINDCHUNK);
	if (Result != MMSYSERR_NOERROR)
	{
		mmioClose(hMmio, 0);
		return false;
	}

	*_pWaveData = new BYTE[DataChunk.cksize];
	WaveDataSize = mmioRead(hMmio, reinterpret_cast<HPSTR>(*_pWaveData), DataChunk.cksize);
	if (WaveDataSize != DataChunk.cksize)
	{
		delete[] * _pWaveData;
		mmioClose(hMmio, 0);
		return false;
	}

	*_pWaveSize = WaveDataSize;
	mmioClose(hMmio, 0);

	return true;
}
