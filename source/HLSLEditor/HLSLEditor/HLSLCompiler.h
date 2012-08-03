#pragma once

#include "stdafx.h"
#include "IncludeHandler.h"

enum OUTPUT_TYPE
{
	OUTPUT_TYPE_INFO,
	OUTPUT_TYPE_WARNING,
	OUTPUT_TYPE_ERROR
};

struct CompilerError
{
	OUTPUT_TYPE type;
	QString errorID;
	QString message;	
	
	// the x component represents the line
	// the y component represents the character
	QPoint location;
	QString filename;
};

enum PARSE_STATE
{
	IDLE,
	FILENAME,
	POS_LINE,
	POS_CHAR,
	TYPE,
	IDENTIFIER,
	MESSAGE
};

template <class T>
class ThreadSafe
{
private:
	CRITICAL_SECTION m_cs;
	T* m_obj;

	void enterSecureMode()
	{
		::EnterCriticalSection(&m_cs);
	}
	void leaveSecureMode()
	{
		::LeaveCriticalSection(&m_cs);
	}

public:
	class BlockSecurity
	{
		ThreadSafe* m_pParent;
		int m_lockCount;

	public:
		BlockSecurity(ThreadSafe* pParent) : m_pParent(pParent), m_lockCount(0)
		{
			pParent->enterSecureMode();
		}
		~BlockSecurity()
		{
			m_pParent->leaveSecureMode();
		}

		T* operator ->()
		{
			return m_pParent->m_obj;
		}
		T* operator *()
		{
			return m_pParent->m_obj;
		}
	};

	ThreadSafe(T* obj = NULL) : m_obj(obj)
	{
		::InitializeCriticalSection(&m_cs);
	}
	ThreadSafe(ThreadSafe& rhs)
	{
		::InitializeCriticalSection(&m_cs);

		rhs.enterSecureMode();
		m_obj = rhs.m_obj;
		rhs.leaveSecureMode();
	}
	~ThreadSafe()
	{
		::EnterCriticalSection(&m_cs);
		::LeaveCriticalSection(&m_cs);
		::DeleteCriticalSection(&m_cs);
	}
	ThreadSafe& operator = (ThreadSafe& rhs)
	{
		if (&rhs == this)
			return *this;

		setObject(rhs.m_obj);

		return *this;
	}

	// insecure function
	void setObject(T* obj)
	{
		BlockSecurity __blockSec(this);
		m_obj = obj;
	}
	void reset()
	{
		BlockSecurity __blockSec(this);
		m_obj = NULL;
	}
	inline T* get() { return m_obj; }
	

	operator bool()
	{
		BlockSecurity __blockSec(this);
		return (bool)m_obj;
	}
	bool operator !()
	{
		BlockSecurity __blockSec(this);
		return !m_obj;
	}

	BlockSecurity operator ->()
	{
		return this;
	}
	BlockSecurity operator *()
	{
		return this;
	}
};

enum EFFECT_PROFILE
{
	EFFECT_PROFILE_2_0,
	EFFECT_PROFILE_3_0,
	EFFECT_PROFILE_4_0,
	EFFECT_PROFILE_5_0 
};

class AsyncCompiler
{
private:
	void* m_pData;
	uint  m_dataSize;

	void*	m_pCompiledData;
	uint	m_compiledDataSize;

	QString m_fileName;
	bool m_save;

	EFFECT_PROFILE m_profile;
	DWORD m_effectFlags;
	DWORD m_shaderFlags;

	IncludeHandler m_includeHandler;

	HRESULT m_result;
	QVector<CompilerError> m_errors;

	bool m_idle;
	bool m_terminate;

	HANDLE m_thread;
	HANDLE m_startEvent;

	void Reset();

public:
	AsyncCompiler();
	~AsyncCompiler();

	char* assembly;
	int size;

	inline ID3DInclude* GetIncludeHandler() { return &m_includeHandler; }

	void SetSave(bool save);
	inline bool GetSave() { return m_save; }

	void SetData(void* pData, uint size);
	UINT GetData(void** pDest);

	void AddHeaderData(const QString& filename, const HEADER_DATA& data);
	void RemoveHeaderData( const QString& filename );

	void SetCompiledData(void*, uint size);
	UINT GetCompiledData(void** pDest);

	void SetResult(HRESULT result);
	inline HRESULT GetResult() { return m_result; }

	inline QVector<CompilerError> GetErrors() { return m_errors; }
	void SetErrors(QVector<CompilerError> errors);

	inline bool Terminating() { return m_terminate; }
	void Terminate();

	inline bool Idle() { return m_idle; }
	void SetIdle(bool idle);

	void SetEvent();
	inline HANDLE GetEvent() { return m_startEvent; }

	inline QVector<QString> GetIncludeDirectories() { return m_includeHandler.GetDirectories(); }
	inline QString GetLocalDirectory() { return m_includeHandler.GetLocalDirectory();}
	void SetIncludeDirectories(QVector<QString> directories);
	void SetLocalDirectory(QString directory);

	inline QString GetFilename() { return m_fileName; }
	void SetFilename(QString filename );

	bool Compile(ThreadSafe<AsyncCompiler>* pCompilerData);
	static DWORD WINAPI AsyncCompile(LPVOID pData);
	static QVector<CompilerError> AsyncParseCompilerOutput(QString outputToParse, QString filename);
};







