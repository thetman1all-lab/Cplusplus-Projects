#include "TBMMonitor.h"
#include <iostream>

int main() {
    TBMMonitor classUser; // Create the TBMMonitor as an object stored as classUser

    classUser.loadFromFile("boring_tbm_sensor_data.txt"); // Use the loadFromFile() function to load, read, and store the data from the desired data file
    
    classUser.generateCriticalReport("TMB_Critical_Report.txt"); // Use the generateCriticalReport() function to generate the report titled with the inputed name

    classUser.printSummary(); // Use the printSummary() function to print a brief summary to the terminal

    return 0;
}