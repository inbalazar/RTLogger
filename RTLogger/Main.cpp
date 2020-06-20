
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
	thread logMgrThread(&LoggerMgr::StartProcess, logMgr); 
	thread logMgrThreadReceive(&LoggerMgr::ReceiveSeverityFromUI, logMgr);

	GasService* gasService = GasService::GetInstance();
	thread gasServiceThread(&GasService::StartJob, gasService);

	ClimateControlService* climateControlService = ClimateControlService::GetInstance();
	thread climateControlServiceThread(&ClimateControlService::StartJob, climateControlService);

	TirePressureService* tirePressureService = TirePressureService::GetInstance();
	thread tirePressureServiceThread(&TirePressureService::StartJob, tirePressureService);

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

//string time_in_HH_MM_SS_MMM()
//{
//	auto now = system_clock::now();
//	auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
//	auto timer = system_clock::to_time_t(now);
//	tm bt = *localtime(&timer);
//
//	ostringstream oss;
//
//	oss << put_time(&bt, "%H:%M:%S"); // HH:MM:SS
//	oss << '.' << setfill('0') << setw(3) << ms.count();
//
//	return oss.str();
//}

