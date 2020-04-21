#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <time.h>
#include <iomanip>
#include <sstream>
#include <windows.h>
#include "Logger.h"
#include "GasService.h"
#include "ClimateControlService.h"
#include "TirePressureService.h"

using namespace std;
//using namespace std::chrono;

uint32_t GetCycle();
//string time_in_HH_MM_SS_MMM();

#endif //MAIN_H_
