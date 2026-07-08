#include "DataLogger.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

// Pushes data into the vector
void DataLogger::pushData(double current_speed, double target_speed, double acceleration, double error) {
    VehicleState data_reading(current_speed,target_speed,acceleration, error);
    data.push_back(data_reading);
}

// Use this in main.cpp
void DataLogger::collectData(double current_speed, double target_speed, double acceleration, double error){
    pushData(current_speed, target_speed, acceleration, error);
}

// Function that creates the data report, format and all
void DataLogger::generateDataReport(const std::string& filename) const {

    std::ofstream outfile(filename); // Create output file object

    if (!outfile.is_open()) return; // Exit if file cannot be opened

    for (const VehicleState& data_print : data) {
        data_print.print(outfile); // Use VehicleSate.h's print() member function to print each formatted readings
    }
    outfile.close(); // ALWAYS close your files DAMNIT!
}