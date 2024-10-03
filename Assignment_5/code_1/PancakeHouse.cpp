/*************************************************************/
/*                PancakeHouse Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of PancakeHouse    */
/*************************************************************/

#include "PancakeHouse.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;
int const PancakeHouse::pancake_types[] = {1, 2, 5, 3, 7};


/**
 * Constructor for the Pancake House
 */
PancakeHouse::PancakeHouse() {
    profit = 0;
    pancakesCooked = 0;
    cashRegister = new Register();
    shopQueue = new ShopQueue();
}

/**
 * Destructor for the pancake house. Removes the register and shopQueue.
 */
PancakeHouse::~PancakeHouse(){
    delete cashRegister;
    delete shopQueue;
}

/**
 * Gets the stack.
 * @returns The cash register
 */
Register* PancakeHouse::getStack(){
    return cashRegister;
}

/**
 * Gets the queue.
 * @returns The shop queue
 */
ShopQueue* PancakeHouse::getQueue() {
    return shopQueue;
}

/**
 * Gets the profit class variable
 * @returns The profit
 */
int PancakeHouse::getProfit(){
    return profit;
}

/**
 * This function should add orders to the queue. 
 * @param name The name of the person to be added
 * @param number_of_pancakes The total number of pancakes to be ordered
 * @param type_of_pancakes The type of pancake to be cooked (i.e., the 'price' of the pancake). There are 5 types, anything outside of the range 1-5 should be rejected.
 */
void PancakeHouse::addOrder(string name, int number_of_pancakes, int type_of_pancakes) {
    if (type_of_pancakes <1 || type_of_pancakes >5){
        return;
    }    
    shopQueue -> enqueue(name, number_of_pancakes, type_of_pancakes);
}

/**
 * This should cook an order of pancakes. By removing an element from the queue (if one exists) it should then calculate the price
 * of an order (num pancakes*type price). The price should then be pushed onto the stack if a space exists.
 * 
 */
void PancakeHouse::cookPancakes() {
    CustomerOrder* order = shopQueue -> peek();
    if (order != nullptr){
        int price = order -> number_of_pancakes * pancake_types[order->type_of_pancakes - 1];
        if (!cashRegister -> isFull()){
            cashRegister -> push(price);
            pancakesCooked += order -> number_of_pancakes;
            shopQueue -> dequeue();
    }
    }
}

/*
 * This function will cancel the existing order in the queue
 */
void PancakeHouse::strikeOrder(){
    shopQueue -> dequeue();
}

/*
 * Takes out the recent order from stack, displays the money refunded and takes away from the profit class variable
 */
void PancakeHouse::refundOrder(){
    int refund = cashRegister->pop();
    if (refund != -1){
    cout << "Money refunded = " << refund << endl;
    }
    else{
        cout << "No money in the cash register!" << endl;
    }
}


/**
 * Closes the shop for the day. Should remove the queue elements and remove all of the elements off of the register.
 */
void PancakeHouse::closeShop(){
    while (!shopQueue -> isEmpty()){
        shopQueue -> dequeue();
    }
    while (!cashRegister -> isEmpty()){
        cashRegister -> pop();
    }
}

/**
 * Should get the total profit that is contained in the register. Removes each element from the register and adds it to the 
 * profit variable.
 */
void PancakeHouse::updateTotalProfit(){
    while (!cashRegister -> isEmpty()){
        profit += cashRegister -> pop();
    }
}

/**
 * Runs through the order queue and prints each order. The queue elements should remain untouched!
 */
void PancakeHouse::printOrders(){
    CustomerOrder* current = shopQueue -> peek();
    while (current != nullptr){
        cout << "Customer name: " << current -> name << endl;
        cout << "Number of pancakes ordered: " << current -> number_of_pancakes << endl;
        cout << "Type of pancakes: " << current -> type_of_pancakes << endl;
        current = current -> next;
    }
}