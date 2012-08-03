#include "stdafx.h"
#include "hlsleditor.h"
#include "SyntaxHighlighter.h"
#include <QtGui/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HLSLEditor editor;

	if (!editor.Init())
	{
		return -1;
	}
	
	editor.show();
	return a.exec();
}
