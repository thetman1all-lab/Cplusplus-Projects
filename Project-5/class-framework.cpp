#include <string>
#include <iostream>
#include <vector>


// ============================================================
// CLASS DECLARATION
// ============================================================
class ExampleClass {                    // ← Class name (use PascalCase)

private:
    // ============================================================
    // PRIVATE MEMBER VARIABLES
    // ============================================================
    // These store the data. They should almost always be private.
    std::string memberVariable1;        // Example: a string
    int         memberVariable2;        // Example: an integer
    double      memberVariable3;        // Example: a double

    // You can also have private helper methods (declared here)
    void privateHelperFunction();

public:
    // ============================================================
    // CONSTRUCTOR
    // ============================================================
    // Special function that runs when an object is created.
    // Use an initializer list to set the private variables.
    ExampleClass(std::string mv1, int mv2, double mv3)
        : memberVariable1(mv1),         // Initialize memberVariable1 with mv1
          memberVariable2(mv2),         // Initialize memberVariable2 with mv2
          memberVariable3(mv3) {}       // Initialize memberVariable3 with mv3

    // ============================================================
    // DESTRUCTOR (Optional)
    // ============================================================
    // Only needed if your class manages resources (like dynamic memory).
    // For most beginner/intermediate classes, you can leave this out.
    ~ExampleClass() {}

    // ============================================================
    // GETTER METHODS (Accessors)
    // ============================================================
    // These let outside code READ private data safely.
    std::string getMemberVariable1() const { return memberVariable1; }
    int         getMemberVariable2() const { return memberVariable2; }
    double      getMemberVariable3() const { return memberVariable3; }

    // ============================================================
    // SETTER METHODS (Mutators) - Optional
    // ============================================================
    // Use these only if you want to allow controlled modification of data.
    void setMemberVariable1(const std::string& newValue) {
        memberVariable1 = newValue;
    }

    // ============================================================
    // PUBLIC MEMBER FUNCTIONS
    // ============================================================
    // These are the main actions/behaviors of the class.
    void doSomething();
    bool isValid() const;
    void print() const;

private:
    // ============================================================
    // PRIVATE HELPER METHODS
    // ============================================================
    // These are helper functions used internally by the class.
    // They are not accessible from outside the class.
    void internalCalculation();
};

// ============================================================
// FUNCTION DEFINITIONS (Outside the class)
// ============================================================
// This is where you write the actual code for functions declared above.

void ExampleClass::doSomething() {
    // Implementation goes here
    std::cout << "Doing something...\n";
}

bool ExampleClass::isValid() const {
    // Example logic
    return memberVariable2 > 0;
}

void ExampleClass::print() const {
    std::cout << "MemberVariable1: " << memberVariable1 << "\n";
    std::cout << "MemberVariable2: " << memberVariable2 << "\n";
    std::cout << "MemberVariable3: " << memberVariable3 << "\n";
}

void ExampleClass::privateHelperFunction() {
    // This can only be called from inside the class
}

void ExampleClass::internalCalculation() {
    // Another private helper
}

//======================================================================================================================
//----------------------------------------------------------------------------------------------------------------------
//======================================================================================================================

// A simple data class that the manager will work with
class Record {
private:
    std::string id;
    double value;

public:
    Record(std::string i, double v) : id(i), value(v) {}

    std::string getId() const { return id; }
    double getValue() const { return value; }
};

// ============================================================
// MANAGER-STYLE CLASS
// ============================================================
class RecordManager {
private:
    // The manager owns a collection of Record objects
    std::vector<Record> records;

    // Private helper method (only used internally)
    void loadFromFileHelper(const std::string& filename);

public:
    // Constructor
    RecordManager() {}

    // Public method that uses the private helper
    void loadData(const std::string& filename);

    // Member function defined INSIDE the class (good for simple functions)
    int getRecordCount() const {
        return records.size();
    }

    // Member function defined OUTSIDE the class (better for complex logic)
    void processAllRecords();

    // Another function defined outside the class
    void printSummary() const;
};

// ============================================================
// FUNCTION DEFINITIONS OUTSIDE THE CLASS
// ============================================================

// This is a private helper, but defined outside for clarity
void RecordManager::loadFromFileHelper(const std::string& filename) {
    // In a real program, you would read the file here
    // and create Record objects, then push them into 'records'
    std::cout << "Loading data from: " << filename << "\n";
}

// Public method - calls the private helper
void RecordManager::loadData(const std::string& filename) {
    loadFromFileHelper(filename);   // Calls the private helper
}

// This function is more complex, so we define it outside the class
void RecordManager::processAllRecords() {
    for (const Record& rec : records) {
        // Do something with each record
        std::cout << "Processing record ID: " << rec.getId() << "\n";
    }
}

// Another function defined outside the class
void RecordManager::printSummary() const {
    std::cout << "Total records: " << records.size() << "\n";
}