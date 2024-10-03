// CPP program to implement hashing with chaining
#include <iostream>
#include "hash.hpp"
#include <sstream>

using namespace std;

node* HashTable::createNode(string restaurantName, node* next)
{
    //create node for the resturaunt
    /*
    struct node {
   string restaurantName; the sink
   PriorityQ pq; //currently empty, so create it of size 50

   struct node* next;
   */
    node* newNode = new node{restaurantName, PriorityQ(50), next};
    return newNode;
}

HashTable::HashTable(int bsize)
{
    //constructor
    tableSize = bsize;
    table = new node* [tableSize];
    for (int i = 0; i < tableSize; i++){
        table[i] = nullptr;
    }
    numCollision = 0;
}

HashTable::~HashTable()
{
    //destructor
    //iterating through the table to delete every entry
    //then freeing the space that was allocated for the table
    for (int i = 0; i < tableSize; i++){
        node* current = table[i];
        while (current != nullptr){
            node* prev = current;
            current = current -> next;
            delete prev;
        }
    }
    delete[] table;
}

void HashTable::displayTable()
{
    //iterating through table
    //printing first restauraunt and go through LL until reach NULL and go to next indices
    for (int i = 0; i < tableSize; i++){
        node* current = table[i];
        cout << i << "|";
        while (current != nullptr){
            cout << current -> restaurantName;
            if (current -> next != nullptr){
                cout << "-->";
            }
            current = current -> next;
        }
        cout << "->NULL" << endl;
    }
}

unsigned int HashTable::hashFunction(string restaurantName)
{
    //We are finding the Hash Value for the specific restaurant so we can store in the correct bin
    int hashVal = 0;
    //counting every character within the restaurant's name
    for (char c : restaurantName){
        hashVal += c;
    }
    //taking the result and mod with tableSize
    return hashVal % tableSize;
}

node* HashTable::searchItem(string restaurantName)
{
    //look for the resturaunt in the hashtable/LL
    int bucket = hashFunction(restaurantName);
    node* entry = table[bucket];

    while (entry != nullptr){
        //if restaurant found, return
        if (entry -> restaurantName == restaurantName)
            return entry;
        //go to next restaurant
        entry = entry -> next;
    }
    //will return nullptr if not found
    return nullptr;
}

void HashTable::insertItem(ReviewInfo restaurant)
{
    /*searchItem() // see if already in the hashtable/LL
    if found, don't createNode(),
    if null (does not exist) createNode()
    hashFunction(name) 
    above built the node, now we need to add the review to the LL
    pq.insertElement() will insert into the priority queue for that resturaunt */

    unsigned int hashValue = hashFunction(restaurant.restaurantName);
    node* current = table[hashValue];

    while (current != nullptr && current -> restaurantName != restaurant.restaurantName){
        current = current -> next;
    }

    //if restaurant found, we insert the review in the existing pq
    if(current != nullptr){
        current -> pq.insertElement(restaurant);
    }
    else{
            //if there is collision
            if(table[hashValue] != nullptr){
                numCollision++;
            }
            node* newNode = createNode(restaurant.restaurantName, table[hashValue]);
            newNode -> pq.insertElement(restaurant);
            table[hashValue] = newNode;
    }
}


void HashTable::setup(string fname)
{
    //read from the file
    ifstream file(fname);
    //if failed - error message
    if (!file.is_open()){
        return;
    }
    //stringstream - while loop - getline
    string line;
    while (getline(file, line)){
        stringstream ss(line);
        string restaurantName, review, customer, timeStr;
        getline(ss, restaurantName, ';');
        getline(ss, review, ';');
        getline(ss, customer, ';');
        getline(ss, timeStr, ';');

        //Creating struct for the restaurant from file
        ReviewInfo restaurant = {restaurantName, review, customer, stoi(timeStr)};
        
        insertItem(restaurant);
    }
    file.close();
}