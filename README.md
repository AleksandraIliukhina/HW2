# Assignment 2

This project contains a TimeCode class and two programs that use it.

TimeCode: A C++ project that implements a `TimeCode` class for working with hours, minutes, and seconds. 
Features:
- Create and copy TimeCode objects
- Convert time components to total seconds
- Convert total seconds to hours, minutes, and seconds
- Add and subtract time
- Multiply and divide time
- Compare TimeCode objects
- Set individual time components
- Reset the time to zero
- Handle rollover for minutes and seconds

To run this code, compile and run the tests using the Makefile.

NASA Launch Analysis: NasaLaunchAnalysis.cpp reads launch data from Space_Corrected.csv and calculates the average launch time.
To run the program, use ./nasa

Paint Dry Timer: PaintDryTimer.cpp is a program that tracks the drying time of painted spheres.
The program allows the user to add a new batch, view current batches, and quit the program.
To run the program, use ./pdt

Makefile: compiles all three programs:
tct - TimeCode tests
nasa - NASA launch analysis
pdt - Paint dry timer

To compile everything, use 'make' command.
