#ifndef CURRENTTIME_VIKRAM_SAHAI_SAXENA_H
#define CURRENTTIME_VIKRAM_SAHAI_SAXENA_H

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

using namespace std;

// Singleton class to get current time
class CurrentTime {
private:
    static CurrentTime* instance; // Static instance of the CurrentTime class

    CurrentTime(); // Private constructor

public:
    
    CurrentTime(const CurrentTime&) = delete; // Delete copy constructor
    CurrentTime& operator=(const CurrentTime&) = delete; // Delete assignment operator
    static CurrentTime* getInstance(); // Static method to get the instance of the singleton
    string getCurrentTime(); // Get the current time as a string
    string getCurrentHHMMSS(); // Get the current time in HH:MM:SS format
    string getCurrentMMDDYYYY(); // Get the current time in MM/DD/YYYY format
};
#endif