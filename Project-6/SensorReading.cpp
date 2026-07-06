#include "SensorReading.h"
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

// Constructor with initializer list
SensorReading::SensorReading(std::string ts, std::string sid, double pbar, double temp, double vl, std::string stat)
    : timestamp(ts), segment_id(sid), pressure_bar(pbar), temperature_C(temp), vibration_level(vl), status(stat) {}

// TODO: Getter methods for all 6 fields
std::string SensorReading::getTimestamp() const {return timestamp;}
std::string SensorReading::getSegmentId() const {return segment_id;}
double SensorReading::getPressureBar()    const {return pressure_bar;}
double SensorReading::getTemperatureC()   const {return temperature_C;}
double SensorReading::getVibrationLevel() const {return vibration_level;}
std::string SensorReading::getStatus()    const {return status;}


// Member function to determine if status is critical. Return true or false
bool SensorReading::isCritical() const {return status == "CRITICAL";}

// Member function to print out data in clear format
void SensorReading::print(std::ostream& out) const {
    out << "Timestamp: " << timestamp << "\n"
        << "Segment ID: " << segment_id << "\n"
        << " Pressure: " << std::fixed << std::setprecision(2) << pressure_bar << " bar" << "\n"
        << "Temperature: " << temperature_C << " C" << "\n"
        << "Vibration Level: " << vibration_level << "\n"
        << "Status: " << status << "\n";
}
