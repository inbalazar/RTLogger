#include "ClimateControlService.h"

ClimateControlService* ClimateControlService::m_pclInstance;

void ClimateControlService::StartJob()
{
	log = Logger::GetLogger();
	log->Init("ClimateControl");

	while (true)
	{

#ifdef WIN32
		Sleep(1000);
#else 
		sleep(1000);
#endif
			log->SendLoggerRTCritical("Climate control service unable to start!");
			log->SendLoggerRTError("Climate control service unable to start!");
			log->SendLoggerRTWarn("Climate control service unable to start!");
			log->SendLoggerRTLog("Climate control service unable to start!");
			log->SendLoggerRTFlow("Climate control service unable to start!");
			log->SendLoggerRTInfo("Climate control service unable to start!");
			log->SendLoggerRTDebug("Climate control service unable to start!");

#ifdef WIN32
			Sleep(1000);
#else 
			sleep(1000);
#endif
	}
}

ClimateControlService* ClimateControlService::GetInstance()
{
	if (m_pclInstance == NULL)
	{
		m_pclInstance = new ClimateControlService();
	}
	return m_pclInstance;
}

