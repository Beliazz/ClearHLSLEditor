#include "StdAfx.h"
#include "IncludeHandler.h"

using namespace std;

IncludeHandler::IncludeHandler(void)
{
	m_pHeaderData = NULL;
}
IncludeHandler::~IncludeHandler(void)
{
	for (QMap<QString, HEADER_DATA>::iterator it = m_headerMap.begin();
		it != m_headerMap.end(); it++)
	{
		free((*it).pData);
	}

	m_headerMap.clear();
}

STDMETHODIMP IncludeHandler::Open( THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes )
{
	if (pFileName == NULL || pFileName == "")
		return E_FAIL;

	QString providedFilename(pFileName);
	bool found = false;
	QString filename = "";
	DWORD  fileAttr;
	switch(IncludeType)
	{
	case D3D_INCLUDE_LOCAL:
		{
			filename = m_localDirectory + QString("\\") + QString(pFileName);

			wchar_t* buff = new wchar_t[filename.size() + 1];
			int whereToInsertNull = filename.toWCharArray(buff);
			buff[whereToInsertNull] = L'\0';

			fileAttr = GetFileAttributes(buff);

			SAFE_DELETE_ARRAY(buff);

			if (0xFFFFFFFF == fileAttr)
			{
				found = false;
			}
			else
			{
				found = true;
			}


		} break;
	case D3D_INCLUDE_SYSTEM:
		{
			if (m_directories.empty())
				return E_FAIL;

			for (int i = 0; i < m_directories.size(); i++)
			{
				DWORD  fileAttr;
				QString filename = m_localDirectory[i] + "\\" + providedFilename;

				wchar_t* buff = new wchar_t[filename.size() + 1];
				int whereToInsertNull = filename.toWCharArray(buff);
				buff[whereToInsertNull] = L'\0';

				fileAttr = GetFileAttributes(buff);

				SAFE_DELETE_ARRAY(buff);

				if (0xFFFFFFFF == fileAttr)
					continue;

				found = true;
				
				break;
			}

		} break;
	}

	if (!found)
		return E_FAIL;

	// first check if this file has already been loaded
	QString docName;
	for (int i = providedFilename.size() - 1; i >= 0; i--)
	{
		if (providedFilename[i] == '\\' || providedFilename[i] == '/' )
			break;

		docName.push_front(pFileName[i]);
	}

	QMap<QString, HEADER_DATA>::iterator it = m_headerMap.find(docName.toLower());
	if (it != m_headerMap.end())
	{
		(*pBytes) = (*it).size;
		(*ppData) = new char[*pBytes];
		memcpy((void*)(*ppData), it->pData, it->size);

		FILE* pFile = fopen(docName.toLower().toAscii().data(), "w");
		fwrite(*ppData, 1, *pBytes, pFile);
		fclose(pFile);

		return S_OK;
	}

	// load file
	wchar_t* buff = new wchar_t[filename.size() + 1];
	int whereToInsertNull = filename.toWCharArray(buff);
	buff[whereToInsertNull] = L'\0';

	m_currFile.open(buff, ios::in|ios::binary|ios::ate);
	if (m_currFile.is_open())
	{
		(*pBytes) = (int)m_currFile.tellg();
		(*ppData) = new char[*pBytes];
		m_currFile.seekg(0, std::ios_base::beg);
		m_currFile.read((char*)*ppData, *pBytes);
		m_currFile.close();

		SAFE_DELETE_ARRAY(buff);

		return S_OK;
	}

	SAFE_DELETE_ARRAY(buff);

	return E_FAIL;
}
STDMETHODIMP IncludeHandler::Close( THIS_ LPCVOID pData )
{
	SAFE_DELETE_ARRAY(pData);
	return S_OK;
}

void IncludeHandler::AddHeaderData( const QString& filename, const HEADER_DATA& data )
{
	QMap<QString, HEADER_DATA>::iterator it = m_headerMap.find(filename.toLower());
	if (it != m_headerMap.end())
	{
		free((*it).pData);
		(*it).pData = (char*)malloc(data.size);
		memcpy((*it).pData, data.pData, data.size);
	}
	else
	{
		HEADER_DATA entryData;
		entryData.pData = (char*)malloc(data.size);
		entryData.size = data.size;
		memcpy(entryData.pData, data.pData, data.size);
		m_headerMap.insert(filename.toLower(), entryData);
	}
}
void IncludeHandler::RemoveHeaderData( const QString& filename )
{
	QMap<QString, HEADER_DATA>::iterator it = m_headerMap.find(filename.toLower());
	if (it != m_headerMap.end())
	{
		free((*it).pData);
	}

	m_headerMap.remove(filename.toLower());
}
