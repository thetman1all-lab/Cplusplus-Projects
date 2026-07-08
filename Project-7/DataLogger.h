#ifndef DATALOGGER_H
#define DATALOGGER_H

#include <vector>
#include <string>
#include <fstream>

struct LogEntry {
    double current_speed;
    double target_speed;
    double acceleration;
    double error;
};

class DataLogger {
private:
    std::vector<LogEntry> data;

    void pushData(double current_speed, double target_speed, 
                  double acceleration, double error);

public:
    void collectData(double current_speed, double target_speed, 
                     double acceleration, double error);

    void generateDataReport(const std::string& filename) const;
};

#endif