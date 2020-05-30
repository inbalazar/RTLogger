#include "TirePressureService.h"

TirePressureService* TirePressureService::m_pclInstance;

void TirePressureService::StartJob()
{
	log = Logger::GetLogger();
	log->Init("TirePressure");


	while (true)
	{
		
	#ifdef WIN32
		Sleep(1000);
#else 
		sleep(1000);
#endif
		log->SendLoggerRTCritical("Tire pressure service unable to start!");
		log->SendLoggerRTError("Tire pressure service unable to start!");
		log->SendLoggerRTWarn("Tire pressure service unable to start!");
		log->SendLoggerRTLog("Tire pressure service unable to start!");
		log->SendLoggerRTFlow("Tire pressure service unable to start!");
		log->SendLoggerRTInfo("Tire pressure service unable to start!");
		log->SendLoggerRTDebug("Tire pressure service unable to start!");

#ifdef WIN32
		Sleep(1000);
#else 
		sleep(1000);
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


