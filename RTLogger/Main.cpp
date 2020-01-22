#include "Main.h"

int main()
{
	uint32_t cycleTime;
	cycleTime = 0;

	Logger* log = Logger::GetLogger();
	log->SetCycle(cycleTime);

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
		log->SetCycle(cycleTime);
		Sleep(0.001);
	}
	logMgrThread.join();
	return 0;
}

string time_in_HH_MM_SS_MMM()
{
	auto now = system_clock::now();
	auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;
	auto timer = system_clock::to_time_t(now);
	tm bt = *localtime(&timer);

	ostringstream oss;

	oss << put_time(&bt, "%H:%M:%S"); // HH:MM:SS
	oss << '.' << setfill('0') << setw(3) << ms.count();

	return oss.str();
}

