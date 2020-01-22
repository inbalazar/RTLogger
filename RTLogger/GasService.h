#ifndef __GAS_SERVICE_H
#define __GAS_SERVICE_H

#include "Logger.h"

class GasService
{
public:
	void StartJob();
	static GasService* GetInstance();
	~GasService() {};

private:
	GasService() {};
	GasService(const GasService& other) {};
	static GasService* m_pclInstance;
	Logger* log;
};
#endif//__GAS_SERVICE_H

