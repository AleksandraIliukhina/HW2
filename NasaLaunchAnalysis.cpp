// Aleksandra Iliukhina
// Assignment 2, Part 2
// For Note 3: I read the notes from HW2 part 2 before working on homework!

#include <iostream>
#include <fstream> // We need it to read CSV
#include <string>
#include <vector>
#include "TimeCode.h"

using namespace std;


// This function gets the time from one line of the CSV file
TimeCode parse_line(string line){
    // Find where " UTC" appears in the line
    int utc = line.find(" UTC");

    // The five characters before UTC are HH:MM
    string time = line.substr(utc - 5, 5);

    // Get the hour and minute from HH:MM
    unsigned int hour = stoi(time.substr(0, 2));
    unsigned int minute = stoi(time.substr(3, 2));

    // The CSV does not give seconds, so seconds are 0
    return TimeCode(hour, minute, 0);
}

int main(){
    ifstream file("Space_Corrected.csv");
    if (!file){
        cout << "Could not open Space_Corrected.csv" << endl;
        return 1;
    }

    string line;
    // The first line contains column names, not launch data
    getline(file, line);
    vector<TimeCode> launchTimes;

    while (getline(file, line)){
        // Launches without UTC have no exact time. The assignment says to ignore those launches
        if (line.find(" UTC") == string::npos){
            continue;
        }
        TimeCode time = parse_line(line);
        launchTimes.push_back(time);
    }

    TimeCode total;
    // Add all launch times together
    for (TimeCode time : launchTimes){
        total = total + time;
    }

    // Divide the total by the number of launches
    TimeCode average = total/launchTimes.size();

    cout << launchTimes.size() << " data points." << endl;
    cout << "AVERAGE: " << average.ToString() << endl;
    return 0;
}