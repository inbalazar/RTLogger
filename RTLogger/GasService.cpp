#include "GasService.h"

GasService* GasService::m_pclInstance;

void GasService::StartJob()
{
	log = Logger::GetLogger();
	log->Init("Gas");

	while (true)
	{
		
#ifdef WIN32
		Sleep(1000);
#else 
		sleep(1);
#endif
		log->SendLoggerRTCritical("Gas service enable to start!");
		log->SendLoggerRTError("Gas service enable to start!");
		log->SendLoggerRTWarn("Gas service enable to start!");
		log->SendLoggerRTLog("Gas service enable to start!");
		log->SendLoggerRTFlow("Gas service enable to start!");
		log->SendLoggerRTInfo("Gas service enable to start!");
		log->SendLoggerRTDebug("Gas service enable to start!");
		

#ifdef WIN32
		Sleep(1000);
#else 
		sleep(1);
#endif
	}
}

GasService* GasService::GetInstance()
{
	if (m_pclInstance == NULL)
	{
		m_pclInstance = new GasService();
	}
	return m_pclInstance;
}
