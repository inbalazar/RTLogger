#ifndef MAIN_H_
#define MAIN_H_

#include <iostream>
#include <string>
#include <ctime>
#include <chrono>
#include <time.h>
#include <iomanip>
#include <sstream>

#include "Logger.h"
#include "GasService.h"
#include "ClimateControlService.h"
#include "TirePressureService.h"

using namespace std;

uint32_t GetCycle();

#endif //MAIN_H_
