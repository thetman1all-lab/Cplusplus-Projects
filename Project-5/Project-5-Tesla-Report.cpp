#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

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

// This class manages a collection of VehicleStatus objects.
class FleetMonitor{
private:
    // This vector holds ALL the Fleet objects we load from the files.
    std::vector<VehicleStatus> records;

    // These keep track of how many records we loaded or skipped ad line number.
    int totalLoaded = 0;
    int totalSkipped = 0;
    int lineNumber = 0;

    // =(1)=
    void readSingleFile(const std::string& filename);

    // double dataValueToDouble(const std::string& data, const int& linenumber, int& totalSkipped); // Because multiple data values need to be converted, avoid repeating and make a function to convert them from strings to doubles

    // int dataValueToInt(const std::string& data, const int& linenumber, int& totalSkipped);

public:

    // =(2)=
    void loadFromFile(const std::string& diagnostics);

    // Returns how many records are loaded by taking the size of the records vector. Remember only valid records go in the vector
    // =(3)=
    size_t getTotalRecords() const { return records.size(); }

    // Writes all critical records to a new text file.
    // =(4)=
    void generateCriticalReport(const std::string& filename);

    // TODO: printSummary() — prints a short summary to the console (total records, number of critical records, etc.).
    // =(5)=
    void printSummary() const;


};

//----------------------------------------------------------------------------------------------------------------------
// Member function definition for reading files
//----------------------------------------------------------------------------------------------------------------------

// =(1)=
void FleetMonitor::readSingleFile(const std::string& filename) {

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
        VehicleStatus record(timestamp, vehicle_id, value1, value2, value3, status);
        records.push_back(record);
        totalLoaded++;
    }

    infile.close();

}

//----------------------------------------------------------------------------------------------------------------------
// Member function definition for loading files
//----------------------------------------------------------------------------------------------------------------------

// =(2)=
void FleetMonitor::loadFromFile(const std::string& diagnostics) {
    readSingleFile(diagnostics);
}


// =(4)=
void FleetMonitor::generateCriticalReport(const std::string& filename) {
    std::ofstream outfile(filename);
    if (!outfile.is_open()) return;

    int warningCount = 0;

    for (const VehicleStatus& rec : records) {
        if (rec.isCritical()) {
            warningCount++;
            rec.print(outfile);
            outfile << "------------------------------------------------------------\n";
        }
    }

    outfile << "Total WARNING records: " << warningCount << "\n";
    outfile.close();
}

// =(5)=
void FleetMonitor::printSummary() const {
    std::cout << "Total records loaded: " << totalLoaded << "\n";
    std::cout << "Total records skipped: " << totalSkipped << "\n";
}

int main() {
    FleetMonitor diagnostic;

    diagnostic.loadFromFile("tesla_vehicle_diagnostics.txt");

    diagnostic.generateCriticalReport("tesla_fleet_critical_report.txt");

    return 0;
}