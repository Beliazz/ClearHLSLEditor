#pragma once

#include "stdafx.h"
#include <fstream>
#include <iostream>
#include <string>

struct HEADER_DATA
{
	int size;
	char* pData;
};

class IncludeHandler : public ID3DInclude
{
private:
	std::ifstream m_currFile;
	QVector<QString> m_directories;
	QString m_localDirectory;
	QMap<QString, HEADER_DATA> m_headerMap;
	BYTE* m_pHeaderData;

public:
	IncludeHandler(void);
	~IncludeHandler(void);

	virtual STDMETHODIMP Open( THIS_ D3D_INCLUDE_TYPE IncludeType, LPCSTR pFileName, LPCVOID pParentData, LPCVOID *ppData, UINT *pBytes );
	virtual STDMETHODIMP Close( THIS_ LPCVOID pData );

	inline QVector<QString> GetDirectories()					{ return m_directories; }
	inline void SetDirectories(QVector<QString> directories)	{ m_directories = directories; }

	inline QString GetLocalDirectory()							{ return m_localDirectory; }
	inline void SetLocalDirectory(QString directory)			{ m_localDirectory = directory;}
	
	void AddHeaderData(const QString& filename, const HEADER_DATA& data);
	void RemoveHeaderData(const QString& filename);

};

