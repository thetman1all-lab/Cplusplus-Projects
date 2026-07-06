#ifndef _SENSORREADING_H_
#define _SENSORREADING_H_

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// #include <fstream>
// #include <sstream>
// #include <algorithm>


class SensorReading {
private:

    // Declare private variables that will be grabbed from the TBM sensor data file
    std::string timestamp;
    std::string segment_id;
    double pressure_bar;
    double temperature_C;
    double vibration_level;
    std::string status;

public:

    // Constructor
    SensorReading(std::string ts, std::string sid, double pbar, double temp, double vl, std::string stat);

    // TODO: Getter methods for all 6 fields
    std::string getTimestamp() const;
    std::string getSegmentId() const;
    double getPressureBar()    const;
    double getTemperatureC()   const;
    double getVibrationLevel() const;
    std::string getStatus()    const;


    // Member function to determine if status is critical. Return true or false
    bool isCritical() const;

    // Member function to print out data in clear format
    void print(std::ostream& out) const;
};

#endif