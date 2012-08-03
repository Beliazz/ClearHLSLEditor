#include "StdAfx.h"
#include "HLSLCompiler.h"

//////////////////////////////////////////////////////////////////////////
// async compiler
AsyncCompiler::AsyncCompiler()
{
	m_thread = NULL;
	m_startEvent = NULL;
	m_pData = NULL;
	m_dataSize = 0;
	m_pCompiledData = NULL;
	m_compiledDataSize = 0;
	m_result = E_FAIL;
	m_idle = true;
	m_terminate = false;
	m_save = false;
}
AsyncCompiler::~AsyncCompiler()
{
	if (m_pData != NULL)
		free(m_pData);
}

void AsyncCompiler::SetLocalDirectory( QString directory )
{
	m_includeHandler.SetLocalDirectory(directory);
}
void AsyncCompiler::SetIncludeDirectories( QVector<QString> directories )
{
	m_includeHandler.SetDirectories(directories);
}
void AsyncCompiler::SetIdle( bool idle )
{
	m_idle = idle;
}
void AsyncCompiler::SetEvent()
{
	::SetEvent(m_startEvent);
}
void AsyncCompiler::SetResult( HRESULT result )
{
	m_result = result;
}
void AsyncCompiler::SetErrors( QVector<CompilerError> errors )
{
	m_errors = QVector<CompilerError>(errors);
}
void AsyncCompiler::Terminate()
{
	m_terminate = true;
}
void AsyncCompiler::SetFilename( QString filename )
{
	m_fileName = filename;
}
void AsyncCompiler::SetSave( bool save )
{
	m_save = save;
}

void AsyncCompiler::SetData( void* pData, uint size )
{
	if(m_pData) { free(m_pData); }
	m_dataSize = size;
	m_pData = malloc(m_dataSize);
	memcpy(m_pData, pData, m_dataSize);
}
UINT AsyncCompiler::GetData( void** pDest )
{
	(*pDest) = malloc(m_dataSize);
	memcpy((*pDest), m_pData, m_dataSize);
	return m_dataSize;
}
void AsyncCompiler::SetCompiledData( void* pData, uint size )
{
	if(m_pCompiledData) { free(m_pCompiledData); }
	m_compiledDataSize = size;
	m_pCompiledData = malloc(m_compiledDataSize);
	memcpy(m_pCompiledData, pData, m_compiledDataSize);
}
UINT AsyncCompiler::GetCompiledData( void** pDest )
{
	(*pDest) = malloc(m_compiledDataSize);
	memcpy((*pDest), m_pCompiledData, m_compiledDataSize);
	return m_compiledDataSize;
}
void AsyncCompiler::AddHeaderData( const QString& filename, const HEADER_DATA& data )
{
	m_includeHandler.AddHeaderData(filename, data);
}
void AsyncCompiler::RemoveHeaderData( const QString& filename )
{
	m_includeHandler.RemoveHeaderData(filename);
}

void AsyncCompiler::Reset()
{
	m_thread = NULL;
	m_terminate = false;
	m_idle = true;
}
bool AsyncCompiler::Compile( ThreadSafe<AsyncCompiler>* pCompilerData )
{
	if (m_thread == NULL)
	{
		m_startEvent = CreateEvent(NULL, false, true, NULL);
		m_thread = CreateThread(NULL, NULL, &AsyncCompile, pCompilerData, NULL, NULL);
		if (m_thread != NULL)
		{
			return true;
		}
	}
	else
	{
		SetEvent();
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////
// static thread functions
DWORD WINAPI AsyncCompiler::AsyncCompile( LPVOID pData )
{
	ThreadSafe<AsyncCompiler>& pCompiler = *((ThreadSafe<AsyncCompiler>*)pData);

	ID3DBlob* pErrors = NULL;
	ID3DBlob* pCode = NULL;
	ID3DInclude* pInclude;
	HANDLE startEvent = pCompiler->GetEvent();

	while(!pCompiler->Terminating())
	{			
		pCompiler->SetIdle(true);
		::WaitForSingleObject(startEvent, INFINITE);

		void* pData = NULL;
		int size;
		QString filename;
		QString localDirectory;

		{
			ThreadSafe<AsyncCompiler>::BlockSecurity __blockSec(&pCompiler);
			pCompiler->SetIdle(false);
			size = pCompiler->GetData(&pData);
			pInclude = pCompiler->GetIncludeHandler();
			filename = pCompiler->GetFilename();
			localDirectory = pCompiler->GetLocalDirectory();
		}

		// compile
		HRESULT result = D3DCompile(pData, size, filename.toAscii().constData(), NULL, pInclude, NULL, "fx_5_0", NULL, NULL, &pCode, &pErrors );
		
		// parse output
		QVector<CompilerError> error;
		if (pErrors)
		{
			error = AsyncParseCompilerOutput((char*)pErrors->GetBufferPointer(), localDirectory);
		}

		{
			ThreadSafe<AsyncCompiler>::BlockSecurity __blockSec(&pCompiler);
			if (SUCCEEDED(result) && pCompiler->GetSave())
			{
				pCompiler->SetCompiledData(pCode->GetBufferPointer(), pCode->GetBufferSize());
				filename = pCompiler->GetLocalDirectory() + "\\" + pCompiler->GetFilename() + "c";
			}

			pCompiler->SetErrors(error);
			pCompiler->SetResult(result);
		}

		if (SUCCEEDED(result))
		{
			FILE* pFile = fopen(filename.toAscii().data(), "wb");
			if (pFile)
			{
				fwrite(pCode->GetBufferPointer(), pCode->GetBufferSize(), 1, pFile);
				fclose(pFile);
			}
		}

		// release com interfaces
		SAFE_RELEASE(pErrors);
		SAFE_RELEASE(pCode);
	}

	pCompiler->Reset();

	return 0;
}
QVector<CompilerError> AsyncCompiler::AsyncParseCompilerOutput( QString outputToParse, QString localDirectory )
{
	QVector<CompilerError> errors;

	// get lines
	QStringList lines = outputToParse.split(QRegExp("\n"), QString::SkipEmptyParts);

	foreach (const QString& line, lines)
	{
		CompilerError output;
		PARSE_STATE state = FILENAME;
		QString buff;
		for (int cursor = 0; cursor < line.size(); cursor++)
		{
			QChar currChar = line[cursor];
			switch(state)
			{
			case FILENAME:
				{
					if (currChar == '(')
					{
						state = POS_LINE;
						output.filename = buff.remove(localDirectory.replace('/', '\\') + "\\");
						buff.clear();
					}
					else
					{
						buff.push_back(currChar);
					}
				} break;

				//////////////////////////////////////////////////////////////////////////
				// position
				// 
				// line
			case POS_LINE:
				{
					if (currChar == ',')
					{
						output.location.setX(buff.toInt());
						buff.clear();
						state = POS_CHAR;
					}
					else
					{
						buff.push_back(currChar);
					}

				} break;
				//
				// char pos
			case POS_CHAR:
				{
					if (currChar == ')')
					{
						output.location.setY(buff.toInt());
						buff.clear();
						cursor += 2;
						state = TYPE;
					}
					else
					{
						buff += currChar;
					}
				} break;


				//////////////////////////////////////////////////////////////////////////
				// output type
				// 
			case TYPE:
				{
					if (currChar == ' ')
					{
						buff = buff.toLower();

						if (buff == "warning")
						{
							output.type = OUTPUT_TYPE_WARNING;
							buff.clear();
							state = IDENTIFIER;
						}
						else if ( buff == "error" )
						{
							output.type = OUTPUT_TYPE_ERROR;
							buff.clear();
							state = IDENTIFIER;
						}
						else
						{
							buff += currChar;
							output.type = OUTPUT_TYPE_INFO;
							state = MESSAGE;
						}

					}
					else
					{
						buff += currChar;
					}
				} break;

				//////////////////////////////////////////////////////////////////////////
				// identifier
				// 
			case IDENTIFIER:
				{
					if (currChar == ':')
					{
						output.errorID = buff;
						buff.clear();
						state = MESSAGE;
						cursor++;
					}
					else
					{
						buff += currChar;
					}
				} break;

				//////////////////////////////////////////////////////////////////////////
				// message
				// 
			case MESSAGE:
				{
					buff += currChar;
					if (cursor == line.size()-1)
					{
						output.message = buff;
						buff.clear();
						state = IDLE;
					}
				} break;
			}
		}

		errors.push_back(output);
	}

	return errors;
}













