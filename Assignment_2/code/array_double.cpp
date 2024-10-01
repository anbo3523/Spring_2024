#include "array_double.hpp"
#include <sstream>

/**
 * Reads the input file line by line, takes in the
 * query params along with reference of the passengers array
 */
void parseFile(ifstream& input, string queryParams[], AirlinePassenger *&passengers, int &arrCapacity, int &recordIdx, int &doublingCounter) {
    string line;
    
    //loop to read each line from file
    while (getline(input, line))
    {
        stringstream ss(line);
        AirlinePassenger newPassenger;

        //reading line until reaches comma and stores in respective variable.
        getline(ss, newPassenger.name, ',');
        getline(ss, newPassenger.airline, ',');
        getline(ss, newPassenger.location, ',');
        ss >> newPassenger.age; 

        //calling the function isPassengerQueried and sees if newPassenger satifies the conditions (location, airline, age) The function will either return true or false depending on if the passenger meets the criteria.
        if (isPassengerQueried(newPassenger, queryParams[0], queryParams[1], stoi(queryParams[2]), stoi(queryParams[5])))
        {
            addPassenger(passengers, newPassenger, arrCapacity, recordIdx, doublingCounter);
        }

    }
}

/**
 * Checks if the current passenger has their age in 
 * the queried age range, and their location and 
 * the airline matching with the queried ones.
 */
bool isPassengerQueried(AirlinePassenger passenger, string queryLocation, string queryAirline, int startAge, int endAge) {
    //returning true or false based on whether the expressions on the left matches with the expression on the right. If ALL is true, it will return a true. if anything is false, it will return false
    return passenger.location == queryLocation &&
           passenger.airline == queryAirline &&
           passenger.age >= startAge &&
           passenger.age <= endAge;
}

/**
 * Takes in a reference to an array of structs (passengers) 
 * and the current arrayCapacity. It doubles the size 
 * of the array by making a new array of size the current
 * size and copying the elements of the old one. 
 */
void resizeArr(AirlinePassenger *&passengers, int *arraySize) {
   //calculating new size for array
   int newSize = (*arraySize) * 2;
   //creating pointer with address of AirlinePassenger that points to the new array on the heap
   AirlinePassenger* newArr = new AirlinePassenger[newSize];

   //taking information from old array and inputting it into new array as long as i is less than arraySize
   for (int i = 0; i < *arraySize; ++i)
   {
    newArr[i] = passengers[i];
   }
   //Removing old array on the heap since we no longer need it
   delete[] passengers;
   //Updating the pointer "passengers" to point at the new array
   passengers = newArr;
   //Updating the array size so we can keep track of it
   *arraySize = newSize; 
}

/**
 * Append the new record to the passengers array. Here we double the 
 * array capacity whenever it is full. Assuming that the passenger to
 * be added is already checked if it satisfies the query params.
 */
void addPassenger(AirlinePassenger *&passengers, AirlinePassenger airlinePassenger, int &arrCapacity, int &recordIdx, int &doublingCounter) 
{
    //Checking if recordIdx is equal to arrCapacity. This means we need to increase the size of the array so we will call the function resizeArr
   if (recordIdx == arrCapacity) 
   {
    resizeArr(passengers, &arrCapacity);
    doublingCounter++;
   }
   //adding airlinePassenger to the array passengers at the current position (recordIdx) and then moving on to the next position.
   passengers[recordIdx++] = airlinePassenger;
}

/**
 * Sorting the array of structs in descending order of age.
 * Tie breaker: Alphabetical order of names.
 */
void sortPassengers(AirlinePassenger *passengers, int length) 
{
    //bubble sort - goes through the list and compares each pair of items next to each other and sorts them if they are in the wrong order. This is repeated until the entire list is sorted correctly.
    for (int i = 0; i < length - 1; i++)
    {
        for(int j = 0; j < length - i - 1; j++)
        {
            //Compares the age of the two lines. if the first is greater than the next, it swaps the positions of the two lines in the array.
            if(passengers[j].age < passengers[j+1].age || (passengers[j].age == passengers[j+1].age && passengers[j].name > passengers[j+1].name))
            {
                swap(passengers[j], passengers[j+1]);
            }
        }
    }
}

/**
 * Call the sortPassenger function and print the name and the age of the passenger.
 */
void printQueriedPassengers(AirlinePassenger *passengers, int numOfRecords) {
    //Calling sortPassengers to sort our queried passengers
    sortPassengers(passengers, numOfRecords);

    cout << "Queried Passengers" << endl;
    cout << "---------------------------------------" << endl;
    for (int i = 0; i < numOfRecords; ++i)
    {
        //printing name and age of passenger
        cout << passengers[i].name << " " << passengers[i].age << endl;
    }
}
