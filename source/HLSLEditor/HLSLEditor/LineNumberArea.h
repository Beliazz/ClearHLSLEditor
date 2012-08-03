#pragma once

#include "stdafx.h"
#include "CodeEditor.h"

class CodeEditor;
class LineNumberArea : public QWidget
{
public:
	LineNumberArea(CodeEditor *editor);

	QSize sizeHint() const;

protected:
	void paintEvent(QPaintEvent *event);

private:
	CodeEditor* m_pCodeEditor;
};
