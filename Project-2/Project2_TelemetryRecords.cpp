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

int main() {

    std::vector<TelemetryRecord> all_records;
    int line_num = 0;
    int skipped_lines = 0;
    int valid_readings = 0;

    //------------------------------------------------------------------------------------------------------------------
    // Data Reading First File
    //------------------------------------------------------------------------------------------------------------------

    readTelemetryFile("starship_engine_telemetry.txt", all_records, line_num, skipped_lines, valid_readings);

    //------------------------------------------------------------------------------------------------------------------
    // Data Reading Second File
    //------------------------------------------------------------------------------------------------------------------

    readTelemetryFile("starship_environmental_telemetry.txt", all_records, line_num, skipped_lines, valid_readings);
    
    //------------------------------------------------------------------------------------------------------------------
    // Report Creation
    //------------------------------------------------------------------------------------------------------------------

    std::ofstream outfile("starship_critical_alerts.txt"); // Create the Report text file

    if (!outfile.is_open()) {
        std::cerr << "Error: Cannot open output file\n";
        return 1;
    }

    //------------------------------------------------------------------------------------------------------------------
    // Header
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================" << "\n"
            << "          STARSHIP CRITICAL ALERTS REPORT" << "\n"
            << "============================================================" << "\n\n"
            << "Input files processed: starship_engine_telemetry.txt starship_environmental_telemetry.txt\n"
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
            outfile << rec.timestamp << " "
                    << rec.sensor << " "
                    << rec.value << " "
                    << rec.unit << " "
                    << rec.status << "\n";
        }
    }

    //------------------------------------------------------------------------------------------------------------------
    // Footer
    //------------------------------------------------------------------------------------------------------------------

    outfile << "\n============================================================" << "\n"
            << "End of Report" << "\n"
            << "============================================================" << "\n"
            << "Total warnings: " << warning_count;

    outfile.close();

    return 0;
}