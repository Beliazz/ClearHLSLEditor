#pragma once

#include "stdafx.h"
#include "SyntaxHighlighter.h"
#include "LineNumberArea.h"
#include "HLSLCompiler.h"

class SyntaxHighlighter;
class CodeEditor : public QPlainTextEdit
{
	Q_OBJECT

private:
	SyntaxHighlighter*	m_pHighlighter;
	QFont m_font;
	QVector<CompilerError> m_currErrors;
	QWidget* m_pLineNumberArea;

private slots:
	void updateLineNumberAreaWidth(int newBlockCount);
	void highlightCurrentLine();
	void updateLineNumberArea(const QRect &, int);

protected:
	void resizeEvent(QResizeEvent *event);

public:
	CodeEditor(QWidget* pParent);
	~CodeEditor(void);

	bool Init(QDomDocument* pConfig);
	bool ParseConfigFile(QDomDocument* pConfig);

	void SetErrors(QVector<CompilerError> errors);
	void SetCursorPos(int line);
	void SetText(QString text);

	// line number area
	void lineNumberAreaPaintEvent(QPaintEvent *event);
	int lineNumberAreaWidth();

	void ResetBlockData();
};

struct TextBlockUserData : public QTextBlockUserData
{
	bool m_hasChanged;
};

