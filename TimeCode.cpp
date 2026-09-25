// Aleksandra Iliukhina
// Assignment 2, Part 2
// For Note 3: I read the notes from HW2 part 2 before working on homework!

#include "TimeCode.h"
#include <stdexcept>
#include <string>

using namespace std;


// Constructor
TimeCode::TimeCode(unsigned int hr, unsigned int min, long long unsigned int sec){
    t = ComponentsToSeconds(hr, min, sec);
}

// Copy constructor
TimeCode::TimeCode(const TimeCode& tc){
    t = tc.t;
}

// Set hours
void TimeCode::SetHours(unsigned int hours){
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(hours, m, s);
}

// Set minutes
void TimeCode::SetMinutes(unsigned int minutes){
    if(minutes >= 60){
        throw invalid_argument("Minutes must be less than 60");
    }
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, minutes, s);
}

// Set seconds
void TimeCode::SetSeconds(unsigned int seconds){
    if(seconds >= 60){
        throw invalid_argument("Seconds must be less than 60");
    }
    unsigned int h, m, s;
    GetComponents(h, m, s);
    t = ComponentsToSeconds(h, m, seconds);
}

// Reset
void TimeCode::reset(){
    t = 0;
}

// Get hours
unsigned int TimeCode::GetHours() const{
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return h;
}

// Get minutes
unsigned int TimeCode::GetMinutes() const{
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return m;
}

// Get seconds
unsigned int TimeCode::GetSeconds() const{
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return s;
}

// Get total seconds
long long unsigned int TimeCode::GetTimeCodeAsSeconds() const{
    return t;
}

// Convert components to seconds
long long unsigned int TimeCode::ComponentsToSeconds(unsigned int hr, unsigned int min, unsigned long long int sec){
    return static_cast<unsigned long long>(hr) * 3600
         + static_cast<unsigned long long>(min) * 60
         + sec;
}

// Convert seconds to components
void TimeCode::GetComponents(unsigned int& hr, unsigned int& min, unsigned int& sec) const{
    hr = t / 3600;
    min = (t % 3600) / 60;
    sec = t % 60;
}

// Convert to string
string TimeCode::ToString() const{
    unsigned int h, m, s;
    GetComponents(h, m, s);
    return to_string(h) + ":" +
           to_string(m) + ":" +
           to_string(s);
}

// Addition
TimeCode TimeCode::operator+(const TimeCode& other) const{
    TimeCode result;
    result.t = t + other.t;
    return result;
}

// Subtraction
TimeCode TimeCode::operator-(const TimeCode& other) const{
    if(t < other.t){
        throw invalid_argument("Result cannot be negative");
    }
    TimeCode result;
    result.t = t - other.t;
    return result;
}

// Multiplication
TimeCode TimeCode::operator*(double a) const{
    if(a < 0){
        throw invalid_argument("Cannot multiply by a negative number");
    }
    TimeCode result;
    result.t = t * a;
    return result;
}

// Division
TimeCode TimeCode::operator/(double a) const{
    if(a <= 0){
        throw invalid_argument("Cannot divide by zero or a negative number");
    }
    TimeCode result;
    result.t = t / a;
    return result;
}

// Comparisons
bool TimeCode::operator==(const TimeCode& other) const{
    return t == other.t;
}

bool TimeCode::operator!=(const TimeCode& other) const{
    return t != other.t;
}

bool TimeCode::operator<(const TimeCode& other) const{
    return t < other.t;
}

bool TimeCode::operator<=(const TimeCode& other) const{
    return t <= other.t;
}

bool TimeCode::operator>(const TimeCode& other) const{
    return t > other.t;
}

bool TimeCode::operator>=(const TimeCode& other) const{
    return t >= other.t;
}

// Sources I used to understand how to write code better: 

// https://www.tutorialspoint.com/cpp_standard_library/stdexcept.htm 

// https://www.geeksforgeeks.org/cpp/constructors-c/ 

// https://dev.to/sandordargo/how-to-use-ampersands-in-c-3kga 

// https://www.geeksforgeeks.org/cpp/address-operator-in-c/ 

// https://learn.microsoft.com/en-us/cpp/cpp/this-pointer?view=msvc-170&utm_source 