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

class LoggerMgr
{
public:
	typedef struct queueStru {
		std::atomic<unsigned int> head;
		std::atomic<unsigned int> tail;
		unsigned int maxSize;
		element_In_Q msgsElements;
	} queue;

	typedef struct LoggerRTData
	{
		LOGGER_RT_SEVERITY eLOGGER_RT_SEVERITYFromUI;
		LOGGER_RT_SERVICE eLoggerRTDivece;
		queue* queueMsgs;
	}stLoggerRTData;

	stLoggerRTData m_stArrLoggerRTData[LOGGER_RT_NUM_OF_SERVICES];
	udp_Received_Severity studp_Received_Severity;

	static const char* LOGGER_RT_SEVERITY_STR[LOGGER_RT_NUM_OF_SEVERITY];
	static const char* LOGGER_RT_SERVICE_STR[LOGGER_RT_NUM_OF_SERVICES];

	static LoggerMgr* GetInstance();
	~LoggerMgr() {};
	void SendToLoggerDisplay(data_Send_To_UI* msg);
	void ReceiveSeverityFromUI();
	void StartProcess();
	stLoggerRTData* Registerservice(const char* serviceName);

	//Lockless
	queue* CreateQueue(int maxSize);
	void FreeQueue(queue* q);
	int Enqueue(queue* q, char* element, LOGGER_RT_SEVERITY eSeverity, uint32_t cycleMsg);
	char* Dequeue(queue* q);
	unsigned int CountQ(queue* q);

private: 
	static LoggerMgr* m_pclInstance;
	LoggerMgr();
	LoggerMgr(const LoggerMgr& other) {};
};
#endif // __LOGGERMGR_H
