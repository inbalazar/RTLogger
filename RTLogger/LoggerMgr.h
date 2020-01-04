#ifndef __LOGGERMGR_H
#define __LOGGERMGR_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <atomic>
#include <thread> 
#include "DataTypes.h"

#pragma comment(lib, "Ws2_32.lib")
//#define _CRT_SECURE_NO_WARNINGS
//#pragma warning(disable:4996)

#define MAX_ELEMENT_SIZE 50 + 1

using namespace std;

class LoggerMgr
{
public:
	typedef struct queueStru {
		std::atomic<unsigned int> head;
		std::atomic<unsigned int> tail;
		unsigned int maxSize;
		element msgsElements; //to do
		//char* elements;
	} queue;

	typedef struct LoggerRTData
	{
		LoggerRTSeverity eLoggerRTSeverityFromUI;
		LoggerRTDevice eLoggerRTDivece;
		queue* queueMsgs;
	}stLoggerRTData;

	stLoggerRTData m_stArrLoggerRTData[1]; //todo defult

	static const char* LoggerRTSeverityStr[7];// todo defult
	static const char* LoggerRTDiveceStr[1];// todo defult

	static LoggerMgr* GetInstance();
	~LoggerMgr() {};
	void init();
	void sendToLoggerDisplay(char* msg);
	void startProcess();
	stLoggerRTData* registerDevice(const char* deviceName);

	//Lockless
	queue* createQueue(int maxSize);
	void freeQueue(queue* q);
	int enqueue(queue* q, char* element, LoggerRTSeverity eSeverity);
	char* dequeue(queue* q);
	unsigned int count(queue* q);

private: 
	static LoggerMgr* m_pclInstance;
	LoggerMgr();
	LoggerMgr(const LoggerMgr& other) {};
};
#endif // __LOGGERMGR_H
