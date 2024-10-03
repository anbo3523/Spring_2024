#include <iostream>
#include "hash.hpp"
#include "PriorityQueue.hpp"
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace std::chrono;

void displayMenu() // do not modify
{
    cout << "------------------" << endl;
    cout << "1: Build the data structure (execute this option one time)" << endl;
    cout << "2: Add a review" << endl;
    cout << "3: Retrieve most recent review for a restaurant" << endl;
    cout << "4: Pop most recent review for a restaurant" << endl;
    cout << "5: Print reviews for a restaurant" << endl;
    cout << "6: Display number of collisions" << endl;
    cout << "7: Display table results" << endl;
    cout << "8: Exit" << endl;
    cout << "------------------" << endl;
}

int main(int argc, char* argv[])
{
    if (argc <3)
    {
        cout<<"need correct number of arguments"<<endl;
    }
	
    string fname = argv[1]; //test.txt
    int tableSize = stoi(argv[2]); //array size of 5
    int ch = 0;
    string chs;
    HashTable ht(5); //calling contructor
	bool isBuilt = false;
    
    while(ch!=8)
    {
        displayMenu();
        cout << "Enter your choice >>";
        getline(cin, chs);
        ch = stoi(chs);
        switch (ch)
        {
            case 1:
			{
                //flag to check 
                if(isBuilt){
                    cout << "The data structure has already been built." << endl;
                }
                //ht.setup(filename); only call one time per execution so isBuilt is switched to true
                else{
                    ht.setup(fname);
                    isBuilt = true;
                }
				
				break;
            }
            case 2:
			{
                //Adding new review
                {
                    cout << "Restaurant Name: ";
                    string name, customer, review;
                    int time;
                    getline(cin, name);
                    cout << "Customer: ";
                    getline(cin, customer);
                    cout << "Review: ";
                    getline(cin, review);
                    cout << "Time: ";
                    cin >> time;
                    //clears out input buffer
                    cin.ignore();

                    //Creating instance of ReviewInfo for above info
                    ReviewInfo r{name, review, customer, time};
                    //insert into hash table
                    ht.insertItem(r);
                }
				break;
            }
            case 3:
			{
                //Retrieving most recent review via peek
                cout << "Restaurant Name: ";
                string name;
                getline(cin, name);
                node* n = ht.searchItem(name);
                if(n){
                    cout << "retrieved result" << endl;
                    n -> pq.peek();
                }
                else{
                    cout << "No record found." << endl;
                }
				break;
            }
            case 4:
			{
                //pop
                {
                    cout << "Restaurant Name: ";
                    string name;
                    getline(cin, name);
                    node* n = ht.searchItem(name);
                    if(n){
                        //printing top of pq
                        n -> pq.pop();
                    }
                    else{
                        cout << "No record found." << endl;
                    }
                }
				break;
            }
            case 5:
			{
                //displaying all reviews for given restaurant
				string restaurantName;
                cout << "Restaurant Name: ";
                getline(cin, restaurantName);
                node* n = ht.searchItem(restaurantName);
                if(n){
                    n -> pq.print();
                }
                else{
                    cout << "No record found" << endl;
                }
				break;
			}
            case 6:
                //collisions are after the first node
                cout << "Number of collisions: " << ht.getNumCollision() << endl;
                break;
            case 7:
                //display table
                ht.displayTable();
                break;
            case 8:
                //exit
                cout << "Exiting the program" << endl;
                return 0;
				break;
            default:
                cout << "Enter a valid option." << endl;
                break;
        }
    }
}
