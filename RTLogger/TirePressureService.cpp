#include "TirePressureService.h"

TirePressureService* TirePressureService::m_pclInstance;

void TirePressureService::StartJob()
{
	log = Logger::GetLogger();
	log->Init("TirePressure");

	while (true)
	{
		log->SendLoggerRTCritical("Tire pressure service enable to start!");
		log->SendLoggerRTError("Tire pressure service enable to start!");
		log->SendLoggerRTWarn("Tire pressure service enable to start!");
		log->SendLoggerRTLog("Tire pressure service enable to start!");
		log->SendLoggerRTFlow("Tire pressure service enable to start!");
		log->SendLoggerRTInfo("Tire pressure service enable to start!");
		log->SendLoggerRTDebug("Tire pressure service enable to start!");

#ifdef WIN32
		Sleep(2000);
#else 
		usleep(2000000);
#endif
	}	
}

TirePressureService* TirePressureService::GetInstance()
{
	if (m_pclInstance == NULL)
	{
		m_pclInstance = new TirePressureService();
	}
	return m_pclInstance;
}


