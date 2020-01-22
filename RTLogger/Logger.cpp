#include "Logger.h"

Logger* Logger::m_pclLoggerInstance;

void Logger::SendLoggerRTCritical(const char* msg, ...)
{
	if (p_stLoggerRTData->eLOGGER_RT_SEVERITYFromUI >= LOGGER_RT_SEVERITY_CRITICAL)
	{
		char buffer[256];
		char arrBuffer[256] = {};

		va_list arg;
		va_start(arg, msg);

		PrintfFormat(msg, buffer, arrBuffer, arg);

		va_end(arg);

		int ret = logMgr->Enqueue(p_stLoggerRTData->queueMsgs, arrBuffer, LOGGER_RT_SEVERITY_CRITICAL, cycleMsg);
		printf("\nEnqueue: %d, count: %d, msg: %s\n", ret, logMgr->CountQ(p_stLoggerRTData->queueMsgs), arrBuffer);
	}
}

void Logger::SendLoggerRTError(const char* msg, ...)
{
	if (p_stLoggerRTData->eLOGGER_RT_SEVERITYFromUI >= LOGGER_RT_SEVERITY_ERROR)
	{
		char buffer[256];
		char arrBuffer[256] = {};

		va_list arg;
		va_start(arg, msg);

		PrintfFormat(msg, buffer, arrBuffer, arg);

		va_end(arg);

		int ret = logMgr->Enqueue(p_stLoggerRTData->queueMsgs, arrBuffer, LOGGER_RT_SEVERITY_ERROR, cycleMsg);
		printf("\nEnqueue: %d, count: %d, msg: %s\n", ret, logMgr->CountQ(p_stLoggerRTData->queueMsgs), arrBuffer);
	}
}

void Logger::SendLoggerRTWarn(const char* msg, ...)
{
	if (p_stLoggerRTData->eLOGGER_RT_SEVERITYFromUI >= LOGGER_RT_SEVERITY_WARN)
	{
		char buffer[256];
		char arrBuffer[256] = {};

		va_list arg;
		va_start(arg, msg);

		PrintfFormat(msg, buffer, arrBuffer, arg);

		va_end(arg);

		int ret = logMgr->Enqueue(p_stLoggerRTData->queueMsgs, arrBuffer, LOGGER_RT_SEVERITY_WARN, cycleMsg);
		printf("\nEnqueue: %d, count: %d, msg: %s\n", ret, logMgr->CountQ(p_stLoggerRTData->queueMsgs), arrBuffer);
	}
}

void Logger::SendLoggerRTLog(const char* msg, ...)
{
	if (p_stLoggerRTData->eLOGGER_RT_SEVERITYFromUI >= LOGGER_RT_SEVERITY_LOG)
	{
		char buffer[256];
		char arrBuffer[256] = {};

		va_list arg;
		va_start(arg, msg);

		PrintfFormat(msg, buffer, arrBuffer, arg);

		va_end(arg);

		int ret = logMgr->Enqueue(p_stLoggerRTData->queueMsgs, arrBuffer, LOGGER_RT_SEVERITY_LOG, cycleMsg);
		printf("\nEnqueue: %d, count: %d, msg: %s\n", ret, logMgr->CountQ(p_stLoggerRTData->queueMsgs), arrBuffer);
	}
}

void Logger::SendLoggerRTFlow(const char* msg, ...)
{
	if (p_stLoggerRTData->eLOGGER_RT_SEVERITYFromUI >= LOGGER_RT_SEVERITY_FLOW)
	{
		char buffer[256];
		char arrBuffer[256] = {};

		va_list arg;
		va_start(arg, msg);

		PrintfFormat(msg, buffer, arrBuffer, arg);

		va_end(arg);

		int ret = logMgr->Enqueue(p_stLoggerRTData->queueMsgs, arrBuffer, LOGGER_RT_SEVERITY_FLOW, cycleMsg);
		printf("\nEnqueue: %d, count: %d, msg: %s\n", ret, logMgr->CountQ(p_stLoggerRTData->queueMsgs), arrBuffer);
	}
}

void Logger::SendLoggerRTInfo(const char* msg, ...)
{
	if (p_stLoggerRTData->eLOGGER_RT_SEVERITYFromUI >= LOGGER_RT_SEVERITY_INFO)
	{
		char buffer[256];
		char arrBuffer[256] = {};

		va_list arg;
		va_start(arg, msg);

		PrintfFormat(msg, buffer, arrBuffer, arg);

		va_end(arg);

		int ret = logMgr->Enqueue(p_stLoggerRTData->queueMsgs, arrBuffer, LOGGER_RT_SEVERITY_INFO, cycleMsg);
		printf("\nEnqueue: %d, count: %d, msg: %s\n", ret, logMgr->CountQ(p_stLoggerRTData->queueMsgs), arrBuffer);
	}
}

void Logger::SendLoggerRTDebug(const char* msg, ...)
{
	if (p_stLoggerRTData->eLOGGER_RT_SEVERITYFromUI >= LOGGER_RT_SEVERITY_DEBUG)
	{
		char buffer[256];
		char arrBuffer[256] = {};

		va_list arg;
		va_start(arg, msg);

		PrintfFormat(msg, buffer, arrBuffer, arg);

		va_end(arg);
		
		int ret = logMgr->Enqueue(p_stLoggerRTData->queueMsgs, arrBuffer, LOGGER_RT_SEVERITY_DEBUG, cycleMsg);
		printf("\nEnqueue: %d, count: %d, msg: %s\n", ret, logMgr->CountQ(p_stLoggerRTData->queueMsgs),arrBuffer);
	}
}

Logger* Logger::GetLogger()
{
	return m_pclLoggerInstance = new Logger();
}

void Logger::Init(const char* serviceName)
{	 
	p_stLoggerRTData = logMgr->Registerservice(serviceName);
}

void Logger::PrintfFormat(const char* msg, char* buffer, char* arrBuffer, va_list arg)
{
	const char* traverse;
	unsigned int i;
	char* s;
	float f;

	for (traverse = msg; *traverse != '\0'; traverse++)
	{
		while (*traverse != '%')
		{
			sprintf(buffer, "%c", *traverse);
			traverse++;
			strcat(arrBuffer, buffer);
			if (*traverse == '\0')
				break;
		}
		traverse++;

		switch (*traverse)
		{
		case 'c': i = va_arg(arg, int); //Fetch char argument
			sprintf(buffer, "%c", i);
			break;

		case 'd': i = va_arg(arg, int); //Fetch Decimal/Integer argument
			sprintf(buffer, "%i", i);
			break;

		case 'f':
		{
			f = va_arg(arg, double);		//Fetch Float argument 
			char str[100];
			const char* tmpSign = ((f) < 0) ? "-" : "";
			float tmpVal = (f < 0) ? -f : f;

			int tmpInt1 = tmpVal;                  // Get the integer (678).
			float tmpFrac = tmpVal - tmpInt1;      // Get fraction (0.0123).
			int tmpInt2 = trunc(tmpFrac * 10000);  // Turn into integer (123).

			sprintf(buffer, "%s%d.%04d", tmpSign, tmpInt1, tmpInt2);
		}
		break;

		case 's': s = va_arg(arg, char*); //Fetch string
			sprintf(buffer, "%s", s);
			break;
		}
		strcat(arrBuffer, buffer);
	}
}

void Logger::SetCycle(uint32_t cycle)
{
	cycleMsg = cycle;
}
