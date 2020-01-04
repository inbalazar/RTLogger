#include "LoggerMgr.h"
#include "DatagramSocket.h"

LoggerMgr* LoggerMgr::m_pclInstance;
const char* LoggerMgr::LoggerRTSeverityStr[] = { "Critical","Error","Warn","Log","Flow","Info","Debug" };
const char* LoggerMgr::LoggerRTDiveceStr[] = { "CCU" };

LoggerMgr::LoggerMgr()
{
	for (int i = 0; i < sizeof(m_stArrLoggerRTData) / sizeof(LoggerRTData); i++)
	{
		m_stArrLoggerRTData[i].queueMsgs= createQueue(1000);
	}
}

LoggerMgr::queue* LoggerMgr::createQueue(int maxSize) 
{
	queue* q = new queue[sizeof(queue)];
	q->head = 0;
	q->tail = 0;
	q->maxSize = maxSize + 1;
	unsigned int charArrSize = q->maxSize * MAX_ELEMENT_SIZE;
	q->msgsElements.textMsg = new char[charArrSize];
	memset(q->msgsElements.textMsg, 0, charArrSize);

	q->msgsElements.severityMsg = new LoggerRTSeverity[charArrSize];

	return q;
}

void LoggerMgr::freeQueue(queue* q) 
{
	delete []q->msgsElements.textMsg;
	delete []q->msgsElements.severityMsg;
	delete []q;
}

int LoggerMgr::enqueue(queue* q, char* element, LoggerRTSeverity eSeverity) 
{
	int nextTail = (q->tail + 1) % q->maxSize;
	if (nextTail == q->head) 
	{
		return -1;
	}

	memset(&q->msgsElements.textMsg[q->tail * MAX_ELEMENT_SIZE], 0, MAX_ELEMENT_SIZE);
	strncpy(&q->msgsElements.textMsg[q->tail * MAX_ELEMENT_SIZE], element, MAX_ELEMENT_SIZE);

	q->msgsElements.severityMsg[q->tail * MAX_ELEMENT_SIZE] = eSeverity;

	q->tail = nextTail;
	return 1;
}

char* LoggerMgr::dequeue(LoggerMgr::queue* q) 
{
	if (q->head == q->tail) {
		return NULL;
	}
	int head = q->head;
	q->head = (q->head + 1) % q->maxSize;

	return &q->msgsElements.textMsg[head * MAX_ELEMENT_SIZE];
}

unsigned int LoggerMgr::count(LoggerMgr::queue* q) 
{
	if (q->head <= q->tail) {
		return q->tail - q->head;
	}
	else {
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
 

void LoggerMgr::init()
{
	//
}

void LoggerMgr::sendToLoggerDisplay(char* msg) 
{
	char ipAdress[] = "127.0.0.1";
	DatagramSocket* s = new DatagramSocket(5001, ipAdress, TRUE, TRUE);
	s->send(msg, strlen(msg));
}

void LoggerMgr::startProcess()
{
	while (true)
	{
		//printf("%s", m_stArrLoggerRTData[0].queueMsgs->elements);
		for (int i = 0; i < sizeof(m_stArrLoggerRTData) / sizeof(LoggerRTData); i++)
		{
			//printf(" !%d", count(m_stArrLoggerRTData[i].queueMsgs));
			//printf("\nsize: %d",sizeof(m_stArrLoggerRTData) / sizeof(LoggerRTData));
			
			if (count(m_stArrLoggerRTData[i].queueMsgs) != 0)
			{
				for (int j = 0; j < count(m_stArrLoggerRTData[i].queueMsgs); j++)
				{
					char* msg = 
						&m_stArrLoggerRTData[i].queueMsgs->msgsElements.textMsg[m_stArrLoggerRTData[i].queueMsgs->head * MAX_ELEMENT_SIZE];
					LoggerRTSeverity severity = 
						m_stArrLoggerRTData[i].queueMsgs->msgsElements.severityMsg[m_stArrLoggerRTData[i].queueMsgs->head * MAX_ELEMENT_SIZE];
					
					element stElement;// move to h file
					stElement.textMsg = msg;
					stElement.severityMsg = &severity;

					dataSend stDataSend;
					stDataSend.elementMsg = stElement;
					stDataSend.deviceMsg = m_stArrLoggerRTData[i].eLoggerRTDivece;

					if (msg != NULL||msg!="")
					{
						sendToLoggerDisplay((char*)(&stDataSend)); //need to send struct
					}
					else
					{
						//do nothing
					}
					char* msg2 = dequeue(m_stArrLoggerRTData[i].queueMsgs); //remove return
					/*printf("\ndequeue: %s, count: %d\n", msg, count(m_stArrLoggerRTData[i].queueMsgs));
					printf("\ndequeue: %s, severity: %s\n", msg, LoggerRTSeverityStr[severity]);*/

					printf("\ndequeue: %s, count: %d\n", stDataSend.elementMsg.textMsg, count(m_stArrLoggerRTData[i].queueMsgs));
					printf("\ndequeue: %s, severity: %s\n", stElement.textMsg, LoggerRTSeverityStr[*stDataSend.elementMsg.severityMsg]);
					printf("\ndequeue: %s, device: %s\n", stElement.textMsg, LoggerRTDiveceStr[stDataSend.deviceMsg]);
				}
			}
			
		}
	}
}

LoggerMgr::stLoggerRTData* LoggerMgr::registerDevice(const char* deviceName)
{
	if (deviceName == "CCU")
	{
		m_stArrLoggerRTData[LoggerRTCcu].eLoggerRTDivece = LoggerRTCcu;
		return &m_stArrLoggerRTData[LoggerRTCcu];
	}
	//else if -need to add
	
	return NULL;
}
