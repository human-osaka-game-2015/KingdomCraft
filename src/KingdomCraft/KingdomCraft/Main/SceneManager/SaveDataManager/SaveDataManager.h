/**
 * @file   SaveDataManager.h
 * @brief  SaveDataManagerクラスのヘッダファイル
 * @author kotani
 */
#ifndef SAVEDATAMANAGER_H
#define SAVEDATAMANAGER_H

#include <windows.h>
#include <string>
#include <vector>

/**
 * セーブデータの作成と読み込みをしてくれるクラス
 */
class SaveDataManager
{
public:
	/**
	 * インスタンス生成関数
	 */
	inline static void Create()
	{
		if (m_pSaveDataManager == NULL)
		{
			m_pSaveDataManager = new SaveDataManager();
		}
	}

	/**
	 * インスタンスを取得する
	 * @return インスタンスが返る
	 */
	inline static SaveDataManager* GetInstance()
	{
		return m_pSaveDataManager;
	}

	/**
	 * インスタンスの破棄
	 */
	inline static void Delete()
	{
		delete m_pSaveDataManager;
	}

	/**
	 * ファイル読み込み
	 * @param[in] _pFileName 読み込むセーブデータのファイルパス
	 */
	void FileLoad(LPCTSTR _pFileName);

	/**
	 * ファイルセーブ
	 * @param[in] _pFileName セーブするファイルの名前
	 */
	void FileSave(LPCTSTR _pFileName);

	/**
	 * グループ名を指定してその中にデータを書き込む
	 * @param[in] _pGroupName 書き込みたいデータの名前
	 * @param[in] _pData 書き込みたいデータ
	 */
	void WriteData(LPCTSTR _pGroupName, std::vector<int>* _pData);

	/**
	 * グループ名を指定してその中にデータを書き込む
	 * @param[in] _pGroupName 書き込みたいデータの名前
	 * @param[in] _pData 書き込みたいデータ
	 */
	void WriteData(LPCTSTR _pGroupName, std::vector<float>* _pData);

	/**
	 * グループ名を指定してその中にデータを書き込む
	 * @param[in] _pGroupName 書き込みたいデータの名前
	 * @param[in] _pData 書き込みたいデータ
	 */
	void WriteData(LPCTSTR _pGroupName, std::vector<std::string>* _pData);

	/**
	 * グループ名を指定してその中からデータを読み込む
	 * @param[in] _pGroupName 読み込みたいデータの名前
	 * @param[out] _pData 読み込みたいデータ
	 * @return グループが存在すればtrue無ければfalse
	 */
	bool ReadData(LPCTSTR _pGroupName, std::vector<int>* _pData);

	/**
	 * グループ名を指定してその中からデータを読み込む
	 * @param[in] _pGroupName 読み込みたいデータの名前
	 * @param[out] _pData 読み込みたいデータ
	 * @return グループが存在すればtrue無ければfalse
	 */
	bool ReadData(LPCTSTR _pGroupName, std::vector<float>* _pData);

	/**
	 * グループ名を指定してその中からデータを読み込む
	 * @param[in] _pGroupName 読み込みたいデータの名前
	 * @param[out] _pData 読み込みたいデータ
	 * @return グループが存在すればtrue無ければfalse
	 */
	bool ReadData(LPCTSTR _pGroupName, std::vector<std::string>* _pData);

private:
	/**
	 * SaveDataManagerクラスのコンストラクタ
	 */
	SaveDataManager();

	/**
	 * SaveDataManagerクラスのデストラクタ
	 */
	~SaveDataManager();

	/**
	 * 読み込みバッファの開放
	 */
	void ReleaseLoadBuffer();

	/**
	 * 書き込みバッファの開放
	 */
	void ReleaseWriteBuffer();

	static SaveDataManager* m_pSaveDataManager;

	FILE*		m_pFile;
	std::string m_StrBuffer;//!<書き込み用バッファ
	TCHAR*		m_pBuffer; //!<読み込んだ時の文字列が入っている
	TCHAR*		m_pTmpBuffer;//!<一時保存用バッファ
	long		m_FileSize;

};


#endif
