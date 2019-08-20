/*
	File Name	: Log.h

	Description	: log

	Programmer	: download from net

	Make Date	: 2010-0111
                  liu.j.l 2010.02.10 for the bug file cannot be found when Far Run @11125

	Change		: 
*/
#ifndef _LOG_H
#define _LOG_H

class CLog
{
public:
	CLog();
	~CLog();

public:
	void	InitLog(LPCTSTR lpszLogPath);		
	void	Add(const char* fmt, ...);		
	
protected:
	enum {BUFSIZE = 3000};  
	char		m_tBuf[BUFSIZE];
	
	CString	 m_strLogPath;
	CRITICAL_SECTION  m_crit;  
};
extern CLog g_Log;


#endif