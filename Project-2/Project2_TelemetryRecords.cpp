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
    // Data Reading
    //------------------------------------------------------------------------------------------------------------------

    std::string file_path = "/Users/wardkimball/Desktop/Misc/Computing/Cplusplus-Projects/Project-1/starship_avionics_log.txt"; // String variable to input file for futur use in script
    std::ifstream infile(file_path);

    if (!infile.is_open()) { // Check if the data file can be opened
        std::cerr << "Error: Cannot open input file\n";
        return 1;
    }

    std::string line; // Define a string for the line being read in the while loop
    int line_num = 0; // Keep count of line number
    int skipped_lines = 0; // Keep count of comments, empty, or invalid lines
    int valid_readings = 0; // Keep count of how many valid readings there are
    std::map<std::string, std::vector<double>> sensor_data;   // Declare the map BEFORE the while loop

    while (std::getline(infile, line)) {
        line_num++;

        if (line.empty() || line[0] == '#') { // Empty OR commented '#' lines are to be skipped
            skipped_lines++;
            continue;
        }

        std::stringstream ss(line); // <--- fresh stream every line

        std::string timestamp, sensor, value_str, unit, status; // Fresh variables every iteration

        if (!std::getline(ss, timestamp, ',') ||
            !std::getline(ss, sensor, ',') ||
            !std::getline(ss, value_str, ',') ||
            !std::getline(ss, unit, ',') ||
            !std::getline(ss, status, ',')) {

            std::cerr << "Warning: Malformed line " << line_num 
                      << " (wrong number of fields), skipping.\n";
            continue;
        }
        
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

        // === HERE is where the data STORED ===
        sensor_data[sensor].push_back(value); // <--- this is the key line where data is now stored for the report
        valid_readings++; // Can only increment here if everything else prior ran smoothly
    }

    infile.close();

    //------------------------------------------------------------------------------------------------------------------
    // Report Creation
    //------------------------------------------------------------------------------------------------------------------
    
    std::ofstream outfile("/Users/wardkimball/Desktop/Misc/Computing/Cplusplus-Projects/Project-1/starship-avionics-summary.txt"); // Create the Report text file

    if (!outfile.is_open()) {
        std::cerr << "Error: Cannot open output file\n";
        return 1;
    }
    // Header
    outfile << "============================================================" << "\n"
            << "     STARSHIP AVIONICS TELEMETRY SUMMARY REPORT" << "\n"
            << "============================================================" << "\n\n"
            << "Input file processed: " << file_path
            << "\nTotal lines in file: " << line_num
            << "\nValid numeric sensor readings processed: " << valid_readings
            << "\nLines skipped (comments, empty, or invalid): " << skipped_lines << "\n\n"
            << "------------------------------------------------------------" << "\n" 
            << "SENSOR STATISTICS (values shown in log-native units)" << "\n"
            << "------------------------------------------------------------" << "\n\n";

    //------------------------------------------------------------------------------------------------------------------
    // Data Analysis
    //------------------------------------------------------------------------------------------------------------------

    for (const auto& [sensor, values] : sensor_data) { // const auto& x)Binds to the original elements without copying them, but marks them read-only. This is the industry best practice for viewing large objects or strings.
        if (values.empty()) continue;

        double min_v = *std::min_element(values.begin(), values.end());
        double max_v = *std::max_element(values.begin(), values.end());
        
        double sum = 0.0; // Fresh sum for each sensor type

        for (double num : values) { // Sum all values for current sensor type
            sum += num;
        }

        double average_v = sum / values.size(); // Find average for current sensor type's values

        outfile << "Sensor: " << sensor << "\n"
                << "  Number of readings: " << values.size() << "\n";

        outfile << std::fixed << std::setprecision(2); // Set the precision of all reported values to 2 decimal places

        outfile << "  Minimum value: " << min_v << "\n"
                << "  Maximum value: " << max_v << "\n"
                << "  Average value: " << average_v << "\n\n";
    }

    //------------------------------------------------------------------------------------------------------------------
    // Footer
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================" << "\n"
            << "End of Report" << "\n"
            << "============================================================";

    outfile.close();

    return 0;
}