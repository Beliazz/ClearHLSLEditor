#include "stdafx.h"
#include "SyntaxHighlighter.h"

enum HLSLDocumentType
{
	HLSL_HEADER,
	HLSL_SOURCE
};

class HLSLDocument
{
private:
	QVector<HLSLDocument*>	m_dependencies;
	QSharedPointer<QFile>	m_pFile;
	QString					m_text;
	QString					m_docName;
	QString					m_dir;

	QString m_fileName;
	HLSLDocumentType m_docType;
	bool m_saved;

public:
	HLSLDocument(QString fileName);
	~HLSLDocument(void);

	bool Open();
	void Close();
	bool Save(QString path = "override");

	inline QString GetName()			{ return m_docName; }
	inline HLSLDocumentType GetType()	{ return m_docType; }
	inline QString GetDirectory()		{ return m_dir; }
	inline QString GetText()			{ return m_text; }
	inline void SetText(QString text)	{ m_text = text; }
};


