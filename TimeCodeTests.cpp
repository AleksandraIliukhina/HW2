// Aleksandra Iliukhina
// Testing TimeCode

#include <iostream>
#include <assert.h>
#include <stdexcept>
using namespace std;

#include "TimeCode.h"


void TestComponentsToSeconds(){
	cout << "Testing ComponentsToSeconds" << endl;
	
	// Random but "safe" inputs
	long long unsigned int t = TimeCode::ComponentsToSeconds(3, 17, 42);
	assert(t == 11862);
	
	// More tests go here!
	assert(TimeCode::ComponentsToSeconds(0, 0, 0) == 0); //Zero values
	assert(TimeCode::ComponentsToSeconds(0, 1, 30) == 90); // Minutes and seconds
	assert(TimeCode::ComponentsToSeconds(1, 60, 0) == 7200); // Rollover values
	assert(TimeCode::ComponentsToSeconds(0, 120, 0) == 7200);
	
	cout << "PASSED!" << endl << endl;
}


void TestDefaultConstructor(){
	cout << "Testing Default Constructor" << endl;
	TimeCode tc;
	
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	cout << "PASSED!" << endl << endl;
}


void TestComponentConstructor(){
	cout << "Testing Component Constructor" << endl;
	TimeCode tc = TimeCode(0, 0, 0);
	//cout << "Testing ToString()" << endl;
	//cout << "tc: " << tc.ToString() << endl;
	assert(tc.ToString() == "0:0:0");
	
	// more tests go here!
	TimeCode tc2 = TimeCode(2, 30, 15); // Regular values
	assert(tc2.ToString() == "2:30:15");
	TimeCode tc4 = TimeCode(1, 60, 0); // Large minutes
	assert(tc4.ToString() == "2:0:0");
	TimeCode tc5 = TimeCode(0, 0, 60); // Large seconds
	assert(tc5.ToString() == "0:1:0");
	TimeCode tc3 = TimeCode(3, 71, 3801); // Roll-over inputs
	//cout << "tc3: " << tc3.ToString() << endl;
	assert(tc3.ToString() == "5:14:21");
	
	// More tests go here!
	TimeCode tc6 = TimeCode(2, 71, 100); // Very large seconds
	assert(tc6.ToString() == "3:12:40");
	
	cout << "PASSED!" << endl << endl;
}


void TestGetComponents(){
	cout << "Testing GetComponents" << endl;
	
	unsigned int h;
	unsigned int m;
	unsigned int s;
	
	// Regular values
	TimeCode tc = TimeCode(5, 2, 18);
	tc.GetComponents(h, m, s);
	assert(h == 5 && m == 2 && s == 18);
	
	// More tests go here!
	TimeCode tc2 = TimeCode(0, 0, 0);
	tc2.GetComponents(h, m, s);
	assert(h == 0 && m == 0 && s == 0);
	TimeCode tc3 = TimeCode(3, 71, 3801); // Rollover
	tc3.GetComponents(h, m, s);
	assert(h == 5 && m == 14 && s == 21);
	
	cout << "PASSED!" << endl << endl;
}


void TestSubtract(){
	cout << "Testing Subtract" << endl;
	TimeCode tc1 = TimeCode(1, 0, 0);
	TimeCode tc2 = TimeCode(0, 50, 0);
	TimeCode tc3 = tc1 - tc2;
	assert(tc3.ToString() == "0:10:0");
	
	
	TimeCode tc4 = TimeCode(1, 15, 45);
	try{
		TimeCode tc5 = tc1 - tc4;
		cout << "tc5: " << tc5.ToString() << endl;
		assert(false);
	}
	catch(const invalid_argument& e){
		// just leave this empty
		// and keep doing more tests
	}

	// more tests
	TimeCode tc6 = TimeCode(1, 0, 0); // Subtract equal values
	TimeCode tc7 = TimeCode(1, 0, 0);
	TimeCode tc8 = tc6 - tc7;
	assert(tc8.ToString() == "0:0:0");
	TimeCode tc9 = TimeCode(1, 0, 10); // Subtract with seconds rollover
	TimeCode tc10 = TimeCode(0, 0, 20);
	try{
		TimeCode tc11 = tc9 - tc10;
		assert(false);
	}
	catch(const invalid_argument& e){
	}
	
	cout << "PASSED!" << endl << endl;
}


void TestSetMinutes()
{
	cout << "Testing SetMinutes" << endl;

	TimeCode tc = TimeCode(8, 5, 9);
	tc.SetMinutes(15); // test valid change
	assert(tc.ToString() == "8:15:9");

	try
	{
		tc.SetMinutes(80);  // test invalid change
		assert(false);
	}
	catch (const invalid_argument &e)
	{
		// cout << e.what() << endl;
	}

	assert(tc.ToString() == "8:15:9");

	cout << "PASSED!" << endl << endl;
}


// Many More Tests...
void TestSetHours(){
    cout << "Testing SetHours" << endl;

    TimeCode tc = TimeCode(8, 5, 9);
    tc.SetHours(12);

    assert(tc.ToString() == "12:5:9");

    cout << "PASSED!" << endl << endl;
}

void TestSetSeconds(){
    cout << "Testing SetSeconds" << endl;

    TimeCode tc = TimeCode(8, 5, 9);
    tc.SetSeconds(30);

    assert(tc.ToString() == "8:5:30");

    try{
        tc.SetSeconds(60);
        assert(false);
    }
    catch(const invalid_argument& e){
    }

    assert(tc.ToString() == "8:5:30");

    cout << "PASSED!" << endl << endl;
}

void TestGetTimeCodeAsSeconds(){
    cout << "Testing GetTimeCodeAsSeconds" << endl;

    TimeCode tc = TimeCode(3, 17, 42);

    assert(tc.GetTimeCodeAsSeconds() == 11862);

    cout << "PASSED!" << endl << endl;
}

void TestCopyConstructor(){
    cout << "Testing Copy Constructor" << endl;

    TimeCode tc1 = TimeCode(3, 17, 42);
    TimeCode tc2 = TimeCode(tc1);

    assert(tc2.ToString() == "3:17:42");

    cout << "PASSED!" << endl << endl;
}

void TestReset(){
    cout << "Testing Reset" << endl;

    TimeCode tc = TimeCode(5, 20, 30);
    tc.reset();

    assert(tc.ToString() == "0:0:0");

    cout << "PASSED!" << endl << endl;
}

void TestAdd(){
    cout << "Testing Add" << endl;

    TimeCode tc1 = TimeCode(1, 15, 22);
    TimeCode tc2 = TimeCode(2, 9, 5);

    TimeCode tc3 = tc1 + tc2;

    assert(tc3.ToString() == "3:24:27");

    TimeCode tc4 = TimeCode(1, 15, 55); //Rollover
    TimeCode tc5 = TimeCode(0, 1, 25);

    TimeCode tc6 = tc4 + tc5;

    assert(tc6.ToString() == "1:17:20");

    cout << "PASSED!" << endl << endl;
}

void TestMultiply()
{
    cout << "Testing Multiply" << endl;

    TimeCode tc = TimeCode(1, 0, 0);

    TimeCode tc2 = tc * 2;
    assert(tc2.ToString() == "2:0:0");

    TimeCode tc3 = tc * 0.5;
    assert(tc3.ToString() == "0:30:0");

    try{
        TimeCode tc4 = tc * -1;
        assert(false);
    }
    catch(const invalid_argument& e){
    }

    cout << "PASSED!" << endl << endl;
}

void TestDivide(){
    cout << "Testing Divide" << endl;

    TimeCode tc = TimeCode(2, 0, 0);

    TimeCode tc2 = tc / 2;
    assert(tc2.ToString() == "1:0:0");

    TimeCode tc3 = tc / 4;
    assert(tc3.ToString() == "0:30:0");

    try{
        TimeCode tc4 = tc / 0;
        assert(false);
    }
    catch(const invalid_argument& e){
    }

    cout << "PASSED!" << endl << endl;
}

void TestDifferentComparisons()
{
    cout << "Testing Comparisonss" << endl;

    TimeCode tc1 = TimeCode(1, 0, 0);
    TimeCode tc2 = TimeCode(1, 0, 0);
    TimeCode tc3 = TimeCode(2, 0, 0);

    assert(tc1 == tc2);
    assert(tc1 != tc3);

    assert(tc1 < tc3);
    assert(tc1 <= tc2);
    assert(tc1 <= tc3);

    assert(tc3 > tc1);
    assert(tc3 >= tc1);
    assert(tc1 >= tc2);

    cout << "PASSED!" << endl << endl;
}
	
int main(){
	
	TestComponentsToSeconds();
	TestDefaultConstructor();
	TestComponentConstructor();
	TestGetComponents();
	
	// Many othere test functions...
	
	cout << "PASSED ALL TESTS!!!" << endl;
	return 0;
}
