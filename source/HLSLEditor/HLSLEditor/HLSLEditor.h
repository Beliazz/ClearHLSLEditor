#ifndef HLSLEDITOR_H
#define HLSLEDITOR_H

// generated files
#include "ui_hlsleditor.h"

#include "stdafx.h"
#include "SyntaxHighlighter.h"
#include "HLSLDocument.h"
#include "HLSLCompiler.h"
#include "LineNumberArea.h"

//#define TEST

class D3D11GraphicsView;

class HLSLEditor : public QMainWindow
{
	Q_OBJECT

public:
	HLSLEditor(QWidget *parent = 0, Qt::WFlags flags = 0);
	~HLSLEditor();

	bool Init();
	bool InitGraphics();
	bool ReparseConfig();

private:
	Ui::HLSLEditorClass ui;
		
	// compiling
	bool						m_isOtfc;
	QTimer						m_timCheckAsyncCompiler;
	QTimer						m_compileTimout;
	ThreadSafe<AsyncCompiler>	m_pAsyncCompiler;

	QMap<QString, HLSLDocument*> 		m_docs;
	HLSLDocument*						m_pCurrDoc;
	cgl::PCGLManager					m_pCGLMgr;
	bool								m_loading;
	QString								m_localDirectory;

public slots:
	void Compile_EvtHandler();
	void Save_EvtHandler();
	void Open_EvtHandler();
	void TextChanged_EvtHandler();
	void ErrorClicked_EvtHandler();
	void ReparseConfig_EvtHandler();
	void CheckAsynCompiler_EvtHandler();
	void CheckCompileTimout_EvtHandler();
	void ActiveDocumentChanged_EvtHandler(const QString);
};

class D3D11GraphicsView : public QGraphicsView
{
	Q_OBJECT

public:
	virtual QPaintEngine* paintEngine( ) const
	{
		return NULL;
	}
};

#endif // HLSLEDITOR_H
