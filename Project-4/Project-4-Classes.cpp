#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

class TelemetryRecord {
private:
    // ============================================================
    // PRIVATE SECTION
    // ============================================================
    // These variables are the DATA that belongs to ONE telemetry reading.
    // Because they are private, NO CODE OUTSIDE this class can directly
    // touch or change these variables. This is called ENCAPSULATION.
    std::string timestamp;
    std::string sensor;
    double value;
    std::string unit;
    std::string status;

public:
    // ============================================================
    // PUBLIC SECTION
    // ============================================================
    // This is the "interface" — the only way outside code is allowed
    // to interact with a TelemetryRecord object.

    // --- CONSTRUCTOR ---
    // This special function runs automatically when you create
    // a new TelemetryRecord object. Its job is to initialize the
    // private variables.
    TelemetryRecord(std::string ts, std::string sen, double val,
                    std::string un, std::string stat)
        :timestamp(ts), sensor(sen), value(val), unit(un), status(stat) {} // Why is it variable name then parenthesies?
        // The colon syntax above is called an "initializer list".
        // It's the preferred way to initialize member variables in a constructor.
    

    // --- GETTER METHODS ---
    // These functions let outside code READ the private data.
    // We use getters instead of making the variables public
    // because we want to control how the data is accessed.
    std::string getTimestamp() const {return timestamp;}
    std::string getSensor()    const {return sensor;}
    double      getValue()     const {return value;}
    std::string getUnit()      const {return unit;}
    std::string getStatus()    const {return status;}

    // --- MEMBER FUNCTIONS (Behavior) ---
    // These are actions the object can perform on its own data.
    bool isWarning() const{                    // Checks if status == "WARNING"
        return status == "WARNING";
    }

    void print(std::ostream& out) const{       // Prints the record nicely
        out << "Timestamp : " << timestamp << "\n"
            << "Sensor    : " << sensor << "\n"
            << "Value     : " << value << " " << unit << "\n"
            << "Status    : " << status << "\n";
    }
};

//======================================================================================================================

class TelemetryProcessor {
private:
    // ============================================================
    // PRIVATE DATA
    // ============================================================
    // This vector belongs to the TelemetryProcessor.
    // It will store all the TelemetryRecord objects we load.
    std::vector<TelemetryRecord> records;

    // Optional counters (you can add these later if you want)
    int totalLoaded = 0;
    int totalSkipped = 0;

    // ============================================================
    // PRIVATE HELPER METHOD
    // ============================================================
    // This function reads ONE file and adds the records to the vector.
    // It is private because outside code doesn't need to call it directly.
    void readSingleFile(const std::string& filename);

public:
    // Load both files by calling the helper twice
    void loadFromFiles(const std::string& engineFile,
                       const std::string& environmentalFile);

    // Sort all records by timestamp
    void sortByTimestamp();

    // Generate reports
    void generateWarningsReport(const std::string& outputFilename) const;
    void generateHighValueReport(const std::string& outputFilename) const;

    // Utility methods
    size_t getRecordCount() const;
    void printSummary() const;
};

//======================================================================================================================

// This is the public method the user of the class will call
void TelemetryProcessor::loadFromFiles(const std::string& engineFile,
                                       const std::string& environmentalFile)
{
    // We simply call our private helper method twice.
    // This avoids duplicating the file reading logic.
    readSingleFile(engineFile);
    readSingleFile(environmentalFile);
}

// This private helper does the actual reading work for ONE file
void TelemetryProcessor::readSingleFile(const std::string& filename)
{
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open file: " << filename << "\n";
        return;
    }

    std::string line;

    while (std::getline(infile, line)) {
        // Skip empty lines and comments
        if (line.empty() || line[0] == '#') {
            totalSkipped++;
            continue;
        }

        std::stringstream ss(line);

        std::string timestamp, sensor, value_str, unit, status;

        // Parse the five fields
        if (!std::getline(ss, timestamp, ',') ||
            !std::getline(ss, sensor, ',') ||
            !std::getline(ss, value_str, ',') ||
            !std::getline(ss, unit, ',') ||
            !std::getline(ss, status, ',')) {
            totalSkipped++;
            continue;
        }

        // Convert value to double
        double value;
        try {
            value = std::stod(value_str);
        }catch (const std::invalid_argument& e) {
            std::cerr << "Warning: Invalid numeric value on line";
                     
            totalSkipped++;
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Warning: Value out of range on line";
            totalSkipped++;
            continue;
        }

        // Create a TelemetryRecord object and store it
        TelemetryRecord record(timestamp, sensor, value, unit, status);
        records.push_back(record);
        totalLoaded++;
    }

    infile.close();
}