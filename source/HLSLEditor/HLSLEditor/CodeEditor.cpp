#include "StdAfx.h"
#include "CodeEditor.h"

CodeEditor::CodeEditor(QWidget* pParent) : QPlainTextEdit(pParent)
{
	m_pLineNumberArea = new LineNumberArea(this);

	QObject::connect(this, SIGNAL(blockCountChanged(int)), this, SLOT(updateLineNumberAreaWidth(int)));
	QObject::connect(this, SIGNAL(updateRequest(QRect,int)), this, SLOT(updateLineNumberArea(QRect,int)));

	updateLineNumberAreaWidth(0);
}

bool CodeEditor::Init(QDomDocument* pConfig)
{
	ParseConfigFile(pConfig);
	
	SetCursorPos(0);

	return true;
}
bool CodeEditor::ParseConfigFile( QDomDocument* pConfig )
{
	//////////////////////////////////////////////////////////////////////////
	// create syntax highlighter
	QDomNode node = pConfig->documentElement().elementsByTagName("Editor").at(0).toElement().elementsByTagName("HLSL").at(0);
	m_pHighlighter = new SyntaxHighlighter(this, node);
	QObject::connect(this, SIGNAL(cursorPositionChanged()), this, SLOT(highlightCurrentLine()));
	highlightCurrentLine();

	//////////////////////////////////////////////////////////////////////////
	// set text edit props
	//
	// font
	QDomNode fontNode = pConfig->elementsByTagName("Editor").at(0).toElement().elementsByTagName("Font").at(0);
	m_font = QFont(fontNode.attributes().namedItem("Family").nodeValue(), fontNode.attributes().namedItem("Size").nodeValue().toInt());
	//setFont(m_font);

	//
	// tab stop width
	QDomNode tabStopNode = pConfig->elementsByTagName("Editor").at(0).toElement().elementsByTagName("TabStop").at(0);
	int tabStopWidth = tabStopNode.attributes().namedItem("Width").nodeValue().toInt();
	if (tabStopWidth == 0) { tabStopWidth = 24; }

	setTabStopWidth(tabStopWidth);

	return true;
}

CodeEditor::~CodeEditor(void)
{
	SAFE_DELETE(m_pHighlighter);
	SAFE_DELETE(m_pLineNumberArea);
}

void CodeEditor::SetErrors( QVector<CompilerError> errors )
{
	m_currErrors = errors;
	m_pHighlighter->HighlightErrors(errors);
	m_pHighlighter->HighlightCurrLine();
}
void CodeEditor::SetCursorPos( int line )
{
	QTextCursor cursor = textCursor();
	cursor.setPosition(0);
	cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, line - 1 );
	setTextCursor(cursor);

	ensureCursorVisible();
}
void CodeEditor::ResetBlockData()
{
	QTextBlock block;
	QTextCursor cursor = textCursor();
	cursor.setPosition(0);
	block = cursor.block();

	while(block.isValid())
	{
		TextBlockUserData* pData = new TextBlockUserData();
		pData->m_hasChanged = false;
		block.setUserData(pData);

		block = block.next();
	}
}
void CodeEditor::SetText( QString text )
{
	setPlainText(text);
	SetCursorPos(0);
}

//////////////////////////////////////////////////////////////////////////
// line number area
int CodeEditor::lineNumberAreaWidth()
{
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 20 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

void CodeEditor::updateLineNumberAreaWidth(int /* newBlockCount */)
{
	setViewportMargins(lineNumberAreaWidth() + 5,0 ,0 ,0);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{
	if (dy)
		m_pLineNumberArea->scroll(0, dy);
	else
		m_pLineNumberArea->update(0, rect.y(), m_pLineNumberArea->width(), rect.height());

	if (rect.contains(viewport()->rect()))
		updateLineNumberAreaWidth(0);
}

void CodeEditor::resizeEvent(QResizeEvent *e)
{
	QPlainTextEdit::resizeEvent(e);

	QRect cr = contentsRect();
	m_pLineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

void CodeEditor::highlightCurrentLine()
{
	m_pHighlighter->HighlightCurrLine();
}

void CodeEditor::lineNumberAreaPaintEvent(QPaintEvent *event)
{
	QPainter painter(m_pLineNumberArea);
	painter.fillRect(event->rect(), QColor("#FAFAFA"));
 
	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int) blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int) blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.setFont(font());
			painter.drawText(0, top, m_pLineNumberArea->width() - 12, fontMetrics().height(),
				Qt::AlignRight, number);

			if(((TextBlockUserData*)block.userData())->m_hasChanged)
			{
				painter.fillRect(m_pLineNumberArea->width() - 5, top, 5, fontMetrics().height(), QColor("Gold").lighter(150));
			}
			else
			{
				painter.fillRect(m_pLineNumberArea->width() - 5, top, 5, fontMetrics().height(), QColor("LimeGreen"));
			}
		}

		block = block.next();
		top = bottom;
		bottom = top + (int) blockBoundingRect(block).height();
		++blockNumber;
	}
}






