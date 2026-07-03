#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <vector>
#include <algorithm>
#include <iomanip>

int main() {
    std::ifstream infile("/Users/wardkimball/Desktop/Misc/Computing/Cplusplus-Projects/Project-1/starship_avionics_log.txt");

    if (!infile.is_open()) {
        std::cerr << "Error: Cannot open input file\n";
        return 1;
    }

    std::string line;
    int line_num = 0; // Keep track of line number
    std::map<std::string, std::vector<double>> sensor_data;   // declare this BEFORE the while loop

    while (std::getline(infile, line)) {          // full line

        line_num++;

        if (line.empty() || line[0] == '#') {
            // skipped++;
            continue;
        }
        std::stringstream ss(line);

        std::string timestamp, sensor, value_str, unit, status; // Fresh variables every iteration

        std::getline(ss, timestamp, ',');
        std::getline(ss, sensor, ',');
        std::getline(ss, value_str, ',');
        std::getline(ss, unit, ',');
        std::getline(ss, status, ',');

        std::cout << value_str << "\n" << !!std::getline(ss, value_str, ',') << "\n";

        if (!std::getline(ss, timestamp, ',') || !std::getline(ss, sensor, ',') || !std::getline(ss, value_str, ',') || !std::getline(ss, unit, ',') || !std::getline(ss, status, ',')) {
            std::cerr << "Warning: malformed line " << line_num << "\n";
            continue;
        }
        
        double value; // Define fresh value to store the conversion of the string to a double

        try {
            value = std::stod(value_str);
        } catch (...) {
            std::cerr << "Warning: bad numeric value on line " << line_num << "\n";
            continue;
        }

        // === HERE is where the data STORED ===
        sensor_data[sensor].push_back(value);     // <--- this is the key line where data is now stored for the report
    }

    infile.close();
    return 0;
}