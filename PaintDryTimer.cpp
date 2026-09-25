// Aleksandra Iliukhina
// Assignment 2 Part 2
// For Note 3: I read the notes from HW2 part 2 before working on homework!

#include <ctime>
#include <iostream>
#include <cmath>
#include <vector>
#include <cstdlib>
#include <cassert>
#include "TimeCode.h"

using namespace std;

struct DryingSnapShot{
    string name;
    time_t startTime;
    TimeCode* timeToDry;
};

// Find how many seconds are left for a batch
long long int get_time_remaining(DryingSnapShot dss){
    time_t now = time(0);
    long long int elapsed = now - dss.startTime;
    long long int total = dss.timeToDry->GetTimeCodeAsSeconds();
    long long int remaining = total - elapsed;
    return remaining;
}

// Turn a batch into a string for printing.
string drying_snap_shot_to_string(DryingSnapShot dss){
    long long int remaining = get_time_remaining(dss);

    if (remaining <= 0){
        return dss.name + " DONE!";
    }

    TimeCode remainingTime(0, 0, remaining);
    return dss.name +
           " (takes " +
           dss.timeToDry->ToString() +
           " to dry) time remaining: " +
           remainingTime.ToString();
}

// Calculate  the surface area of a sphere
double get_sphere_sa(double rad){
    return 4 * M_PI * rad * rad;
}

// Create a TimeCode containing the drying time
TimeCode* compute_time_code(double surfaceArea){
    // The assignment says that surface area is the number of seconds needed for the paint to dry
    TimeCode* result = new TimeCode(0, 0, surfaceArea);
    return result;
}

void tests(){
    // Test get_time_remaining
    DryingSnapShot dss;
    dss.startTime = time(0);
    TimeCode tc(0, 0, 7);
    dss.timeToDry = &tc;
    long long int ans = get_time_remaining(dss);
    assert(ans > 6 && ans < 8);

    // Test sphere surface area
    double sa = get_sphere_sa(2.0);
    assert(50.2654 < sa && sa < 50.2655);

    // Test compute_time_code
    TimeCode* tc2 = compute_time_code(1.0);
    assert(tc2->GetTimeCodeAsSeconds() == 1);
    delete tc2;
    cout << "All tests passed :)" << endl;
}

int main(){
    vector<DryingSnapShot> batches;
    char choice;

    while (true){
        cout << "Choose an option: (A)dd, (V)iew Current Items, (Q)uit: ";
        cin >> choice;

        if(choice == 'A' || choice == 'a'){
            double radius;

            cout << "Enter sphere radius: ";
            cin >> radius;

            double surfaceArea = get_sphere_sa(radius);

            DryingSnapShot batch;

            batch.name = "Batch-" + to_string(rand());
            batch.startTime = time(0);
            batch.timeToDry = compute_time_code(surfaceArea);

            batches.push_back(batch);
        } else if(choice == 'V' || choice == 'v'){
            int i = 0;

            while (i < batches.size()){
                long long int remaining =
                    get_time_remaining(batches[i]);

                if(remaining <= 0){
                    cout << batches[i].name << " DONE!" << endl;

                    // The TimeCode was created with new, so we must delete it when the batch is finished
                    delete batches[i].timeToDry;
                    // Remove the finished batch from the vector
                    batches.erase(batches.begin() + i);
                } else{
                    cout << drying_snap_shot_to_string(batches[i])
                         << endl;

                    i++;
                }
            }

            cout << batches.size()
                 << " batches being tracked."
                 << endl;
        } else if(choice == 'Q' || choice == 'q'){
            break;
        }
    }

    // Delete all remaining TimeCodes before the program ends
    for(int i = 0; i < batches.size(); i++){
        delete batches[i].timeToDry;
    }

    return 0;
}