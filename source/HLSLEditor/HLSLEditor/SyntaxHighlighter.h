#ifndef SyntaxHighlighter_h__
#define SyntaxHighlighter_h__

#include "stdafx.h"
#include "HLSLCompiler.h"
#include "CodeEditor.h"

class CodeEditor;
class SyntaxHighlighter : public QSyntaxHighlighter
{
	Q_OBJECT

private:
	struct HighlightingRule
	{
		QRegExp pattern;
		QTextCharFormat format;
	};
	QVector<HighlightingRule> highlightingRules;

	QRegExp commentStartExpression;
	QRegExp commentEndExpression;

	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;

	CodeEditor* m_pEditor;
	QList<QTextEdit::ExtraSelection> m_extraSelections;
	QTextEdit::ExtraSelection m_currLine;
	
	QTextCharFormat m_warningFormat;
	QTextCharFormat m_errorFormat;
	QTextCharFormat m_currLineFormat;

protected:
	void highlightBlock(const QString &text);

public:
	SyntaxHighlighter(CodeEditor *parent, QDomNode& node );
	void HighlightErrors(QVector<CompilerError> errors);
	void HighlightCurrLine();

};

#endif // SyntaxHighlighter_h__