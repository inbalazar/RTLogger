#ifndef __CLIMATE_CONTROL_SERVICE_H
#define __CLIMATE_CONTROL_SERVICE_H

#include "Logger.h"

class ClimateControlService
{
public:
	void StartJob();
	static ClimateControlService* GetInstance();
	~ClimateControlService() {};

private:
	ClimateControlService() {};
	ClimateControlService(const ClimateControlService& other) {};
	static ClimateControlService* m_pclInstance;
	Logger* log;
};
#endif//__CLIMATE_CONTROL_SERVICE_H
