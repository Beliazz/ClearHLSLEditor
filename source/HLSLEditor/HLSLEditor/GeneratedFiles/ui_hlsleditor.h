/********************************************************************************
** Form generated from reading UI file 'hlsleditor.ui'
**
** Created: Sun 5. Aug 21:05:49 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HLSLEDITOR_H
#define UI_HLSLEDITOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDockWidget>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTableWidget>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <codeeditor.h>

QT_BEGIN_NAMESPACE

class Ui_HLSLEditorClass
{
public:
    QAction *actionCompile;
    QAction *actionNew;
    QAction *actionUndo;
    QAction *actionRedo;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionExit;
    QAction *actionViewOpenFiles;
    QAction *actionViewOutput;
    QAction *actionViewErrors;
    QAction *actionViewRender;
    QAction *actionSave_2;
    QAction *actionReparse_Configuration;
    QAction *actionParallel_Compiling;
    QAction *actionOn_the_Fly_Compiling;
    QAction *actionSet_Working_Directory;
    QAction *actionSet_Additional_Include_Paths;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QComboBox *comboBox;
    CodeEditor *codeEditor;
    QStatusBar *statusbar;
    QDockWidget *dockWidgetErrors;
    QWidget *dockWidgetContents_8;
    QHBoxLayout *horizontalLayout;
    QTableWidget *tableWidget;
    QToolBar *toolBar;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuBuild;
    QMenu *menuView;
    QMenu *menuOptions;

    void setupUi(QMainWindow *HLSLEditorClass)
    {
        if (HLSLEditorClass->objectName().isEmpty())
            HLSLEditorClass->setObjectName(QString::fromUtf8("HLSLEditorClass"));
        HLSLEditorClass->resize(836, 660);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(HLSLEditorClass->sizePolicy().hasHeightForWidth());
        HLSLEditorClass->setSizePolicy(sizePolicy);
        HLSLEditorClass->setContextMenuPolicy(Qt::NoContextMenu);
        HLSLEditorClass->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);\n"
"\n"
"\n"
""));
        HLSLEditorClass->setDocumentMode(true);
        HLSLEditorClass->setTabShape(QTabWidget::Rounded);
        HLSLEditorClass->setDockOptions(QMainWindow::AllowNestedDocks|QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        actionCompile = new QAction(HLSLEditorClass);
        actionCompile->setObjectName(QString::fromUtf8("actionCompile"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/Icons/cc_mono_icon_set_png/blacks/48x48/download.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCompile->setIcon(icon);
        actionNew = new QAction(HLSLEditorClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        actionNew->setCheckable(false);
        actionNew->setEnabled(true);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/Icons/cc_mono_icon_set_png/blacks/48x48/doc_new.png"), QSize(), QIcon::Active, QIcon::Off);
        icon1.addFile(QString::fromUtf8(":/Icons/cc_mono_icon_set_png/white/48x48/doc_new.png"), QSize(), QIcon::Active, QIcon::On);
        actionNew->setIcon(icon1);
        QFont font;
        font.setFamily(QString::fromUtf8("Segoe UI"));
        actionNew->setFont(font);
        actionNew->setSoftKeyRole(QAction::NoSoftKey);
        actionNew->setIconVisibleInMenu(true);
        actionUndo = new QAction(HLSLEditorClass);
        actionUndo->setObjectName(QString::fromUtf8("actionUndo"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/Icons/cc_mono_icon_set_png/blacks/48x48/undo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUndo->setIcon(icon2);
        actionRedo = new QAction(HLSLEditorClass);
        actionRedo->setObjectName(QString::fromUtf8("actionRedo"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/Icons/cc_mono_icon_set_png/blacks/48x48/redo.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRedo->setIcon(icon3);
        actionOpen = new QAction(HLSLEditorClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(HLSLEditorClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSave_as = new QAction(HLSLEditorClass);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        actionExit = new QAction(HLSLEditorClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionViewOpenFiles = new QAction(HLSLEditorClass);
        actionViewOpenFiles->setObjectName(QString::fromUtf8("actionViewOpenFiles"));
        actionViewOpenFiles->setCheckable(true);
        actionViewOpenFiles->setChecked(true);
        actionViewOutput = new QAction(HLSLEditorClass);
        actionViewOutput->setObjectName(QString::fromUtf8("actionViewOutput"));
        actionViewOutput->setCheckable(true);
        actionViewOutput->setChecked(true);
        actionViewErrors = new QAction(HLSLEditorClass);
        actionViewErrors->setObjectName(QString::fromUtf8("actionViewErrors"));
        actionViewErrors->setCheckable(true);
        actionViewErrors->setChecked(true);
        actionViewRender = new QAction(HLSLEditorClass);
        actionViewRender->setObjectName(QString::fromUtf8("actionViewRender"));
        actionViewRender->setCheckable(true);
        actionViewRender->setChecked(true);
        actionSave_2 = new QAction(HLSLEditorClass);
        actionSave_2->setObjectName(QString::fromUtf8("actionSave_2"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/Icons/cc_mono_icon_set_png/blacks/48x48/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_2->setIcon(icon4);
        actionReparse_Configuration = new QAction(HLSLEditorClass);
        actionReparse_Configuration->setObjectName(QString::fromUtf8("actionReparse_Configuration"));
        actionParallel_Compiling = new QAction(HLSLEditorClass);
        actionParallel_Compiling->setObjectName(QString::fromUtf8("actionParallel_Compiling"));
        actionParallel_Compiling->setCheckable(true);
        actionOn_the_Fly_Compiling = new QAction(HLSLEditorClass);
        actionOn_the_Fly_Compiling->setObjectName(QString::fromUtf8("actionOn_the_Fly_Compiling"));
        actionOn_the_Fly_Compiling->setCheckable(true);
        actionSet_Working_Directory = new QAction(HLSLEditorClass);
        actionSet_Working_Directory->setObjectName(QString::fromUtf8("actionSet_Working_Directory"));
        actionSet_Additional_Include_Paths = new QAction(HLSLEditorClass);
        actionSet_Additional_Include_Paths->setObjectName(QString::fromUtf8("actionSet_Additional_Include_Paths"));
        centralwidget = new QWidget(HLSLEditorClass);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setFont(font);
        centralwidget->setContextMenuPolicy(Qt::NoContextMenu);
        centralwidget->setStyleSheet(QString::fromUtf8("/*QMenuBar { \n"
"	border-bottom: 1px solid gray; \n"
"}\n"
"\n"
"QMenuBar::item {\n"
"     background-color: transparent;\n"
"     color: black;\n"
" }\n"
"\n"
"QMenuBar::item::selected {\n"
"     background-color: steelblue  ;\n"
"     color: white;\n"
" }\n"
"\n"
"QMenu {\n"
"    background-color: steelblue  ;\n"
"    color: white;\n"
"	margin: 0px;\n"
" }\n"
"\n"
"QMenu::item {\n"
"    background-color: steelblue  ;\n"
"    color: white;\n"
"	padding: 4px 25px 4px 15px;\n"
" }\n"
"\n"
"QMenu::item::selected {\n"
"	border: 1px solid gray ;\n"
"    background-color: white;\n"
"    color: black ;\n"
" }*/\n"
"\n"
"background-color: white;\n"
"color: rgb(255, 255, 255);\n"
"border-top: 0px solid white;\n"
""));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setSpacing(0);
        verticalLayout->setContentsMargins(9, 9, 9, 9);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 1);
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"	 background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(230, 230, 235, 255), stop:1 rgba(200, 200, 205, 255));\n"
"	border: 1px solid gray;\n"
"	border-bottom: 0px solid white;\n"
"	color: black;\n"
"	height: 21px;\n"
"	border-top-right-radius: 3px;\n"
"	border-top-left-radius: 3px;\n"
"}\n"
"\n"
" QComboBox::drop-down {\n"
"     subcontrol-origin: padding;\n"
"     subcontrol-position: top right;\n"
"     width: 0px;\n"
" }\n"
"\n"
" QComboBox QAbstractItemView {\n"
"	 padding: 5px 5px 5px 10px;\n"
"	 background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0 rgba(200, 200, 205, 255), stop:1 rgba(195, 195, 200, 255) );\n"
"	 color: black;\n"
"	 selection-color: black;\n"
"     selection-background-color: WhiteSmoke ;\n"
"	 outline: solid;\n"
"	 border: 1px solid gray;\n"
"	 border-top: opx;\n"
" }\n"
"\n"
" QComboBox:on { /* shift the text when the popup opens */\n"
"	  background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(23"
                        "0, 230, 235, 255), stop:1 rgba(200, 200, 205, 255));\n"
"	 color: white;\n"
" }"));
        comboBox->setEditable(false);
        comboBox->setSizeAdjustPolicy(QComboBox::AdjustToContentsOnFirstShow);

        verticalLayout->addWidget(comboBox);

        codeEditor = new CodeEditor(centralwidget);
        codeEditor->setObjectName(QString::fromUtf8("codeEditor"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        codeEditor->setFont(font1);
        codeEditor->setStyleSheet(QString::fromUtf8("QMenuBar { \n"
"	border-bottom: 1px solid gray; \n"
"}\n"
"\n"
"QMenuBar::item {\n"
"	 font: 8pt \"Segoe UI\";\n"
"     background-color: transparent;\n"
"     color: black;\n"
" }\n"
"\n"
"QMenuBar::item::selected {\n"
"     background-color: whitesmoke;\n"
"     color: black;\n"
" }\n"
"\n"
"QMenu {\n"
"    background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(230, 230, 235, 255), stop:1 rgba(200, 200, 205, 255));\n"
"    color: black;\n"
"	margin: 0px;\n"
" }\n"
"\n"
"QMenu::item {\n"
"    background-color: transparent;\n"
"    color: black;\n"
"	padding: 4px 25px 4px 15px;\n"
" }\n"
"\n"
"QMenu::item::selected {\n"
"	border: 1px solid gray ;\n"
"    background-color: whitesmoke;\n"
"    color: black ;\n"
" }\n"
"\n"
"QScrollBar:horizontal {\n"
"    background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(230, 230, 235, 255), stop:1 rgba(200, 200, 200, 255));\n"
" 	border: 1px solid gray;\n"
"  }\n"
"\n"
"QScrollBar:vertical {\n"
"    background: qlineargra"
                        "dient(spread:pad, x1: 0, y1 :0, x2: 1, y2:0, stop:0.3 rgba(230, 230, 235, 255), stop:1 rgba(200, 200, 200, 255));\n"
"	border: 1px solid gray;\n"
"  }\n"
"\n"
"QPlainTextEdit {\n"
"	background-color: rgba(254, 254, 254, 255);\n"
"	color: rgb(0, 0, 0);\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
"\n"
""));
        codeEditor->setFrameShape(QFrame::StyledPanel);
        codeEditor->setLineWidth(1);
        codeEditor->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        codeEditor->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        codeEditor->setLineWrapMode(QPlainTextEdit::NoWrap);
        codeEditor->setBackgroundVisible(true);
        codeEditor->setCenterOnScroll(true);

        verticalLayout->addWidget(codeEditor);

        HLSLEditorClass->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(HLSLEditorClass);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8(" background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(230, 230, 235, 255), stop:1 rgba(200, 200, 205, 255));"));
        HLSLEditorClass->setStatusBar(statusbar);
        dockWidgetErrors = new QDockWidget(HLSLEditorClass);
        dockWidgetErrors->setObjectName(QString::fromUtf8("dockWidgetErrors"));
        dockWidgetErrors->setStyleSheet(QString::fromUtf8("QDockWidget::title {\n"
"     text-align: left; /* align the text to the left */\n"
"     background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(230, 230, 235, 255), stop:1 rgba(200, 200, 200, 255));\n"
"     padding-left: 5px;\n"
"	 border: 1px solid gray;\n"
"	border-top-right-radius: 3px;\n"
"	border-top-left-radius: 3px;\n"
" }\n"
"\n"
"font: 8pt \"Segoe UI\";"));
        dockWidgetErrors->setFeatures(QDockWidget::DockWidgetClosable|QDockWidget::DockWidgetMovable);
        dockWidgetContents_8 = new QWidget();
        dockWidgetContents_8->setObjectName(QString::fromUtf8("dockWidgetContents_8"));
        horizontalLayout = new QHBoxLayout(dockWidgetContents_8);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(9, 9, 9, 9);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(1, 0, 1, 1);
        tableWidget = new QTableWidget(dockWidgetContents_8);
        if (tableWidget->columnCount() < 5)
            tableWidget->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Ignored, QSizePolicy::Ignored);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(tableWidget->sizePolicy().hasHeightForWidth());
        tableWidget->setSizePolicy(sizePolicy1);
        tableWidget->setMinimumSize(QSize(324, 0));
        tableWidget->setStyleSheet(QString::fromUtf8("QScrollBar:horizontal {\n"
"    background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.5 rgba(255, 255, 255, 255), stop:1 rgba(200, 200, 200, 255));\n"
"  }\n"
"\n"
"QScrollBar:vertical {\n"
"    background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 1, y2:0, stop:0.5 rgba(255, 255, 255, 255), stop:1 rgba(200, 200, 200, 255));\n"
"  }\n"
"\n"
"QTableWidget { \n"
"	background-color: rgb(255, 255, 255);\n"
"	color: rgb(0, 0, 0);\n"
"	border: 1px solid gray;\n"
"}\n"
"\n"
""));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        tableWidget->setSortingEnabled(true);
        tableWidget->setCornerButtonEnabled(true);
        tableWidget->setColumnCount(5);
        tableWidget->horizontalHeader()->setVisible(true);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(true);
        tableWidget->horizontalHeader()->setDefaultSectionSize(200);
        tableWidget->horizontalHeader()->setMinimumSectionSize(50);
        tableWidget->horizontalHeader()->setProperty("showSortIndicator", QVariant(true));
        tableWidget->horizontalHeader()->setStretchLastSection(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setProperty("showSortIndicator", QVariant(false));

        horizontalLayout->addWidget(tableWidget);

        dockWidgetErrors->setWidget(dockWidgetContents_8);
        HLSLEditorClass->addDockWidget(static_cast<Qt::DockWidgetArea>(8), dockWidgetErrors);
        toolBar = new QToolBar(HLSLEditorClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QLinearGradient gradient(0, 0, 0, 1);
        gradient.setSpread(QGradient::PadSpread);
        gradient.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush1(gradient);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        QLinearGradient gradient1(0, 0, 0, 1);
        gradient1.setSpread(QGradient::PadSpread);
        gradient1.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient1.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient1.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush2(gradient1);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        QLinearGradient gradient2(0, 0, 0, 1);
        gradient2.setSpread(QGradient::PadSpread);
        gradient2.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient2.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient2.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush3(gradient2);
        palette.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QLinearGradient gradient3(0, 0, 0, 1);
        gradient3.setSpread(QGradient::PadSpread);
        gradient3.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient3.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient3.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush4(gradient3);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        QLinearGradient gradient4(0, 0, 0, 1);
        gradient4.setSpread(QGradient::PadSpread);
        gradient4.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient4.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient4.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush5(gradient4);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush5);
        QLinearGradient gradient5(0, 0, 0, 1);
        gradient5.setSpread(QGradient::PadSpread);
        gradient5.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient5.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient5.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush6(gradient5);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        QLinearGradient gradient6(0, 0, 0, 1);
        gradient6.setSpread(QGradient::PadSpread);
        gradient6.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient6.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient6.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush7(gradient6);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        QLinearGradient gradient7(0, 0, 0, 1);
        gradient7.setSpread(QGradient::PadSpread);
        gradient7.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient7.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient7.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush8(gradient7);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        QLinearGradient gradient8(0, 0, 0, 1);
        gradient8.setSpread(QGradient::PadSpread);
        gradient8.setCoordinateMode(QGradient::ObjectBoundingMode);
        gradient8.setColorAt(0.3, QColor(245, 245, 245, 255));
        gradient8.setColorAt(1, QColor(230, 230, 235, 255));
        QBrush brush9(gradient8);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush9);
        toolBar->setPalette(palette);
        toolBar->setContextMenuPolicy(Qt::NoContextMenu);
        toolBar->setStyleSheet(QString::fromUtf8("QToolBar { \n"
"	color: rgb(0, 0, 0);\n"
"	 background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(245, 245, 245, 255), stop:1 rgba(230, 230, 235, 255));\n"
"	padding: 1px 0px 0px 1px;\n"
"}\n"
"\n"
"QToolButton {\n"
"	background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(245, 245, 245, 255), stop:1 rgba(230, 230, 235, 255));\n"
"\n"
"}\n"
"\n"
" QToolButton::hover {\n"
"	background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.847, stop:0.386364 rgba(250, 250, 255, 255), stop:1 lightgray);\n"
"	border: 1px solid gray\n"
" }\n"
""));
        toolBar->setIconSize(QSize(16, 16));
        toolBar->setToolButtonStyle(Qt::ToolButtonFollowStyle);
        toolBar->setFloatable(false);
        HLSLEditorClass->addToolBar(Qt::TopToolBarArea, toolBar);
        menuBar = new QMenuBar(HLSLEditorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 836, 19));
        menuBar->setContextMenuPolicy(Qt::NoContextMenu);
        menuBar->setStyleSheet(QString::fromUtf8("QMenuBar { \n"
"	border-bottom: 1px solid gray; \n"
"	background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(230, 230, 235, 255), stop:1 rgba(200, 200, 205, 255));\n"
"	font: 8pt \"Segoe UI\";\n"
"}\n"
"\n"
"QMenuBar::item {\n"
"    background: transparent;\n"
"     color: black;\n"
" }\n"
"\n"
"QMenuBar::item::selected {\n"
"     background: qlineargradient(spread:pad, x1: 0, y1 :1, x2: 0, y2:0, stop:0.3 rgba(245, 245, 245, 255), stop:1 rgba(230, 230, 235, 255));\n"
"     color: black;\n"
" }\n"
"\n"
"QMenu {\n"
"     background: qlineargradient(spread:pad, x1: 0, y1 :0, x2: 0, y2:1, stop:0.3 rgba(245, 245, 245, 255), stop:1 rgba(230, 230, 235, 255));\n"
"     color: white;\n"
"	 margin: 0px;\n"
" }\n"
"\n"
"QMenu::item {\n"
"    background: transparent;\n"
"    color: black;\n"
"	padding: 4px 25px 4px 20px;\n"
" }\n"
"\n"
"QMenu::item::selected {\n"
"	border: 1px solid gray ;\n"
"    background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:0, y2:0.847, stop:0.386364 rgba(250, 25"
                        "0, 255, 255), stop:1 lightgray);\n"
"    color: black ;\n"
" }\n"
"\n"
"\n"
""));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuBuild = new QMenu(menuBar);
        menuBuild->setObjectName(QString::fromUtf8("menuBuild"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuOptions = new QMenu(menuBar);
        menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
        HLSLEditorClass->setMenuBar(menuBar);

        toolBar->addAction(actionNew);
        toolBar->addAction(actionSave_2);
        toolBar->addAction(actionUndo);
        toolBar->addAction(actionRedo);
        toolBar->addSeparator();
        toolBar->addAction(actionCompile);
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuBuild->menuAction());
        menuBar->addAction(menuOptions->menuAction());
        menuFile->addAction(actionOpen);
        menuFile->addAction(actionSave);
        menuFile->addAction(actionSave_as);
        menuFile->addAction(actionExit);
        menuFile->addSeparator();
        menuFile->addAction(actionReparse_Configuration);
        menuView->addAction(actionViewErrors);
        menuView->addAction(actionViewOpenFiles);
        menuView->addAction(actionViewOutput);
        menuView->addAction(actionViewRender);
        menuOptions->addAction(actionOn_the_Fly_Compiling);
        menuOptions->addAction(actionSet_Additional_Include_Paths);

        retranslateUi(HLSLEditorClass);
        QObject::connect(actionViewErrors, SIGNAL(toggled(bool)), dockWidgetErrors, SLOT(setVisible(bool)));
        QObject::connect(dockWidgetErrors, SIGNAL(visibilityChanged(bool)), actionViewErrors, SLOT(setChecked(bool)));

        QMetaObject::connectSlotsByName(HLSLEditorClass);
    } // setupUi

    void retranslateUi(QMainWindow *HLSLEditorClass)
    {
        HLSLEditorClass->setWindowTitle(QApplication::translate("HLSLEditorClass", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionCompile->setText(QApplication::translate("HLSLEditorClass", "Compile", 0, QApplication::UnicodeUTF8));
        actionNew->setText(QApplication::translate("HLSLEditorClass", "New", 0, QApplication::UnicodeUTF8));
        actionUndo->setText(QApplication::translate("HLSLEditorClass", "Undo", 0, QApplication::UnicodeUTF8));
        actionRedo->setText(QApplication::translate("HLSLEditorClass", "Redo", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("HLSLEditorClass", "Open", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("HLSLEditorClass", "Save", 0, QApplication::UnicodeUTF8));
        actionSave_as->setText(QApplication::translate("HLSLEditorClass", "Save as...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("HLSLEditorClass", "Exit", 0, QApplication::UnicodeUTF8));
        actionViewOpenFiles->setText(QApplication::translate("HLSLEditorClass", "Open Files", 0, QApplication::UnicodeUTF8));
        actionViewOutput->setText(QApplication::translate("HLSLEditorClass", "Output", 0, QApplication::UnicodeUTF8));
        actionViewErrors->setText(QApplication::translate("HLSLEditorClass", "Errors", 0, QApplication::UnicodeUTF8));
        actionViewRender->setText(QApplication::translate("HLSLEditorClass", "Render", 0, QApplication::UnicodeUTF8));
        actionSave_2->setText(QApplication::translate("HLSLEditorClass", "Save", 0, QApplication::UnicodeUTF8));
        actionReparse_Configuration->setText(QApplication::translate("HLSLEditorClass", "Reparse config.xml", 0, QApplication::UnicodeUTF8));
        actionParallel_Compiling->setText(QApplication::translate("HLSLEditorClass", "Parallel Compiling", 0, QApplication::UnicodeUTF8));
        actionOn_the_Fly_Compiling->setText(QApplication::translate("HLSLEditorClass", "On the Fly Compiling", 0, QApplication::UnicodeUTF8));
        actionSet_Working_Directory->setText(QApplication::translate("HLSLEditorClass", "Set Working Directory", 0, QApplication::UnicodeUTF8));
        actionSet_Additional_Include_Paths->setText(QApplication::translate("HLSLEditorClass", "Set Additional Include Paths", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        codeEditor->setToolTip(QString());
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        statusbar->setStatusTip(QApplication::translate("HLSLEditorClass", "Ready", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_STATUSTIP
        dockWidgetErrors->setWindowTitle(QApplication::translate("HLSLEditorClass", "Errors", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("HLSLEditorClass", "Type", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("HLSLEditorClass", "Description", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("HLSLEditorClass", "ID", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("HLSLEditorClass", "File", 0, QApplication::UnicodeUTF8));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("HLSLEditorClass", "Line", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("HLSLEditorClass", "toolBar", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("HLSLEditorClass", "File", 0, QApplication::UnicodeUTF8));
        menuBuild->setTitle(QApplication::translate("HLSLEditorClass", "Build", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("HLSLEditorClass", "View", 0, QApplication::UnicodeUTF8));
        menuOptions->setTitle(QApplication::translate("HLSLEditorClass", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HLSLEditorClass: public Ui_HLSLEditorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HLSLEDITOR_H
