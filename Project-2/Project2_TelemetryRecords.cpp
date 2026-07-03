#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

struct TelemetryRecord {
    std::string timestamp;
    std::string sensor;
    double value;
    std::string unit;
    std::string status;
};

int main() {

    //------------------------------------------------------------------------------------------------------------------
    // Data Reading First File
    //------------------------------------------------------------------------------------------------------------------

    std::string engine_path = "starship_engine_telemetry.txt"; // String variable to engine file
    std::ifstream inenginefile(engine_path);

    if (!inenginefile.is_open()) { // Check if the data file can be opened
        std::cerr << "Error: Cannot open input file\n";
        return 1;
    }

    std::string line; // Define a string for the line being read in the while loop

    int line_num = 0; // Keep count of line number

    int skipped_lines = 0; // Keep count of comments, empty, or invalid lines

    int valid_readings = 0; // Keep count of how many valid readings there are

    std::vector<TelemetryRecord> all_records;   // empty vector of our struct type

    // std::map<std::string, std::vector<double>> sensor_data;   // Declare the map BEFORE the while loop

    while (std::getline(inenginefile, line)) {
        line_num++;

        if (line.empty() || line[0] == '#') { // Empty OR commented '#' lines are to be skipped
            skipped_lines++;
            continue;
        }

        std::stringstream ss(line); // <--- fresh stream every line

        std::string timestamp, sensor, value_str, unit, status; // Fresh variables every iteration

        //--------------------------------------------------------------------------------------------------------------
        // Check for readability of lines
        //--------------------------------------------------------------------------------------------------------------

        if (!std::getline(ss, timestamp, ',') ||
            !std::getline(ss, sensor, ',') ||
            !std::getline(ss, value_str, ',') ||
            !std::getline(ss, unit, ',') ||
            !std::getline(ss, status, ',')) {

            std::cerr << "Warning: Malformed line " << line_num 
                      << " (wrong number of fields), skipping.\n";
            continue;
        }
        
        //--------------------------------------------------------------------------------------------------------------
        // Try-Catch for value conversion from string to double
        //--------------------------------------------------------------------------------------------------------------

        double value; // Define fresh value to store the conversion of the string to a double

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

        //--------------------------------------------------------------------------------------------------------------
        // Failure cases passed. Assign values to the struct
        //--------------------------------------------------------------------------------------------------------------

        TelemetryRecord record; // Create a fresh record for each iteration
        record.timestamp = timestamp;
        record.sensor    = sensor;
        record.value     = value;
        record.unit      = unit;
        record.status    = status;

        all_records.push_back(record); // <--- this is the key line where data is now stored for the report
        valid_readings++; // Can only increment here if everything else prior ran smoothly
    }

    inenginefile.close();

    //------------------------------------------------------------------------------------------------------------------
    // Data Reading Second File
    //------------------------------------------------------------------------------------------------------------------

    std::string environmental_path = "starship_environmental_telemetry.txt"; // String variable to environmental input file
    std::ifstream inenvifile(environmental_path);

    if (!inenvifile.is_open()) { // Check if the data file can be opened
        std::cerr << "Error: Cannot open input file\n";
        return 1;
    }

    while (std::getline(inenvifile, line)) {
        line_num++;

        if (line.empty() || line[0] == '#') { // Empty OR commented '#' lines are to be skipped
            skipped_lines++;
            continue;
        }

        std::stringstream ss(line); // <--- fresh stream every line

        std::string timestamp, sensor, value_str, unit, status; // Fresh variables every iteration

        //--------------------------------------------------------------------------------------------------------------
        // Check for readability of lines
        //--------------------------------------------------------------------------------------------------------------

        if (!std::getline(ss, timestamp, ',') ||
            !std::getline(ss, sensor, ',') ||
            !std::getline(ss, value_str, ',') ||
            !std::getline(ss, unit, ',') ||
            !std::getline(ss, status, ',')) {

            std::cerr << "Warning: Malformed line " << line_num 
                      << " (wrong number of fields), skipping.\n";
            continue;
        }
        
        //--------------------------------------------------------------------------------------------------------------
        // Try-Catch for value conversion from string to double
        //--------------------------------------------------------------------------------------------------------------

        double value; // Define fresh value to store the conversion of the string to a double

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

        //--------------------------------------------------------------------------------------------------------------
        // Failure cases passed. Assign values to the struct
        //--------------------------------------------------------------------------------------------------------------

        TelemetryRecord record; // Create a fresh record for each iteration
        record.timestamp = timestamp;
        record.sensor    = sensor;
        record.value     = value;
        record.unit      = unit;
        record.status    = status;

        all_records.push_back(record); // <--- this is the key line where data is now stored for the report
        valid_readings++; // Can only increment here if everything else prior ran smoothly
    }

    inenvifile.close();

    //------------------------------------------------------------------------------------------------------------------
    // Report Creation
    //------------------------------------------------------------------------------------------------------------------
    
    /*
    After both files have been completely read and merged:
    - Print to std::cout a brief summary: total number of records loaded from both files combined.
    - Create and write to a new output file /home/workdir/artifacts/starship_critical_alerts.txt containing:
    - A professional header
    - A section titled "CRITICAL WARNING RECORDS" that lists only the records whose status member equals "WARNING". For each warning record print all five fields on separate indented lines.
    A footer with the total number of warning records found.
    */

    std::ofstream outfile("starship_critical_alerts.txt"); // Create the Report text file

    if (!outfile.is_open()) {
        std::cerr << "Error: Cannot open output file\n";
        return 1;
    }

    //------------------------------------------------------------------------------------------------------------------
    // Header
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================" << "\n"
            << "          STARSHIP AVIONICS REPORT" << "\n"
            << "============================================================" << "\n\n"
            << "Input files processed: " << engine_path << " " << environmental_path << "\n"
            << "Total lines in files: " << line_num << "\n"
            << "Valid numeric sensor readings processed: " << valid_readings << "\n"
            << "Lines skipped (comments, empty, or invalid): " << skipped_lines << "\n\n"
            << "------------------------------------------------------------" << "\n" 
            << "CRITICAL WARNING RECORDS" << "\n"
            << "------------------------------------------------------------" << "\n\n";

    //------------------------------------------------------------------------------------------------------------------
    // Data Analysis
    //------------------------------------------------------------------------------------------------------------------

    int warning_count = 0; // Keep count of how many warnings there are

    for (const TelemetryRecord& rec : all_records) {
        /* for (const auto& x )Binds to the original elements without copying them, but marks them read-only. This is
        the industry best practice for viewing large objects or strings.
        */

        if (rec.status == "WARNING") {
            warning_count++;
            outfile << rec.timestamp << rec.sensor << rec.value << rec.unit << rec.status;
        }
    }

    //------------------------------------------------------------------------------------------------------------------
    // Footer
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================" << "\n"
            << "End of Report" << "\n"
            << "============================================================" << "\n"
            << "Total warnings: " << warning_count;

    outfile.close();

    return 0;
}