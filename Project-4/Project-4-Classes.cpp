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
    // The class owns the data
    std::vector<TelemetryRecord> records;

    // Counters
    int totalLoaded = 0;
    int totalSkipped = 0;

public:
    // === Core Methods ===

    // Load data from the two files (reuses your existing parsing logic)
    void loadFromFiles(const std::string& engineFile,
                       const std::string& environmentalFile);

    // Sort all records by timestamp
    void sortByTimestamp();

    // === Reporting Methods ===

    // Write only WARNING records to a file
    void generateWarningsReport(const std::string& outputFilename) const;

    // Write high-value alerts to a file
    void generateHighValueReport(const std::string& outputFilename) const;

    // === Utility / Information Methods ===

    // Return how many records are currently loaded
    size_t getRecordCount() const;

    // Optional: Print a summary to the console
    void printSummary() const;
};

//======================================================================================================================




void readTelemetryFile(const std::string& filename,
                       std::vector<TelemetryRecord>& records,
                       int& line_num,
                       int& skipped_lines,
                       int& valid_readings)
{

    std::ifstream infile(filename);

    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open input file: " << filename << "\n";
        return;   // or you can exit(1) if you prefer
    }

    std::string line;

    while (std::getline(infile, line)) {
        line_num++;

        if (line.empty() || line[0] == '#') {
            skipped_lines++;
            continue;
        }

        std::stringstream ss(line);

        std::string timestamp, sensor, value_str, unit, status;

        if (!std::getline(ss, timestamp, ',') ||
            !std::getline(ss, sensor, ',') ||
            !std::getline(ss, value_str, ',') ||
            !std::getline(ss, unit, ',') ||
            !std::getline(ss, status, ',')) {

            std::cerr << "Warning: Malformed line " << line_num 
                      << " (wrong number of fields), skipping.\n";
            continue;
        }

        double value;
        try {
            value = std::stod(value_str);
        } catch (const std::invalid_argument& e) {
            std::cerr << "Warning: Invalid numeric value on line " << line_num 
                      << " ('" << value_str << "'), skipping.\n";
            skipped_lines++;
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Warning: Value out of range on line " << line_num << "\n";
            skipped_lines++;
            continue;
        }

        // All checks passed — create and store the record
        TelemetryRecord record;
        record.timestamp = timestamp;
        record.sensor    = sensor;
        record.value     = value;
        record.unit      = unit;
        record.status    = status;

        records.push_back(record);
        valid_readings++;
    }

    infile.close();
}

//======================================================================================================================

void writeSortedWarningsReport(const std::vector<TelemetryRecord>& records,
                               const std::string& output_filename)
{
    std::ofstream outfile(output_filename);

    if (!outfile.is_open()) {
        std::cerr << "Error: Cannot create output file: " << output_filename << "\n";
        return;
    }

    //------------------------------------------------------------------------------------------------------------------
    // Header
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================\n"
            << "          STARSHIP WARNINGS REPORT\n"
            << "============================================================\n\n"
            << "------------------------------------------------------------\n" 
            << "CRITICAL WARNING RECORDS\n"
            << "------------------------------------------------------------\n\n";

    int warning_count = 0; // Keep count of how many warnings there are

    for (const TelemetryRecord& rec : records) {

        if (rec.status == "WARNING") {
            warning_count++;

            outfile << "Timestamp : " << rec.timestamp << "\n"
                    << "Sensor    : " << rec.sensor << "\n"
                    << "Value     : " << std::fixed << std::setprecision(2) << rec.value << "\n"
                    << "Unit      : " << rec.unit << "\n"
                    << "Status    : " << rec.status << "\n"
                    << "------------------------------------------------------------\n\n";
        }
    }

    //------------------------------------------------------------------------------------------------------------------
    // Footer
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================\n"
            << "Total WARNING records found: " << warning_count << "\n"
            << "============================================================";

    outfile.close();

    std::cout << "Number of WARNING records written           : " << warning_count << "\n";
}

//======================================================================================================================

// Helper function to determine if a record meets high-value criteria (returns true)
bool isHighValueAlert(const TelemetryRecord& rec) {
    if (rec.sensor == "Engine1_Temperature" || rec.sensor == "Engine2_Temperature") {
        return rec.value > 2460.0;
    }
    else if (rec.sensor == "Engine1_Pressure" || rec.sensor == "Engine2_Pressure") {
        return rec.value > 130.0;
    }
    else if (rec.sensor == "Fuel_Tank_Pressure") {
        return rec.value > 48.0;
    }
    return false;   // Not a sensor we're monitoring for high values (returns false)
}

//======================================================================================================================

void HighValueAlertReport(const std::vector<TelemetryRecord>& records,
                               const std::string& output_filename)
{
    std::ofstream outfile(output_filename);

    if (!outfile.is_open()) {
        std::cerr << "Error: Cannot create output file: " << output_filename << "\n";
        return;
    }

    //------------------------------------------------------------------------------------------------------------------
    // Header
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================\n"
            << "          STARSHIP HIGH VALUE ALERTS REPORT\n"
            << "============================================================\n\n"
            << "------------------------------------------------------------\n" 
            << "HIGH VALUE ALERT RECORDS\n"
            << "------------------------------------------------------------\n\n";

    int alert_count = 0;

    for (const TelemetryRecord& rec : records) {
        if (isHighValueAlert(rec)) {
            alert_count++;

            outfile << "Timestamp : " << rec.timestamp << "\n"
                    << "Sensor    : " << rec.sensor << "\n"
                    << "Value     : " << std::fixed << std::setprecision(2) << rec.value << "\n"
                    << "Unit      : " << rec.unit << "\n"
                    << "Status    : " << rec.status << "\n"
                    << "------------------------------------------------------------\n\n";
        }
    }
    //------------------------------------------------------------------------------------------------------------------
    // Footer
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================\n"
            << "Total ALERT records found: " << alert_count << "\n"
            << "============================================================";

    outfile.close();

    std::cout << "Number of high-value alert records written  : " << alert_count << "\n";
}

//======================================================================================================================

int main() {

    TelemetryProcessor processor;

    // Load the data
    processor.loadFromFiles("starship_engine_telemetry.txt",
                            "starship_environmental_telemetry.txt");

    // Sort everything. This is a void function, so it does not take in any data
    processor.sortByTimestamp();

    //------------------------------------------------------------------------------------------------------------------
    // Data Reading First File
    //------------------------------------------------------------------------------------------------------------------

    readTelemetryFile("starship_engine_telemetry.txt", all_records, line_num, skipped_lines, valid_readings);

    //------------------------------------------------------------------------------------------------------------------
    // Data Reading Second File
    //------------------------------------------------------------------------------------------------------------------

    readTelemetryFile("starship_environmental_telemetry.txt", all_records, line_num, skipped_lines, valid_readings);

    std::cout << "Total records loaded                        : " << valid_readings << "\n";

    //------------------------------------------------------------------------------------------------------------------
    // Sorting Data
    //------------------------------------------------------------------------------------------------------------------

    std::sort(all_records.begin(), all_records.end(),           // Sort the struct values based on timestamp
        [](const TelemetryRecord& a, const TelemetryRecord& b) {
            return a.timestamp < b.timestamp;
    });
    // At this point, all-records used in any other function should be sorted by date now

    //------------------------------------------------------------------------------------------------------------------
    // Sorted Warnings Report Creation
    //------------------------------------------------------------------------------------------------------------------

    writeSortedWarningsReport(all_records,"starship_warnings_sorted.txt");

    //------------------------------------------------------------------------------------------------------------------
    // High Value Alert Report Creation
    //------------------------------------------------------------------------------------------------------------------

    HighValueAlertReport(all_records,"starship_high_value_alerts.txt");

    return 0;
}