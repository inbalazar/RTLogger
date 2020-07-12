#include "ClimateControlService.h"

ClimateControlService* ClimateControlService::m_pclInstance;

void ClimateControlService::StartJob()
{
	log = Logger::GetLogger();
	log->Init("ClimateControl");

	while (true)
	{
		log->SendLoggerRTCritical("Climate control service enable to start!");
		log->SendLoggerRTError("Climate control service enable to start!");
		log->SendLoggerRTWarn("Climate control service enable to start!");
		log->SendLoggerRTLog("Climate control service enable to start!");
		log->SendLoggerRTFlow("Climate control service enable to start!");
		log->SendLoggerRTInfo("Climate control service enable to start!");
		log->SendLoggerRTDebug("Climate control service enable to start!");

#ifdef WIN32
			Sleep(2000);
#else 
			sleep(2);
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

