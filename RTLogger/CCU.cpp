#include "CCU.h"

int main()
{
	Logger* log = new Logger();
	log-> init("CCU");

	LoggerMgr* logMgr = LoggerMgr::GetInstance();
	logMgr->init();
	thread logMgrThread(&LoggerMgr::startProcess, logMgr);
	
	bool flag = true;
	int i = 0;

	while (true)
	{
		string sTime = time_in_HH_MM_SS_MMM();

		const char* cstr = sTime.c_str();

		log->sendLoggerRTDebug("%d--- time: %s", ++i, cstr);
		printf("\n%d--- time: %s", i, cstr);

		if (i == 3)
			break;
		//Sleep(1000);

		/*if (flag)
		{
			log->sendLoggerRTDebug("Start Engine%d!!!", 7);
			log->sendLoggerRTDebug("In process!!!");
			log->sendLoggerRTDebug("In pr%d", 6);
			log->sendLoggerRTDebug("%d", 6);
			log->sendLoggerRTDebug("%f", 6.8);
			log->sendLoggerRTDebug("%f%c Test string %d", 32.49, 'a', 4);
			log->sendLoggerRTDebug("%cTest string%d", 'a', 4);

			flag = false;
		}*/
	}
	logMgrThread.join();
	//delete logMgr;
	return 0;
}

string time_in_HH_MM_SS_MMM()
{
	// get current time
	auto now = system_clock::now();

	// get number of milliseconds for the current second
	// (remainder after division into seconds)
	auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

	// convert to std::time_t in order to convert to std::tm (broken time)
	auto timer = system_clock::to_time_t(now);

	// convert to broken time
	tm bt = *localtime(&timer);

	ostringstream oss;

	oss << put_time(&bt, "%H:%M:%S"); // HH:MM:SS
	oss << '.' << setfill('0') << setw(3) << ms.count();

	return oss.str();
}

