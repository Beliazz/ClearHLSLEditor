#include "StdAfx.h"
#include "HLSLDocument.h"

HLSLDocument::HLSLDocument( QString fileName )
{
	m_pFile = QSharedPointer<QFile>(new QFile(fileName));
	int i;
	for (i = fileName.size() - 1; i >= 0; i--)
	{
		if (fileName[i] == '\\' || fileName[i] == '/' )
			break;

		m_docName.push_front(fileName[i]);
	}

	m_dir = fileName.remove(i, fileName.size() - i);
	
	if (m_docName[m_docName.size() - 1] == 'h')
	{
		m_docType = HLSL_HEADER;
	}
	else
	{
		m_docType = HLSL_SOURCE;
	}

}
HLSLDocument::~HLSLDocument(void)
{
	if (m_pFile->isOpen())
	{
		Close();
	}
}

bool HLSLDocument::Open()
{
	if (!m_pFile->open(QIODevice::ReadOnly | QIODevice::Text))
		return false;

	m_text = QString(m_pFile->readAll());

	m_pFile->close();

	return true;
}
void HLSLDocument::Close()
{
	m_pFile->close();
}
bool HLSLDocument::Save( QString path /*= "override"*/ )
{
	if (path != "override")	
	{
		m_pFile->remove();
		m_pFile->setFileName(path);
	}

	if (!m_pFile->open(QIODevice::WriteOnly | QIODevice::Text))
		return false;

	m_pFile->seek(0);
	m_pFile->resize(m_text.toAscii().size());
	m_pFile->write(m_text.toAscii());
	m_pFile->flush();
	m_pFile->close();

	return true;
}
