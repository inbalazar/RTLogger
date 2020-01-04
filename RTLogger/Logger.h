#ifndef __LOGGER_H
#define __LOGGER_H

#include "DataTypes.h"
#include <cstdio> 
#include <cwchar>
#include <stdio.h>
#include <wchar.h>
#include "LoggerMgr.h"

#pragma warning(disable:4996)

class Logger
{
	public:
	Logger() { logMgr = LoggerMgr::GetInstance(); };
	~Logger() { };
	void init(const char* deviceName);
	void printfFormat(const char* msg, char* buffer, char* arrBuffer, va_list arg);

	void sendLoggerRTCritical(char* msg);
	void sendLoggerRTError(char* msg);
	void sendLoggerRTWarn(char* msg);
	void sendLoggerRTLog(char* msg);
	void sendLoggerRTFlow(char* msg);
	void sendLoggerRTInfo(char* msg);
	void sendLoggerRTDebug(const char* msg, ...);

private:
	LoggerMgr::stLoggerRTData* p_stLoggerRTData;
	LoggerMgr* logMgr;
};

#endif // __LOGGER_H

