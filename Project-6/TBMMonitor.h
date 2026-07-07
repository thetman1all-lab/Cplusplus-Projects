#ifndef TBMMONITOR_H
#define TBMMONITOR_H

#include "SensorReading.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

class TBMMonitor {
private:

    // Vector to store all read data
    std::vector<SensorReading> readings;

    // Counters to keep track of itterations in loop
    int totalLoaded = 0;
    int totalSkipped = 0;
    int lineNumber = 0;

    // Function to read the data from file
    void readSingleFile(const std::string& filename);

public:
    // Function to load data file and access the private readSingleFile() function
    void loadFromFile(const std::string& filename);

    // Unsigned long number function to get the size of the vector after all valid data is collected=
    size_t getTotalRecords() const;

    // Function that creates the Critical readings report, format and all
    void generateCriticalReport(const std::string& filename) const;

    // Function to print a small summary to the terminal after data is collected and analyzed
    void printSummary() const;
};

#endif