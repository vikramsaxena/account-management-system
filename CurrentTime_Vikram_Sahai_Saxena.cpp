#include "CurrentTime_Vikram_Sahai_Saxena.h"

// Initialize the static instance pointer to nullptr
CurrentTime* CurrentTime::instance = nullptr;

// Private constructor definition
CurrentTime::CurrentTime() {}

// Static method to get the singleton instance
CurrentTime* CurrentTime::getInstance() {
    if (instance == nullptr) {
        instance = new CurrentTime();
    }
    return instance;
}

// Get the current time as a string, replacing spaces with underscores
string CurrentTime::getCurrentTime() {
    time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    stringstream ss;
    string currentTime = asctime(timeinfo);
    for (char &ch : currentTime) {
        if (ch == ' ') {
            ch = '_';
        }
    }
    ss << currentTime;
    return ss.str();
}

// Get the current time in HH:MM:SS format
string CurrentTime::getCurrentHHMMSS() {
    time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    stringstream ss;
    ss << setfill('0') << setw(2) << timeinfo->tm_hour << ":"
    << setfill('0') << setw(2) << timeinfo->tm_min << ":"
    << setfill('0') << setw(2) << timeinfo->tm_sec;
    return ss.str();
}

// Get the current date in MM/DD/YYYY format
string CurrentTime::getCurrentMMDDYYYY() {
    time_t seconds;
    seconds = time(NULL);
    tm * timeinfo;
    timeinfo = localtime(&seconds);
    stringstream ss;
    ss << setfill('0') << setw(2) << timeinfo->tm_mon + 1 << "/"
    << setfill('0') << setw(2) << timeinfo->tm_mday << "/"
    << setfill('0') << setw(2) << timeinfo->tm_year + 1900;
    return ss.str();
}