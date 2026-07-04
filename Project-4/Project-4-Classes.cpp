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