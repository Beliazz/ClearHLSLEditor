#include "HLSLEditor.h"

HLSLEditor::HLSLEditor(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
{
	CoInitializeEx(NULL, COINIT_MULTITHREADED);

	// set up user interface
	QTableWidgetItem* pItem;
	ui.setupUi(this);
	
	ui.tableWidget->horizontalHeaderItem(0)->setSizeHint(QSize(100, 30));
	ui.tableWidget->horizontalHeaderItem(2)->setSizeHint(QSize(80, 30));
	ui.tableWidget->horizontalHeaderItem(3)->setSizeHint(QSize(80, 30));
	ui.tableWidget->horizontalHeaderItem(4)->setSizeHint(QSize(80, 30));

	setStyle(new QWindowsVistaStyle());

	// connections
	QObject::connect(ui.actionOpen, SIGNAL(triggered()), this, SLOT(Open_EvtHandler()));
	QObject::connect(ui.actionCompile, SIGNAL(triggered()), this, SLOT(Compile_EvtHandler()));
	QObject::connect(ui.actionSave, SIGNAL(triggered()), this, SLOT(Save_EvtHandler()));
	QObject::connect(ui.actionSave_2, SIGNAL(triggered()), this, SLOT(Save_EvtHandler()));
	QObject::connect(ui.tableWidget, SIGNAL(itemSelectionChanged()), this, SLOT(ErrorClicked_EvtHandler()));
	QObject::connect(ui.actionReparse_Configuration, SIGNAL(triggered()), this, SLOT(ReparseConfig_EvtHandler()));
	QObject::connect(&m_timCheckAsyncCompiler, SIGNAL(timeout()), this, SLOT(CheckAsynCompiler_EvtHandler()));
	QObject::connect(ui.codeEditor, SIGNAL(textChanged()), this, SLOT(TextChanged_EvtHandler()));
	QObject::connect(&m_compileTimout, SIGNAL(timeout()), this, SLOT(CheckCompileTimout_EvtHandler()));
	QObject::connect(ui.comboBox, SIGNAL(currentIndexChanged (const QString)), this, SLOT(ActiveDocumentChanged_EvtHandler(const QString)));

	m_pCGLMgr = NULL;
	m_pCurrDoc = NULL;
}
HLSLEditor::~HLSLEditor()
{
	QMap<QString, HLSLDocument*>::Iterator it = m_docs.begin();
	for(it; it != m_docs.end(); it++)
	{
		SAFE_DELETE((*it));
	}

	m_docs.clear();

	CoUninitialize();
}

bool HLSLEditor::Init()
{
	m_loading = true;

	// load config file
	QFile configFile("config.xml");
	if (configFile.open(QIODevice::ReadWrite))
	{
		QDomDocument config("config.xml");
		if(config.setContent(&configFile))
		{
			if (!ui.codeEditor->Init(&config))
				return false;
		}
		else
		{
			QMessageBox msgBox("Error", "Unable to read configuration file!", QMessageBox::Critical, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
			msgBox.exec();
			return false;
		}
	}


	//////////////////////////////////////////////////////////////////////////
	// init graphics
	if (!InitGraphics())
		return false;

	m_pAsyncCompiler.setObject(new AsyncCompiler());


	m_timCheckAsyncCompiler.setInterval(100);
	m_timCheckAsyncCompiler.setSingleShot(false);
	m_compileTimout.setInterval(2000);
	m_timCheckAsyncCompiler.setSingleShot(true);
	
#ifdef TEST
	// set default file for debugging
	HLSLDocument* testFile = new HLSLDocument("simple.fx");
	if (testFile->Open())
	{
		m_docs.insert(testFile->GetName(), testFile);
		//ui.codeEditor->SetText(testFile->GetText());
		ui.comboBox->addItem(testFile->GetName(), 0);
	}
#endif

	ui.codeEditor->ResetBlockData();
	m_loading = false;

	TextChanged_EvtHandler();

	return true;
}
bool HLSLEditor::InitGraphics()
{
// 	m_pCGLMgr = cgl::PCGLManager(new cgl::CGLManager());
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	// create factory
// 	cgl::PDXGIFactory pFactory = cgl::CDXGIFactory::Create();
// 	if (!pFactory)
// 		return false;
// 
// 	pFactory->restore();
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	// device desc
// 	cgl::CGL_D3D11_DEVICE_DESC deviceDesc;
// 	ZeroMemory(&deviceDesc, sizeof(deviceDesc));
// 
// 	// windowed
// 	QDomNamedNodeMap attr = m_pConfig->documentElement().elementsByTagName("Graphics").at(0).toElement().elementsByTagName("Device").at(0).attributes();
// 	deviceDesc.swapDesc.Windowed = attr.namedItem("Windowed").nodeValue().toInt();
// 	int deviceIndex = attr.namedItem("ID").nodeValue().toInt();
// 	int outputIndex = attr.namedItem("Output").nodeValue().toInt();
// 
// 	// get adapter info
// 	cgl::PDXGIAdapter pAdapter = cgl::CDXGIAdapter::Create(pFactory, deviceIndex);
// 	cgl::PDXGIOutput pOutput = cgl::CDXGIOutput::Create(pAdapter, outputIndex);
// 
// 	if (!pOutput->restore())
// 		return false;
// 
// 	// buffer desc
// 	DXGI_MODE_DESC modeToMatch;
// 	DXGI_MODE_DESC closestMode;
// 	ZeroMemory(&modeToMatch, sizeof(modeToMatch));
// 
// 	// format
// 	attr = m_pConfig->documentElement().elementsByTagName("Graphics").at(0).toElement().elementsByTagName("Backbuffer").at(0).attributes();
// 	if(attr.namedItem("Bpp").nodeValue().toInt() == 16)
// 	{
// 		modeToMatch.Format = DXGI_FORMAT_B5G6R5_UNORM;
// 	}
// 	else
// 	{
// 		modeToMatch.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
// 	}
// 
// 	// width, height, scaling, scanline ordering
// 	modeToMatch.Width = attr.namedItem("Width").nodeValue().toInt();
// 	modeToMatch.Height = attr.namedItem("Height").nodeValue().toInt();
// 	modeToMatch.RefreshRate.Denominator = 1;
// 	modeToMatch.RefreshRate.Numerator = attr.namedItem("RefreshRate").nodeValue().toInt();
// 	modeToMatch.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
// 	modeToMatch.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_PROGRESSIVE;
// 
// 	HRESULT result = pOutput->get()->FindClosestMatchingMode(&modeToMatch, &closestMode, NULL);
// 
// 	std::vector<DXGI_MODE_DESC> modes = pOutput->GetFormats();
// 	DXGI_MODE_DESC selectedMode = modes[modes.size() - 1];
// 
// 	deviceDesc.pAdapter = NULL;
// 	deviceDesc.flags = D3D11_CREATE_DEVICE_DEBUG;
// 	deviceDesc.driverType = D3D_DRIVER_TYPE_HARDWARE;
// 	deviceDesc.featureLevel = D3D_FEATURE_LEVEL_10_1;
// 	deviceDesc.swapDesc.OutputWindow = ui.graphicsView->winId();
// 	deviceDesc.swapDesc.SampleDesc.Count = 1;
// 	deviceDesc.swapDesc.SampleDesc.Quality = 0;
// 	deviceDesc.swapDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
// 	deviceDesc.swapDesc.Windowed = TRUE;
// 	deviceDesc.swapDesc.BufferCount = 1;
// 	deviceDesc.swapDesc.BufferDesc = closestMode;
// 	deviceDesc.swapDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
// 
// 	//////////////////////////////////////////////////////////////////////////
// 	// create device
// 	cgl::PD3D11Device pDevice = cgl::CD3D11Device::Create(deviceDesc);
// 	if (!pDevice)
// 		return false;
// 
 	return true;
}

void HLSLEditor::Compile_EvtHandler()
{
	if (m_loading || !m_pCurrDoc)
		return;

	m_pCurrDoc->SetText(ui.codeEditor->toPlainText());

	{
		ThreadSafe<AsyncCompiler>::BlockSecurity __blockSec(&m_pAsyncCompiler);

		m_pAsyncCompiler->SetSave(true);
		if(m_pCurrDoc->GetType() == HLSL_HEADER)
		{
			HEADER_DATA headerData;
			QByteArray arr = m_pCurrDoc->GetText().toAscii();
			headerData.pData = arr.data();
			headerData.size = arr.size();
			m_pAsyncCompiler->AddHeaderData(m_pCurrDoc->GetName(), headerData );
			m_pAsyncCompiler->SetSave(false);
		}

		m_pAsyncCompiler->SetLocalDirectory(m_pCurrDoc->GetDirectory());
		m_pAsyncCompiler->SetData(m_pCurrDoc->GetText().toAscii().data(),
		m_pCurrDoc->GetText().toAscii().size());
		m_pAsyncCompiler->SetFilename(m_pCurrDoc->GetName());
		m_pAsyncCompiler->Compile(&m_pAsyncCompiler);
	}


	m_isOtfc = false;
	m_timCheckAsyncCompiler.start();
}
void HLSLEditor::Save_EvtHandler()
{
	m_pCurrDoc->SetText(ui.codeEditor->document()->toPlainText());
	m_pCurrDoc->Save();
}
void HLSLEditor::Open_EvtHandler()
{
	QString fileName = QFileDialog::getOpenFileName(this, "Open File", m_localDirectory, "HLSL Source Files (*.fx);;HLSL Header Files (*.fxh)", (QString*)0, QFileDialog::ReadOnly);
	
	if (!fileName.isNull())
	{
		HLSLDocument  temp(fileName);
		QMap<QString, HLSLDocument*>::iterator it = m_docs.find(temp.GetName());
		if (it != m_docs.end())
		{
			m_pCurrDoc = *it;
			ui.codeEditor->SetText((*it)->GetText());
			ui.comboBox->setCurrentIndex(ui.comboBox->findText((*it)->GetName()));
		}
		else
		{
			HLSLDocument*  pDoc = new HLSLDocument(fileName);
			if (pDoc->Open())
			{
				m_docs.insert(pDoc->GetName(), pDoc);
				m_pCurrDoc = pDoc;

				ui.codeEditor->SetText(pDoc->GetText());
				ui.comboBox->addItem(pDoc->GetName(), 0);

				ui.comboBox->setCurrentIndex(ui.comboBox->findText(pDoc->GetName()));
			}
		}
	}

}
void HLSLEditor::TextChanged_EvtHandler()
{
	if (m_loading || !m_pCurrDoc)
		return;

	m_pCurrDoc->SetText(ui.codeEditor->toPlainText());
	
	{
		ThreadSafe<AsyncCompiler>::BlockSecurity __blockSec(&m_pAsyncCompiler);
		
		if(m_pCurrDoc->GetType() == HLSL_HEADER)
		{
			HEADER_DATA headerData;
			QByteArray arr = m_pCurrDoc->GetText().toAscii();
			headerData.pData = arr.data();
			headerData.size = arr.size();
			m_pAsyncCompiler->AddHeaderData(m_pCurrDoc->GetName(), headerData );
		}

		m_pAsyncCompiler->SetLocalDirectory(m_pCurrDoc->GetDirectory());
		m_pAsyncCompiler->SetData(m_pCurrDoc->GetText().toAscii().data(),
								  m_pCurrDoc->GetText().toAscii().size());

		m_pAsyncCompiler->SetFilename(m_pCurrDoc->GetName());
		m_pAsyncCompiler->Compile(&m_pAsyncCompiler);
	}


	m_isOtfc = true;
	m_timCheckAsyncCompiler.start();
}
void HLSLEditor::ErrorClicked_EvtHandler()
{
	QVariant line = ui.tableWidget->item(ui.tableWidget->currentRow(), 3)->data(0);
	if (line.isValid())
	{
		ui.codeEditor->SetCursorPos(line.toInt());
	}
}
void HLSLEditor::ReparseConfig_EvtHandler()
{
	// load config file
	QFile configFile("config.xml");
	if (configFile.open(QIODevice::ReadWrite))
	{
		QDomDocument config("config.xml");
		if(config.setContent(&configFile))
		{
			if (!ui.codeEditor->ParseConfigFile(&config))
			{
				QMessageBox msgBox("Error", "Unable to read configuration file!", QMessageBox::Critical, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
				msgBox.exec();
			}
		}
		else
		{
			QMessageBox msgBox("Error", "Unable to read configuration file!", QMessageBox::Critical, QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);
			msgBox.exec();
		}
	}	
}
void HLSLEditor::CheckAsynCompiler_EvtHandler()
{
	if(m_pAsyncCompiler->Idle())
	{	
		m_timCheckAsyncCompiler.stop();
		
		HRESULT result = m_pAsyncCompiler->GetResult();
		if (SUCCEEDED(result))
		{
			CheckCompileTimout_EvtHandler();
		}
		else
		{
			m_compileTimout.start();
		}
	
		if(!m_isOtfc)
		{
			ui.codeEditor->setReadOnly(false);
		}
	}
}
void HLSLEditor::CheckCompileTimout_EvtHandler()
{
	QVector<CompilerError> output = m_pAsyncCompiler->GetErrors();

	ui.tableWidget->clearContents();
	ui.tableWidget->setRowCount(output.size());
	for (int i = 0; i < output.size(); i++)
	{	
		switch(output[i].type)
		{
		case OUTPUT_TYPE_WARNING:	{ ui.tableWidget->setItem(i, 0, new QTableWidgetItem("Warning"));}	break;
		case OUTPUT_TYPE_ERROR:		{ ui.tableWidget->setItem(i, 0, new QTableWidgetItem("Error")); }	break;
		case OUTPUT_TYPE_INFO:		{ ui.tableWidget->setItem(i, 0, new QTableWidgetItem("Info")); }	break;
		}

		// display error msg
		ui.tableWidget->setItem(i, 1, new QTableWidgetItem(output[i].message));
		ui.tableWidget->setItem(i, 2, new QTableWidgetItem(output[i].errorID));
		ui.tableWidget->setItem(i, 3, new QTableWidgetItem(output[i].filename));
		ui.tableWidget->setItem(i, 4, new QTableWidgetItem(QString::number(output[i].location.x())));
	}

	ui.codeEditor->SetErrors(output);
}
void HLSLEditor::ActiveDocumentChanged_EvtHandler( const QString doc)
{
	if(m_pCurrDoc)
	{
		m_pCurrDoc->SetText(ui.codeEditor->document()->toPlainText());
	}
	
	m_loading = true;

	QMap<QString, HLSLDocument*>::iterator it = m_docs.find(doc);
	if (it != m_docs.end())
	{
		m_pCurrDoc = it.value();
		ui.codeEditor->SetText(m_pCurrDoc->GetText());
		ui.codeEditor->ResetBlockData();
	}

	m_loading = false;

	TextChanged_EvtHandler();
}


