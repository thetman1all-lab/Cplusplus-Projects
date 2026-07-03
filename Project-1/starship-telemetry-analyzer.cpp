#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    //------------------------------------------------------------------------------------------------------------------
    // Data Reading
    //------------------------------------------------------------------------------------------------------------------

    std::ifstream infile("/Users/wardkimball/Desktop/Misc/Computing/Cplusplus-Projects/Project-1/starship_avionics_log.txt");

    if (!infile.is_open()) { // Check if the data file can be opened
        std::cerr << "Error: Cannot open input file\n";
        return 1;
    }

    std::string line; // Define a string for the line being read in the while loop
    int line_num = 0; // Keep track of line number
    std::map<std::string, std::vector<double>> sensor_data;   // Declare the map BEFORE the while loop

    while (std::getline(infile, line)) {
        line_num++;

        if (line.empty() || line[0] == '#') { // Empty OR commented '#' lines are to be skipped
            // skipped++;
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
            continue;
        } catch (const std::out_of_range& e) {
            std::cerr << "Warning: Value out of range on line " << line_num << "\n";
        continue;
        }

        // === HERE is where the data STORED ===
        // Only reaches here on a completely good line
        sensor_data[sensor].push_back(value); // <--- this is the key line where data is now stored for the report
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
            << "STARSHIP AVIONICS TELEMETRY SUMMARY REPORT" << "\n"
            << "============================================================" << "\n\n";

    //------------------------------------------------------------------------------------------------------------------
    // Data Analysis
    //------------------------------------------------------------------------------------------------------------------

    for (const auto& [sensor, values] : sensor_data) { // const auto& x)Binds to the original elements without copying them, but marks them read-only. This is the industry best practice for viewing large objects or strings.
        if (values.empty()) continue;
        double min_v = *std::min_element(values.begin(), values.end());
        double max_v = *std::max_element(values.begin(), values.end());
        
        double sum = 0;

        for (int num : values){
            sum += num;
        }

        double average_v = sum / values.size();

        std::cout << sensor << " | " << min_v << " | " << max_v << " | " << average_v << "\n";
    }

    // All the other gobletigook goes here

    //------------------------------------------------------------------------------------------------------------------
    // Footer
    //------------------------------------------------------------------------------------------------------------------

    outfile << "============================================================" << "\n"
            << "End of Report" << "\n"
            << "============================================================";

    outfile.close();

    return 0;
}