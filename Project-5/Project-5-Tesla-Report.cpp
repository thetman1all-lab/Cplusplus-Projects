#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

// TODO: You must have two properly encapsulated classes (VehicleStatus and FleetMonitor).

// TODO: FleetMonitor must use a private helper method for reading.

// TODO: The program must successfully load the data and generate a critical alerts report file.

// TODO: The code should be reasonably organized (no massive duplication).

// TODO: You should be able to explain (in your own words) why certain things are private vs public.

class VehicleStatus{

private:

    // Private member variables
    std::string timestamp;
    std::string vehicle_id;
    double battery_temp_C;
    int battery_soc_percent;
    double motor_temp_C;
    std::string status;

public:

    // Constructor of variables. An initializer list to set the private variables
    VehicleStatus(std::string ts, std::string vid, double bt, int bsp, double mt, std::string stat)
        : timestamp(ts), vehicle_id(vid), battery_temp_C(bt), battery_soc_percent(bsp), motor_temp_C(mt), status(stat) {}

    // GETTER METHODS (Accessors)
    std::string getTimeStamp()         const {return timestamp;}
    std::string getVehicleId()         const {return vehicle_id;}
    double      getBatteryTemp()       const {return battery_temp_C;}
    int         getBatterySocPercent() const {return battery_soc_percent;}
    double      getMotorTemp()         const {return motor_temp_C;}
    std::string getStatus()            const {return status;}

    // isCritical() — returns true if the status is "CRITICAL".
    bool isCritical() const {
        return status == "CRITICAL";
    }

    // print() — prints the record in a clean format.
    void print(std::ostream& out) const {
        out << "Timestamp           : " << timestamp << "\n"
            << "Vehicle ID          : " << vehicle_id << "\n"
            << "Battery Temperature : " << std::fixed << std::setprecision(2) << battery_temp_C <<  "C\n"
            << "Battery SOC Percent : " << battery_soc_percent << "%\n"
            << "Motor Temperature   : " << motor_temp_C << "C\n"
            << "Status              : " << status << "\n";
    }
};

//----------------------------------------------------------------------------------------------------------------------
// Manager Class
//----------------------------------------------------------------------------------------------------------------------

class FleetMonitor{
private:
    // This vector holds ALL the Fleet objects we load from the files.
    std::vector<VehicleStatus> records;

    // These keep track of how many records we loaded or skipped ad line number.
    int totalLoaded = 0;
    int totalSkipped = 0;
    int lineNumber = 0;

    void readFileMethod(const std::string& filename);

    // double dataValueToDouble(const std::string& data, const int& linenumber, int& totalSkipped); // Because multiple data values need to be converted, avoid repeating and make a function to convert them from strings to doubles

    // int dataValueToInt(const std::string& data, const int& linenumber, int& totalSkipped);

public:


};

//----------------------------------------------------------------------------------------------------------------------
// Member function definition for reading files
//----------------------------------------------------------------------------------------------------------------------

void FleetMonitor::readFileMethod(const std::string& filename) {

    std::ifstream infile(filename);

    // Check if the file can be opened or not
    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open file: " << filename << "\n";
        return;
    }

    // Create a variable the geline function can use for reading lines
    std::string line;

    // === Read and ignore the header line ===
    std::getline(infile, line);   // This reads the first line (the header) and discards it

    // While loop to read through every line of the data file
    while (std::getline(infile, line)) {

        lineNumber++; // Track the line number you are on

        // If the line is empty or has a comment, skip it
        if (line.empty() || line[0] == '#') {
            totalSkipped++; // Track number of lines skipped
            continue;
        }

        std::stringstream ss(line); // Allow the text in the line to be parssed into words
        std::string timestamp, vehicle_id, battery_temp_C, battery_soc_percent, motor_temp_C, status;

        if (!std::getline(ss, timestamp, ',') ||
            !std::getline(ss, vehicle_id, ',') ||
            !std::getline(ss, battery_temp_C, ',') ||
            !std::getline(ss, battery_soc_percent, ',') ||
            !std::getline(ss, motor_temp_C, ',') ||
            !std::getline(ss, status, ',')) {
            totalSkipped++;
            continue;
        }

        double value1;
        int    value2;
        double value3;

        // value1 = dataValueToDouble(battery_temp_C,lineNumber, totalSkipped);
        // value2 = dataValueToDouble(battery_soc_percent,lineNumber, totalSkipped);
        // value3 = dataValueToDouble(motor_temp_C,lineNumber, totalSkipped);

        try {
            value1 = std::stod(battery_temp_C);
        } catch (...) {
            std::cout << "Invalid value at line " << lineNumber << "\n";
            totalSkipped++;
            continue;
        }

           try {
            value2 = std::stod(battery_temp_C);
        } catch (...) {
            std::cout << "Invalid value at line " << lineNumber << "\n";
            totalSkipped++;
            continue;
        }

        try {
            value3 = std::stod(battery_temp_C);
        } catch (...) {
            std::cout << "Invalid value at line " << lineNumber << "\n";
            totalSkipped++;
            continue;
        }

        // Create a FleetMonitor object and store it in the vector
        VehicleStatus record(timestamp, vehicle_id, battery_temp_C, battery_soc_percent, motor_temp_C, status);
        records.push_back(record);
        totalLoaded++;
    }

    infile.close();

}