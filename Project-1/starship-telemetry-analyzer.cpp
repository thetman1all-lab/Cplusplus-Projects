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

    while (std::getline(infile, line)) {          // full line
        if (line.empty() || line[0] == '#') continue;

        std::stringstream ss(line);
        std::string timestamp, sensor, value_str, unit, status;
        std::getline(ss, timestamp, ',');
        std::getline(ss, sensor, ',');
        std::getline(ss, value_str, ',');
        std::getline(ss, unit, ',');
        std::getline(ss, status, ',');
    }

    infile.close();

    return 0;
}