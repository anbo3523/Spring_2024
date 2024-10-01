#include <iostream>
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "../code/array_double.hpp"

using namespace std;


int main(int argc, char* argv[])
{
    //We are taking the command-line arguments and storing them in the below variables
    string fileName = argv[1];
    string location = argv[2];
    string airline = argv[3];
    int startAge = stoi(argv[4]);
    int endAge = stoi(argv[5]);

    //taking the name stored in fileName and opening the file. Also checking if we are able to open the file, if unsucessful, print error.
    ifstream inputFile(fileName);

    if (!inputFile.is_open())
    {
        cerr << "An error occurred. Could not open the file." << endl;
        return 1;
    }

    //initial capacity of dynamic array
    const int initialCapacity = 10;
    //dynamically allocating an array to the heap. The size is currently set to initialCapacity. passengers points to the first element of this array
    AirlinePassenger *passengers = new AirlinePassenger[initialCapacity];
    //keeping track of the current capacity of the dynamic array
    int arrCapacity = initialCapacity;
    //variable that is representing current index where a new "AirlinePassenger" record will be added
    int recordIdx = 0;
    //Count how many times the dynamic array doubled
    int doublingCounter = 0;

    //array to hold query parameters which will be used to process the data from the file
    string queryParams[6] = {location, airline, to_string(startAge), "","",to_string(endAge)};

    //calling function parseFile and passing arguments
    parseFile(inputFile, queryParams, passengers, arrCapacity, recordIdx, doublingCounter);

    inputFile.close();

    cout << "Array doubled: " << doublingCounter << endl;
    cout << "Total number of passengers returned after the query: " << recordIdx << endl;
    
    //calling function printQueriedPassengers which will print all the passengers based off of our parameters
    printQueriedPassengers(passengers, recordIdx);

    //Removing passengers from heap
    delete[] passengers;

    return 0;
}
