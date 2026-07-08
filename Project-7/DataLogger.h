#ifndef DATALOGGER_H
#define DATALOGGER_H

#include "VehicleState.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

class DataLogger {
private:

    // Vector of doubles of the current speed, target speed, and acceleration
    std::vector<VehicleState> data;

    void pushData(double current_speed, double target_speed, double acceleration, double error);

public:

    void collectData(double current_speed, double target_speed, double acceleration, double error);

    // Function that creates the data report, format and all
    void generateDataReport(const std::string& filename) const;

};


#endif