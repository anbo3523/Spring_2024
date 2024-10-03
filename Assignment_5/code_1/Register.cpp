#include <iostream>
#include <cstdlib>
#include <iostream>
#include "Register.hpp"


using namespace std;

Register::Register(){
   top = 0;
}

/*
 * If the register is full or not
 * @returns 
 */
bool Register::isFull(){
   return top >= SIZE;
}

/*
 * Adds money to stack.
 * @param money: the type of pancake's price times the quantity
 */
void Register::push( int money ){
   if (!isFull()){
      a[top++] = money;
}
   else{
   cout << "Stack overflow: " << endl;
   }
}


/*
 * Checks if stack is full. 
 * @returns a bool
 */
bool Register::isEmpty(){
   return top == 0;
}

/*
 * Looping through the stack array to display amounts
 */
void Register::disp(){
   if (isEmpty()){
      cout << "Stack is empty" << endl;
      return;
   }
   cout << "top = " << top << endl;
   for (int i = top - 1; i >= 0; --i){
      cout << a[i] << endl;
   }
}

int Register::pop(){
   if (!isEmpty()){
      return a[--top];
   }
   cout << "Stack empty, cannot pop an item!" << endl;
   return -1;

}