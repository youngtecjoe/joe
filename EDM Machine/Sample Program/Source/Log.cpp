/*
	File Name	: Log.h

	Description	: log

	Programmer	: download from net

	Make Date	: 2010-0111
                  liu.j.l 2010.02.10 for the bug file cannot be found when Far Run @11125

	Change		: 
*/
#include "stdafx.h"
#include "log.h"

CLog g_Log;

CLog::CLog()  
{
	::InitializeCriticalSection(&m_crit);   
	m_strLogPath = "Mocxtest.log";
}


CLog::~CLog()
{
	::DeleteCriticalSection(&m_crit);    
}

void CLog::InitLog(LPCTSTR lpszLogPath)   
{	
	m_strLogPath=lpszLogPath;
}

void CLog::Add(const char* fmt, ...)
{
	if (m_strLogPath.IsEmpty())
		return ;
	
	if (!AfxIsValidString(fmt, -1))
		return ;
	::EnterCriticalSection(&m_crit);   
	try      
	{
		va_list argptr;          
		va_start(argptr, fmt);
		_vsnprintf(m_tBuf, BUFSIZE, fmt, argptr);
		va_end(argptr);
	}
	catch (...)
	{
		m_tBuf[0] = 0;
	}
	
	FILE *fp = fopen(m_strLogPath, "a"); 
	if (fp)
	{
		fprintf(fp,"%s:  ", AfxGetApp()->m_pszExeName);  
		
		CTime ct ;                          
		ct = CTime::GetCurrentTime();
		fprintf(fp,"%s : ",ct.Format("%m/%d/%Y %H:%M:%S"));
		fprintf(fp, "%s\n", m_tBuf);		
		fclose(fp);		
	}	
	::LeaveCriticalSection(&m_crit);  
}


