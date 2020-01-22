#ifndef __LOGGER_H
#define __LOGGER_H

#include "DataTypes.h"
#include <cstdio> 
#include <cwchar>
#include <stdio.h>
#include <wchar.h>
#include <windows.h>
#include "LoggerMgr.h"

#pragma warning(disable:4996)

class Logger
{
public:
	Logger() { logMgr = LoggerMgr::GetInstance(); };
	~Logger() { };

	static Logger* GetLogger();	
	void Init(const char* serviceName);
	void PrintfFormat(const char* msg, char* buffer, char* arrBuffer, va_list arg);
	void SetCycle(uint32_t cycle);

	void SendLoggerRTCritical(const char* msg, ...);
	void SendLoggerRTError(const char* msg, ...);
	void SendLoggerRTWarn(const char* msg, ...);
	void SendLoggerRTLog(const char* msg, ...);
	void SendLoggerRTFlow(const char* msg, ...);
	void SendLoggerRTInfo(const char* msg, ...);
	void SendLoggerRTDebug(const char* msg, ...);

private:
	static Logger* m_pclLoggerInstance;
	LoggerMgr::stLoggerRTData* p_stLoggerRTData;
	LoggerMgr* logMgr;
	uint32_t cycleMsg;
};

#endif // __LOGGER_H

