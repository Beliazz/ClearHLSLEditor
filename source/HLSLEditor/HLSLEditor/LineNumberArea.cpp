#include "LineNumberArea.h"

LineNumberArea::LineNumberArea( CodeEditor *editor ) : QWidget(editor)
{
	m_pCodeEditor = editor;
}

QSize LineNumberArea::sizeHint() const
{
	return QSize(m_pCodeEditor->lineNumberAreaWidth(), 0);
}

void LineNumberArea::paintEvent( QPaintEvent *event )
{
	m_pCodeEditor->lineNumberAreaPaintEvent(event);
}
