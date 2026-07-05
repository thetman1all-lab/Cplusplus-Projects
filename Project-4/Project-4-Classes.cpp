#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>

// ============================================================
// TELEMETRY RECORD CLASS
// ============================================================
// This class represents ONE single telemetry reading.
// It holds the data and provides ways to access it safely.

class TelemetryRecord {
private:
    // These are the actual data values for one reading.
    // They are private so nothing outside this class can directly change them.
    std::string timestamp;
    std::string sensor;
    double value;
    std::string unit;
    std::string status;

public:
    // Constructor: This runs when we create a TelemetryRecord object.
    // It takes the 5 pieces of data and stores them in the private variables.
    TelemetryRecord(std::string ts, std::string sen, double val,
                    std::string un, std::string stat)
        : timestamp(ts), sensor(sen), value(val), unit(un), status(stat) {}
        // called the initializer list. This is where we actually initialize the class’s private member variables.

    // Getters - These let other code READ the private data.
    std::string getTimestamp() const { return timestamp; }
    std::string getSensor()    const { return sensor; }
    double      getValue()     const { return value; }
    std::string getUnit()      const { return unit; }
    std::string getStatus()    const { return status; }

    // Returns true if this record is a warning
    bool isWarning() const {
        return status == "WARNING";
    }

    // Prints the record to any output stream (file or console)
    void print(std::ostream& out) const {
        out << "Timestamp : " << timestamp << "\n"
            << "Sensor    : " << sensor << "\n"
            << "Value     : " << std::fixed << std::setprecision(2) << value 
            << " " << unit << "\n"
            << "Status    : " << status << "\n";
    }
};

//======================================================================================================================

// ============================================================
// TELEMETRY PROCESSOR CLASS
// ============================================================
// This class manages a COLLECTION of TelemetryRecord objects.
// It is responsible for loading, sorting, and reporting on the data.

class TelemetryProcessor {
private:
    // This vector holds ALL the TelemetryRecord objects we load from the files.
    std::vector<TelemetryRecord> records;

    // These keep track of how many records we loaded or skipped.
    int totalLoaded = 0;
    int totalSkipped = 0;
    int lineNumber = 0;

    // ============================================================
    // PRIVATE HELPER METHOD
    // ============================================================
    // We make this private because outside code should NOT call it directly.
    // Its only job is to read ONE file and add records to the 'records' vector.
    // This avoids duplicating the file-reading code.
    void readSingleFile(const std::string& filename);

public:
    // This is the method the user of the class will call.
    // It simply tells the helper to read both files.
    void loadFromFiles(const std::string& engineFile,
                       const std::string& environmentalFile);

    // Sorts all loaded records by timestamp
    void sortByTimestamp();

    // Generates the two reports
    void generateWarningsReport(const std::string& outputFilename) const;
    void generateHighValueReport(const std::string& outputFilename) const;

    // Utility functions
    size_t getRecordCount() const { return records.size(); }
    void printSummary() const;
};

//======================================================================================================================

// ============================================================
// IMPLEMENTATION OF TELEMETRY PROCESSOR METHODS
// ============================================================

// This is the public method. It just calls the private helper twice.
void TelemetryProcessor::loadFromFiles(const std::string& engineFile,
                                       const std::string& environmentalFile)
{
    readSingleFile(engineFile);           // Read first file using the helper
    readSingleFile(environmentalFile);    // Read second file using the helper
}

// Why the fuck am I able to call on readSingleFile() in the void TelemetryProcessor::loadFromFiles() function before we even write its code in the void TelemetryProcessor::readSingleFile() function?

//======================================================================================================================

// This private helper does the actual work of reading one file.
void TelemetryProcessor::readSingleFile(const std::string& filename)
{
    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open file: " << filename << "\n";
        return;
    }

    std::string line;

    while (std::getline(infile, line)) {
        lineNumber++;
        if (line.empty() || line[0] == '#') {
            totalSkipped++;
            continue;
        }

        std::stringstream ss(line);
        std::string timestamp, sensor, value_str, unit, status;

        if (!std::getline(ss, timestamp, ',') ||
            !std::getline(ss, sensor, ',') ||
            !std::getline(ss, value_str, ',') ||
            !std::getline(ss, unit, ',') ||
            !std::getline(ss, status, ',')) {
            totalSkipped++;
            continue;
        }

        double value;
        try {
            value = std::stod(value_str);
        } catch (...) {
            std::cout << "Invalid value at line " << lineNumber << "\n";
            totalSkipped++;
            continue;
        }

        // Create a TelemetryRecord object and store it in the vector
        TelemetryRecord record(timestamp, sensor, value, unit, status);
        records.push_back(record);
        totalLoaded++;
    }

    infile.close();
}

//======================================================================================================================

void TelemetryProcessor::sortByTimestamp()
{
    std::sort(records.begin(), records.end(),
        [](const TelemetryRecord& a, const TelemetryRecord& b) {
            return a.getTimestamp() < b.getTimestamp();
        });
}

//======================================================================================================================

void TelemetryProcessor::generateWarningsReport(const std::string& outputFilename) const
{
    std::ofstream outfile(outputFilename);
    if (!outfile.is_open()) return;

    int warningCount = 0;

    for (const TelemetryRecord& rec : records) {
        if (rec.isWarning()) {
            warningCount++;
            rec.print(outfile);
            outfile << "------------------------------------------------------------\n";
        }
    }

    outfile << "Total WARNING records: " << warningCount << "\n";
    outfile.close();
}

//======================================================================================================================

void TelemetryProcessor::generateHighValueReport(const std::string& outputFilename) const
{
    std::ofstream outfile(outputFilename);
    if (!outfile.is_open()) return;

    int alertCount = 0;

    for (const TelemetryRecord& rec : records) {
        bool isHigh = false;

        if ((rec.getSensor() == "Engine1_Temperature" || rec.getSensor() == "Engine2_Temperature") 
            && rec.getValue() > 2460.0) {
            isHigh = true;
        }
        else if ((rec.getSensor() == "Engine1_Pressure" || rec.getSensor() == "Engine2_Pressure") 
            && rec.getValue() > 130.0) {
            isHigh = true;
        }
        else if (rec.getSensor() == "Fuel_Tank_Pressure" && rec.getValue() > 48.0) {
            isHigh = true;
        }

        if (isHigh) {
            alertCount++;
            rec.print(outfile);
            outfile << "------------------------------------------------------------\n";
        }
    }

    outfile << "Total HIGH VALUE alerts: " << alertCount << "\n";
    outfile.close();
}

//======================================================================================================================

void TelemetryProcessor::printSummary() const
{
    std::cout << "Total records loaded: " << totalLoaded << "\n";
    std::cout << "Total records skipped: " << totalSkipped << "\n";
}


// ============================================================
// MAIN FUNCTION
// ============================================================

int main() {
    TelemetryProcessor processor;

    // Load data from both files using the clean helper method
    processor.loadFromFiles("starship_engine_telemetry.txt",
                            "starship_environmental_telemetry.txt");

    // Sort all records
    processor.sortByTimestamp();

    // Generate the two reports
    processor.generateWarningsReport("starship_warnings_sorted.txt");
    processor.generateHighValueReport("starship_high_value_alerts.txt");

    // Show summary
    processor.printSummary();

    return 0;
}