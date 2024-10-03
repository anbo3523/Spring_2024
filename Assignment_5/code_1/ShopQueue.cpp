#include "ShopQueue.hpp"
#include <iostream>

using namespace std;

ShopQueue::ShopQueue() {
   queueFront = nullptr;
   queueEnd = nullptr;
}

ShopQueue::~ShopQueue() {
   while (!isEmpty()){
      dequeue();
   }
}

/**
 * Checks if the shopqueue is empty or not
 * @returns Whether its empty or not
 */ 
bool ShopQueue::isEmpty() {
   return queueFront == nullptr;
}

/**
 * Looks at the shopqueue and returns the most 'urgent' order on the queue. No elements should be removed.
 * @return A customer order
 */
CustomerOrder* ShopQueue::peek() {
   if (isEmpty()){
      cout << "Queue empty, cannot peek!\n";
      return nullptr;
   }
   return queueFront;
}

/**
 * Adds the customers to the queue.
 * @param name The name of the customer to add.
 * @param num_pancakes The number of pancakes to add
 * @param type_of_pancake The type of pancake to add. 
 * 
 */
void ShopQueue::enqueue(string name, int num_pancakes, int type_of_pancake) {
   CustomerOrder* newOrder = new CustomerOrder;
   newOrder -> name = name;
   newOrder -> number_of_pancakes = num_pancakes;
   newOrder -> type_of_pancakes = type_of_pancake;
   newOrder -> next = nullptr;

   if (isEmpty()){
      queueFront = newOrder;
      queueEnd = newOrder;
   }
   else{
      queueEnd -> next = newOrder;
      queueEnd = newOrder;
   }
}

void ShopQueue::dequeue() {
   if(isEmpty()){
      cout << "Queue empty, cannot dequeue!" << endl;
      return;
   }
   CustomerOrder* temp = queueFront;
   queueFront = queueFront -> next;
   delete temp;

   if(queueFront == nullptr){
      queueEnd = nullptr;
   }
}

/**
 * Should return the total number of customers in the queue. 
 * @returns The total number of elements
 */
int ShopQueue::queueSize(){
   int size = 0;
   CustomerOrder* current = queueFront;
   while (current != nullptr && size < 20){
      size++;
      current = current -> next;
   }
   return size;
}

/**
 * Just returns the end of the queue. Used for testing. Do not touch! :)
 */ 
CustomerOrder* ShopQueue::getQueueEnd(){
   return queueEnd;
}