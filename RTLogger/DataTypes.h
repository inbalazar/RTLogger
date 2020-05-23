#ifndef __DATATYPE_H
#define __DATATYPE_H

#include<stdarg.h>
#include <iostream>
#include <string>
using namespace std;

#define MAX_SIZE_MESSAGE 100
#define MAX_ELEMENT_SIZE 50 + 1
#define MAX_MSG_TO_SEND 100
#define MILLISECONDS_TO_60_HZ 0.01666667


enum LOGGER_RT_SEVERITY
{
	LOGGER_RT_SEVERITY_CRITICAL,
	LOGGER_RT_SEVERITY_ERROR,
	LOGGER_RT_SEVERITY_WARN,
	LOGGER_RT_SEVERITY_LOG,
	LOGGER_RT_SEVERITY_FLOW,
	LOGGER_RT_SEVERITY_INFO,
	LOGGER_RT_SEVERITY_DEBUG,

	LOGGER_RT_NUM_OF_SEVERITY
};

enum LOGGER_RT_SERVICE
{
	LOGGER_RT_GAS_SERVICE,
	LOGGER_RT_CLIMATE_CONTROL_SERVICE,
	LOGGER_RT_TIRE_PRESSURE_SERVICE,

	LOGGER_RT_NUM_OF_SERVICES
};

typedef struct Element_In_Q {
	LOGGER_RT_SEVERITY* severityMsg;
	char* textMsg;
	uint32_t* cycle;
} element_In_Q;

typedef struct Data_Send_To_UI {
	element_In_Q elementMsg;
	LOGGER_RT_SERVICE serviceMsg;
} data_Send_To_UI;

typedef struct UDP_Data_Send {
	uint32_t cycle;
	LOGGER_RT_SEVERITY severityMsg;
	LOGGER_RT_SERVICE serviceMsg;
	char textMsg[MAX_SIZE_MESSAGE];
} udp_Data_Send;

typedef struct UDP_Received_Severity {
	LOGGER_RT_SEVERITY severityMsg;
	LOGGER_RT_SERVICE serviceMsg;
} udp_Received_Severity;

#endif // __DATATYPE_H