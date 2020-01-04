#include "Logger.h"

void Logger::sendLoggerRTCritical(char* msg)
{
}

void Logger::sendLoggerRTError(char* msg)
{
}

void Logger::sendLoggerRTWarn(char* msg)
{
}

void Logger::sendLoggerRTLog(char* msg)
{
}

void Logger::sendLoggerRTFlow(char* msg)
{
}

void Logger::sendLoggerRTInfo(char* msg)
{
}

void Logger::sendLoggerRTDebug(const char* msg, ...)
{
	p_stLoggerRTData->eLoggerRTSeverityFromUI = LoggerRTSeverityWarn; // need to remove!!!
	if (p_stLoggerRTData->eLoggerRTSeverityFromUI >= LoggerRTSeverityWarn)
	{
		char buffer[256];
		char arrBuffer[256] = {};

		va_list arg;
		va_start(arg, msg);

		printfFormat(msg, buffer, arrBuffer, arg);

		va_end(arg);

		//p_stLoggerRTData->eLoggerRTSeverity = LoggerRTSeverityDebug;
		
		int ret = logMgr->enqueue(p_stLoggerRTData->queueMsgs, arrBuffer, LoggerRTSeverityDebug);
		printf("\nenqueue: %d, count: %d, msg: %s\n", ret, logMgr->count(p_stLoggerRTData->queueMsgs),arrBuffer);
		//printf("%d", LoggerMgr::GetInstance()->count(p_stLoggerRTData->queueMsgs));
	}
}

void Logger::init(const char* deviceName)
{	 
	p_stLoggerRTData = logMgr->registerDevice(deviceName);
}

void Logger::printfFormat(const char* msg, char* buffer, char* arrBuffer, va_list arg)
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