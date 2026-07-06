#include "TBMMonitor.h"
#include "SensorReading.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <algorithm>

// Function to read the data from file
void TBMMonitor::readSingleFile(const std::string& filename) {

    // Attempt to open file
    std::ifstream infile(filename);

    // Check if file is open and return an error message if it is not
    if(!infile.is_open()) {
        std::cerr << "Error: Cannot open file: " << filename << "\n";
        return;
    }

    // Make string variable for getline to use for each line
    std::string line;

    // Read and ignore the header line. No need to store it anywhere
    std::getline(infile, line);

    while (std::getline(infile, line)) {
        lineNumber++; // Increase line number count for every loop iteration

        if (line.empty() || line[0] == '#'){
            totalSkipped++; // Increase skipped lines count
            continue;
        }

        std::stringstream ss(line); // Allow the string line to be broken up into words
        std::string timestamp, segment_id, pressure_bar, temperature_C, vibration_level, status; // Make a string variable for each data variable to be stored into

        // Check if line parse values can actually be read or not
        if (!std::getline(ss, timestamp, ',') ||
            !std::getline(ss, segment_id, ',') ||
            !std::getline(ss, pressure_bar, ',') ||
            !std::getline(ss, temperature_C, ',') ||
            !std::getline(ss, vibration_level, ',') ||
            !std::getline(ss, status, ',')) {
                totalSkipped++; // Increase skipped lines count
                continue;
        }


        // Create number variables to store conversions into
        
        double pressure_double;
        double temperature_double;
        double vibration_double;

        // Create a lambda throw away function for running a try catch three times for the conversions
        auto tryParseConvert = [&] (const std::string& str, double& result) -> bool {
            try {
                result = std::stod(str); // Convert string number from getline to a double
                return true; // Successful conversion returns true
            } catch (...) {
                std::cout << "Invalid value at line " << lineNumber << "\n";
                totalSkipped++; // Increase skipped lines count
                return false; // Failed conversion with error returns false
            }
        };

        // Run Lambda functions for the three conversions. Will skip if invalid number
        if (!tryParseConvert(pressure_bar, pressure_double)) continue;
        if (!tryParseConvert(temperature_C, temperature_double)) continue;
        if (!tryParseConvert(vibration_level,vibration_double)) continue;

        // Once numbers are converted, pushback everything into the vector
        SensorReading file_reading(timestamp,
                                   segment_id,
                                   pressure_double,
                                   temperature_double,
                                   vibration_double,
                                   status);

        readings.push_back(file_reading);
        totalLoaded++; // Increase successful line readings loaded
    }
    infile.close();
};

// Public function to access the private readSingleFile() function
void TBMMonitor::loadFromFile(const std::string& filename) {
    readSingleFile(filename);
};

// Unsigned long number function to get the size of the vector after all valid data is collected=
size_t TBMMonitor::getTotalRecords() const {
    return readings.size();
};

// Function that creates the Critical readings report, format and all
void TBMMonitor::generateCriticalReport(const std::string& filename) const {

    std::ofstream outfile(filename); // Create output file object

    if (!outfile.is_open()) return; // Exit if file cannot be opened

    int criticalCount = 0;

    for (const SensorReading& read : readings) {
        if(read.isCritical()) {

            criticalCount++; // Increase the crittical counts

            read.print(outfile); // Use SensorReading.h's print() member function to print each formatted readings
            outfile << "------------------------------------------------------------\n";
        }
    }
    outfile << "Total WARNING records: " << criticalCount << "\n"; // Footer at end of report reads out how many criticals there were

    outfile.close(); // ALWAYS close your files DAMNIT!
};

// Function to print a small summary to the terminal after data is collected and analyzed
void TBMMonitor::printSummary() const {
    std::cout << "Total records loaded: " << totalLoaded << "\n";
    std::cout << "Total records skipped: " << totalSkipped << "\n";
};