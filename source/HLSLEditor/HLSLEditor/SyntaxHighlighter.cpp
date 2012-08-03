#include "SyntaxHighlighter.h"

SyntaxHighlighter::SyntaxHighlighter( CodeEditor *parent, QDomNode& node)
	: QSyntaxHighlighter(parent->document()), m_pEditor(parent)
{
	// string list that holds the key words
	QStringList keys;

	// get first child
	QDomNode temp = node.lastChild();

	//////////////////////////////////////////////////////////////////////////
	// get key words
	while(!temp.isNull())
	{
		// get children
		QDomNodeList children = temp.childNodes();

		// get attributes
		QDomNamedNodeMap attributes = temp.toElement().attributes();

		// extract data
		for (int i = 0; i < children.length(); i++)
		{
			QString keyword = attributes.namedItem("StartTag").nodeValue() + 
								children.at(i).toElement().text() +
								attributes.namedItem("EndTag").nodeValue();

			keys.append(keyword);
		}	
			
		// rule 
		HighlightingRule rule;
		rule.format.setForeground(QColor(attributes.namedItem("Color").nodeValue()));
		rule.format.setFontItalic(attributes.namedItem("Italic").nodeValue().toInt());
		rule.format.setFontWeight(attributes.namedItem("Bold").nodeValue().toInt());

		// add to rule set
		foreach (const QString &pattern, keys)
		{			
			rule.pattern = QRegExp(pattern);
			highlightingRules.append(rule);
		}

		// clear keys
		keys.clear();

		// next
		temp = temp.previousSibling();
	}

	// functions
// 	HighlightingRule rule;
// 	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
// 	rule.format.setForeground(Qt::blue);
// 	rule.format.setFontItalic(true);
// 	highlightingRules.append(rule);
	
	// comments
	QDomNamedNodeMap commentNodeAttr = node.toElement().elementsByTagName("MultilineComment").at(0).attributes();
	multiLineCommentFormat.setForeground(QColor(commentNodeAttr.namedItem("Color").nodeValue()));
	commentStartExpression = QRegExp(commentNodeAttr.namedItem("StartTag").nodeValue());
	commentEndExpression = QRegExp(commentNodeAttr.namedItem("EndTag").nodeValue());
	m_currLineFormat.setBackground(QColor("AliceBlue"));
}

void SyntaxHighlighter::highlightBlock( const QString &text )
{
	TextBlockUserData* pData = (TextBlockUserData*)currentBlockUserData();
	if (pData != NULL)
	{
		pData->m_hasChanged = true;
	}
	else
	{
		pData = new TextBlockUserData();
		pData->m_hasChanged = true;
		setCurrentBlockUserData(pData); 
	}

	foreach (const HighlightingRule &rule, highlightingRules) {
		QRegExp expression(rule.pattern);
		int index = expression.indexIn(text);
		while (index >= 0) {
			int length = expression.matchedLength();
			setFormat(index, length, rule.format);
			index = expression.indexIn(text, index + length);
		}
	}

	setCurrentBlockState(0);

	int startIndex = 0;
	if (previousBlockState() != 1)
		startIndex = commentStartExpression.indexIn(text);

	while (startIndex >= 0) {
		int endIndex = commentEndExpression.indexIn(text, startIndex);
		int commentLength;
		if (endIndex == -1) {
			setCurrentBlockState(1);
			commentLength = text.length() - startIndex;
		} else {
			commentLength = endIndex - startIndex
				+ commentEndExpression.matchedLength();
		}

		setFormat(startIndex, commentLength, multiLineCommentFormat);
		startIndex = commentStartExpression.indexIn(text, startIndex + commentLength);
	}
}

void SyntaxHighlighter::HighlightErrors( QVector<CompilerError> errors )
{
	m_extraSelections.clear();
	for (int i = 0; i < errors.size(); i++)
	{
		// highlight
		QTextEdit::ExtraSelection selection;
		QColor lineColor;
		if (errors[i].type == OUTPUT_TYPE_WARNING)
		{
			lineColor = QColor(Qt::yellow).lighter(170);
			lineColor.setAlpha(180);
		}
		else
		{
			lineColor = QColor(Qt::red).lighter(170);
			lineColor.setAlpha(150);
		}

		selection.format.setBackground(lineColor);
		selection.format.setProperty(QTextFormat::FullWidthSelection, true);
		selection.cursor = m_pEditor->textCursor();
		selection.cursor.clearSelection();
		selection.cursor.setPosition(0);
		selection.cursor.movePosition(QTextCursor::Down, QTextCursor::MoveAnchor, errors[i].location.x() - 1 );
		m_extraSelections.append(selection);
	}

	m_pEditor->setExtraSelections(m_extraSelections);
}

void SyntaxHighlighter::HighlightCurrLine( ) 
{
	QList<QTextEdit::ExtraSelection> selections(m_extraSelections);

	QTextEdit::ExtraSelection markingSelection;
	QTextEdit::ExtraSelection currLineSelection;
	
	markingSelection.cursor = m_pEditor->textCursor();
	
	currLineSelection.format = m_currLineFormat;
	currLineSelection.format.setProperty(QTextFormat::FullWidthSelection, true);
	currLineSelection.cursor = m_pEditor->textCursor();
	currLineSelection.cursor.clearSelection();

	selections.push_back(currLineSelection);
	selections.push_back(markingSelection);

	m_pEditor->setExtraSelections(selections);
}

