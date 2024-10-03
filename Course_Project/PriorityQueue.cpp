#include "PriorityQueue.hpp"
#include <limits.h>

using namespace std;

void swap(ReviewInfo *a, ReviewInfo *b)
{
    ReviewInfo temp = *a;
    *a = *b;
    *b = temp;
}

/*
Constructor for our MinHeap implementation
*/
PriorityQ::PriorityQ(int cap)
{
    heapArr = new ReviewInfo[cap];
    capacity = cap;
    currentSize = 0;
}

/*
Destructor
*/
PriorityQ::~PriorityQ()
{
    delete[] heapArr;
}

/*
Finds the parent of a node, given its index.
*/
int PriorityQ::parent(int index)
{
   return (index - 1) / 2;
}

/*
Returns the left child of a node.
*/
int PriorityQ::leftChild(int index)
{
    return ((2 * index) + 1);
}

/*
Returns the right child of a code.
*/
int PriorityQ::rightChild(int index)
{
    return ((2 * index) + 2);
}

void PriorityQ::peek()
{
    //What is at the top of the queue? (in bucket 0)
    if(currentSize > 0){
        cout << "Restaurant Name: " << heapArr[0].restaurantName << endl;
        cout << "Customer: " << heapArr[0].customer << endl;
        cout << "Review: " << heapArr[0].review << endl;
        cout << "Time: " << heapArr[0].time << endl;        
    }
    else{
        cout << "No record found" << endl;
    }
}

void PriorityQ::heapify(int i)
{
    int largest = i;
    int left = leftChild(i);
    int right = rightChild(i);

    if (left < currentSize && heapArr[left].time > heapArr[largest].time)
        largest = left;

    if (right < currentSize && heapArr[right].time > heapArr[largest].time)
        largest = right;

    if (largest != i){
        swap(heapArr[i], heapArr[largest]);
        heapify(largest);
    }
}

void PriorityQ::insertElement(ReviewInfo restaurant)
{
    //check if heap max has been reached (50)
    if (currentSize >= capacity){
        cout << "Maximum heap size reached. Cannot insert anymore." << endl;
        return;
    }
    //if it did not reach the max, then execute below
    heapArr[currentSize] = restaurant;
    int current = currentSize;
    currentSize++;

    while (current != 0 && heapArr[parent(current)].time < heapArr[current].time){
        swap(heapArr[current], heapArr[parent(current)]);
        current = parent(current);
    }
}
    

/*
Prints the elements in the heap
*/
void PriorityQ::print()
{
    for (int i = 0; i < currentSize; i++){
        cout << "\t" << "Customer: " << heapArr[i].customer << endl;
        cout << "\t" << "Review: " << heapArr[i].review << endl;
        cout << "\t" << "Time: " << heapArr[i].time << endl;
        cout << "\t" << "=====" << endl;
    }
}

// Method to remove minimum element (or root) from min heap
void PriorityQ::pop()
{
    if (currentSize == 0)
        return;
    
    heapArr[0] = heapArr[currentSize - 1];
    currentSize--;
    heapify(0);
}
