#include "DataLogger.h"
#include <iostream>

void DataLogger::pushData(double current_speed, double target_speed, 
                          double acceleration, double error) {
    data.push_back({current_speed, target_speed, acceleration, error});
}

void DataLogger::collectData(double current_speed, double target_speed, 
                             double acceleration, double error) {
    pushData(current_speed, target_speed, acceleration, error);
}

void DataLogger::generateDataReport(const std::string& filename) const {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) {
        std::cerr << "Error: Could not open file " << filename << "\n";
        return;
    }

    // Write header
    outfile << "current_speed,target_speed,acceleration,error\n";

    for (const auto& entry : data) {
        outfile << entry.current_speed << ","
                << entry.target_speed << ","
                << entry.acceleration << ","
                << entry.error << "\n";
    }

    outfile.close();
}