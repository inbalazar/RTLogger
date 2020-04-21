#include "ClimateControlService.h"

ClimateControlService* ClimateControlService::m_pclInstance;

void ClimateControlService::StartJob()
{
	log = Logger::GetLogger();
	log->Init("ClimateControl");

	int i = 0;

	//while (true)
	//{
		while (i < 100)
		{
			Sleep(1000);
			log->SendLoggerRTCritical("Climate control service unable to start!");
			log->SendLoggerRTError("Climate control service unable to start!");
			log->SendLoggerRTWarn("Climate control service unable to start!");
			log->SendLoggerRTLog("Climate control service unable to start!");
			log->SendLoggerRTFlow("Climate control service unable to start!");
			log->SendLoggerRTInfo("Climate control service unable to start!");
			log->SendLoggerRTDebug("Climate control service unable to start!");

			++i;
		}
	//}
		Sleep(0.001);
}

ClimateControlService* ClimateControlService::GetInstance()
{
	if (m_pclInstance == NULL)
	{
		m_pclInstance = new ClimateControlService();
	}
	return m_pclInstance;
}

