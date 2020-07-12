
#include "Main.h"
#include <stdio.h>
#ifdef WIN32
	#include <stdlib.h>
#else
	#include <pthread.h>
#endif

uint32_t cycleTime;

int main()
{
	cycleTime = 0;

	Logger* log = Logger::GetLogger();

	LoggerMgr* logMgr = LoggerMgr::GetInstance();

	// Init system services 
	GasService* gasService = GasService::GetInstance();
	thread gasServiceThread(&GasService::StartJob, gasService);

	ClimateControlService* climateControlService = ClimateControlService::GetInstance();
	thread climateControlServiceThread(&ClimateControlService::StartJob, climateControlService);

	TirePressureService* tirePressureService = TirePressureService::GetInstance();
	thread tirePressureServiceThread(&TirePressureService::StartJob, tirePressureService);

	// Main loop of CCU- demo of an app that do action that takes time
	while (true)
	{
		cycleTime += 1;

		#ifdef WIN32
			Sleep(0.001);
		#else 
			sleep(0.000001);
		#endif
	}
	return 0;
}

uint32_t GetCycle()
{
	return cycleTime;
}

