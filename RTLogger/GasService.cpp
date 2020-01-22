#include "GasService.h"

GasService* GasService::m_pclInstance;

void GasService::StartJob()
{
	log = Logger::GetLogger();
	log->Init("Gas");

	int i = 0;

	while (true)
	{
		if (i < 100)
		{
			Sleep(1000);
			log->SendLoggerRTCritical("Gas service unable to start!");
			log->SendLoggerRTError("Gas service unable to start!");
			log->SendLoggerRTWarn("Gas service unable to start!");
			log->SendLoggerRTLog("Gas service unable to start!");
			log->SendLoggerRTFlow("Gas service unable to start!");
			log->SendLoggerRTInfo("Gas service unable to start!");
			log->SendLoggerRTDebug("Gas service unable to start!");

			++i;
		}
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