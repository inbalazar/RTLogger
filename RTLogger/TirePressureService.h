#ifndef __TIRE_PRESSURE_SERVICE_H
#define __TIRE_PRESSURE_SERVICE_H

#include "Logger.h"

class TirePressureService
{
public:
	void StartJob();
	static TirePressureService* GetInstance();
	~TirePressureService() {};

private:
	TirePressureService() {};
	TirePressureService(const TirePressureService& other) {};
	static TirePressureService* m_pclInstance;
	Logger* log;
};

#endif //__TIRE_PRESSURE_SERVICE_H