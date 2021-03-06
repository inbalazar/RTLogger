#include "LoggerMgr.h"
#include "DatagramSocket.h"

LoggerMgr* LoggerMgr::m_pclInstance;
const char* LoggerMgr::LOGGER_RT_SEVERITY_STR[] = { "CRITICAL", "ERROR", "WARN", "LOG", "FLOW", "INFO", "DEBUG" };
const char* LoggerMgr::LOGGER_RT_SERVICE_STR[] = { "Gas", "ClimateControl", "TirePressure" };


LoggerMgr::LoggerMgr()
{
	m_stArrLoggerRTData->eLoggerRTService;
	m_stArrLoggerRTData->eLOGGER_RT_SEVERITYFromUI;
	m_stArrLoggerRTData->queueMsgs = NULL;
	studp_Received_Severity.serviceMsg = LOGGER_RT_GAS_SERVICE;
	studp_Received_Severity.severityMsg = LOGGER_RT_SEVERITY_CRITICAL;

	for (int i = 0; i < sizeof(m_stArrLoggerRTData) / sizeof(LoggerRTData); i++)
	{
		m_stArrLoggerRTData[i].queueMsgs = CreateQueue(100);
	}
	// Init LoggerMgr threads
	logMgrThread = thread(&LoggerMgr::StartProcess, this);
	logMgrThreadReceive = thread(&LoggerMgr::ReceiveSeverityFromUI, this);
}

LoggerMgr::queue* LoggerMgr::CreateQueue(int maxSize)
{
	queue* q = (queue*)operator new (sizeof(queue));

	q->head = 0;
	q->tail = 0;
	q->maxSize = maxSize + 1;
	unsigned int charArrSize = q->maxSize * MAX_ELEMENT_SIZE;

	q->msgsElements.textMsg = new char[charArrSize];
	memset(q->msgsElements.textMsg, 0, charArrSize);
	q->msgsElements.severityMsg = new LOGGER_RT_SEVERITY[charArrSize];
	q->msgsElements.cycle = new uint32_t[charArrSize];

	return q;
}

void LoggerMgr::FreeQueue(queue* q)
{
	delete[]q->msgsElements.textMsg;
	delete[]q;
}

int LoggerMgr::Enqueue(queue* q, char* element, LOGGER_RT_SEVERITY eSeverity, uint32_t cycleMsg)
{
	int nextTail = (q->tail + 1) % q->maxSize;
	if (nextTail == q->head)
	{
		return -1;
	}

	memset(&q->msgsElements.textMsg[q->tail * MAX_ELEMENT_SIZE], 0, MAX_ELEMENT_SIZE);
	strncpy(&q->msgsElements.textMsg[q->tail * MAX_ELEMENT_SIZE], element, MAX_ELEMENT_SIZE);

	q->msgsElements.severityMsg[q->tail * MAX_ELEMENT_SIZE] = eSeverity;
	q->msgsElements.cycle[q->tail * MAX_ELEMENT_SIZE] = cycleMsg;

	q->tail = nextTail;
	return 1;
}

char* LoggerMgr::Dequeue(LoggerMgr::queue* q)
{
	if (q->head == q->tail) {
		return NULL;
	}
	int head = q->head;
	q->head = (q->head + 1) % q->maxSize;

	return &q->msgsElements.textMsg[head * MAX_ELEMENT_SIZE];
}

unsigned int LoggerMgr::CountQ(LoggerMgr::queue* q)
{
	if (q->head <= q->tail)
	{
		return q->tail - q->head;
	}
	else
	{
		return q->maxSize - (q->head - q->tail);
	}
}

LoggerMgr* LoggerMgr::GetInstance()
{
	if (m_pclInstance == NULL)
	{
		m_pclInstance = new LoggerMgr();
	}
	return m_pclInstance;
}


void LoggerMgr::SendToLoggerDisplay(data_Send_To_UI* msg)
{
	char ipAdress[] = "127.0.0.1";
	DatagramSocket* s = new DatagramSocket(5001, ipAdress, TRUE, TRUE);
	UDP_Data_Send dataToSend = UDP_Data_Send();

	dataToSend.severityMsg = *msg->elementMsg.severityMsg;
	dataToSend.serviceMsg = msg->serviceMsg;
	dataToSend.cycle = *msg->elementMsg.cycle;

	strncpy(dataToSend.textMsg, msg->elementMsg.textMsg, strlen(msg->elementMsg.textMsg));

	s->send((char*)&dataToSend, sizeof(dataToSend));
}

void LoggerMgr::ReceiveSeverityFromUI()
{
	char ipAdress[] = "127.0.0.1";
	DatagramSocket* s = new DatagramSocket(5010, ipAdress, FALSE, FALSE);

	while (true)
	{
		int rec = s->receive((char*)&studp_Received_Severity, 8);
		m_stArrLoggerRTData[studp_Received_Severity.serviceMsg].eLOGGER_RT_SEVERITYFromUI =
			studp_Received_Severity.severityMsg;
	}
}

void LoggerMgr::StartProcess()
{
	int counterMsg[LOGGER_RT_NUM_OF_SERVICES];
	for (int i = 0; i < LOGGER_RT_NUM_OF_SERVICES; i++)
		counterMsg[i] = 0;

	while (true) //Main loop cycle 60Hz
	{
		auto start = std::chrono::high_resolution_clock::now();

		for (int i = 0; i < LOGGER_RT_NUM_OF_SERVICES; i++)
		{
			if (counterMsg[i] <= MAX_MSG_TO_SEND) //counter msgs until MAX_MSG_TO_SEND each service
			{
				if (CountQ(m_stArrLoggerRTData[i].queueMsgs) >= 0)
				{
					for (int j = 0; j < CountQ(m_stArrLoggerRTData[i].queueMsgs); j++)
					{
						char* msg =
							&m_stArrLoggerRTData[i].queueMsgs->msgsElements.textMsg[m_stArrLoggerRTData[i].queueMsgs->head * MAX_ELEMENT_SIZE];
						LOGGER_RT_SEVERITY severity =
							m_stArrLoggerRTData[i].queueMsgs->msgsElements.severityMsg[m_stArrLoggerRTData[i].queueMsgs->head * MAX_ELEMENT_SIZE];
						uint32_t cycleSend =
							m_stArrLoggerRTData[i].queueMsgs->msgsElements.cycle[m_stArrLoggerRTData[i].queueMsgs->head * MAX_ELEMENT_SIZE];

						element_In_Q stElement;
						stElement.textMsg = msg;
						stElement.severityMsg = &severity;
						stElement.cycle = &cycleSend;

						data_Send_To_UI stDataSend;
						stDataSend.elementMsg = stElement;
						stDataSend.serviceMsg = m_stArrLoggerRTData[i].eLoggerRTService;

						if (msg != NULL || msg != "")
						{
							SendToLoggerDisplay(&stDataSend);
						}

						char* deleteMsg = Dequeue(m_stArrLoggerRTData[i].queueMsgs);
						++counterMsg[i];

						printf("\nDequeue: %s, count: %d\n", stDataSend.elementMsg.textMsg, CountQ(m_stArrLoggerRTData[i].queueMsgs));
						printf("\nDequeue: %s, severity: %s\n", stElement.textMsg, LOGGER_RT_SEVERITY_STR[*stDataSend.elementMsg.severityMsg]);
						printf("\nDequeue: %s, service: %s\n", stElement.textMsg, LOGGER_RT_SERVICE_STR[stDataSend.serviceMsg]);
						printf("\nDequeue: %s, cycle: %d\n", stElement.textMsg, *stDataSend.elementMsg.cycle);

					}
				}
			}
		}

		auto endLoop = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> deltaTime = endLoop - start;
		auto intEndLoop_ms = std::chrono::duration_cast<std::chrono::milliseconds>(endLoop - start);
		//std::cout << "deltaTime: " << deltaTime.count() << " ms, " << std::endl;

#ifdef WIN32
		Sleep(MILLISECONDS_TO_60_HZ - ((double)deltaTime.count()));

#else 
		usleep(MICROSECONDS_TO_60_HZ - ((double)deltaTime.count() * 1000));

#endif
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double, std::milli> elapsed = end - start;
		auto intEnd_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
		//std::cout << "elapsed:  " << elapsed.count() << " ms, " << std::endl;

	}
}

LoggerMgr::stLoggerRTData* LoggerMgr::Registerservice(const char* serviceName)
{
	if (strcmp(serviceName, "Gas") == 0)
	{
		m_stArrLoggerRTData[LOGGER_RT_GAS_SERVICE].eLoggerRTService = LOGGER_RT_GAS_SERVICE;
		m_stArrLoggerRTData[LOGGER_RT_GAS_SERVICE].eLOGGER_RT_SEVERITYFromUI = LOGGER_RT_SEVERITY_CRITICAL;
		return &m_stArrLoggerRTData[LOGGER_RT_GAS_SERVICE];
	}

	else if (strcmp(serviceName, "ClimateControl") == 0)
	{
		m_stArrLoggerRTData[LOGGER_RT_CLIMATE_CONTROL_SERVICE].eLoggerRTService = LOGGER_RT_CLIMATE_CONTROL_SERVICE;
		m_stArrLoggerRTData[LOGGER_RT_CLIMATE_CONTROL_SERVICE].eLOGGER_RT_SEVERITYFromUI = LOGGER_RT_SEVERITY_CRITICAL;
		return &m_stArrLoggerRTData[LOGGER_RT_CLIMATE_CONTROL_SERVICE];
	}
	else if (strcmp(serviceName, "TirePressure") == 0)
	{
		m_stArrLoggerRTData[LOGGER_RT_TIRE_PRESSURE_SERVICE].eLoggerRTService = LOGGER_RT_TIRE_PRESSURE_SERVICE;
		m_stArrLoggerRTData[LOGGER_RT_TIRE_PRESSURE_SERVICE].eLOGGER_RT_SEVERITYFromUI = LOGGER_RT_SEVERITY_CRITICAL;
		return &m_stArrLoggerRTData[LOGGER_RT_TIRE_PRESSURE_SERVICE];
	}

	return NULL;
}


