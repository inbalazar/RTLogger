#ifndef __DATATYPE_H
#define __DATATYPE_H

#include<stdarg.h>
#include <iostream>
#include <string>
using namespace std;

enum LoggerRTSeverity
{
	LoggerRTSeverityCritical,
	LoggerRTSeverityError,
	LoggerRTSeverityWarn,
	LoggerRTSeverityLog,
	LoggerRTSeverityFlow,
	LoggerRTSeverityInfo,
	LoggerRTSeverityDebug
};

//const char* LoggerRTSeverityStr[] = {"Critical","Error","Warn","Log","Flow","Info","Debug"};

enum LoggerRTDevice
{
	LoggerRTCcu,
	//add more
};

typedef struct elementStru {
	LoggerRTSeverity* severityMsg;
	char* textMsg;
} element;

typedef struct dataSendStru {
	element elementMsg;
	LoggerRTDevice deviceMsg;
} dataSend;

typedef struct udpDataStru {
	LoggerRTSeverity severityMsg;
	char textMsg[100];
} udpData;

#endif // __DATATYPE_H