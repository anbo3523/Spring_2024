
#include "BrowserHistory.hpp"

BrowserHistory::BrowserHistory()
{
    // No changes needed
}

BrowserHistory::~BrowserHistory()
{
    // No changes needed
}

/*
 * Purpose: Has to detect if a defect is present in the linkedlist pointed by head
 * @param none
 * @return integer length of defect if one exists. If defect not present return -1
 */
int BrowserHistory::findDefectLength(){
    
    WebPage* slow = head;
    WebPage* fast = head;

    //traversing the list
    while (fast != nullptr && fast -> next != nullptr) {
        slow = slow -> next; //moving 1 node
        fast = fast -> next -> next; //moving 2 nodes
        if (slow == fast){
            //if slow meets fast (slow == fast), it means there is a defect
            int length = 0;
            do{
                length++;
                slow = slow->next;
            } while (slow != fast);
            return length;
        }
    }
    //will return 0 if fast reaches nullptr
    return -1;
}

/*
 * Purpose: Has to remove all the WebPage nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void BrowserHistory::removeWebPages(int start, int end){

    // TODO START ===================================================

    //checking if Browser history is empty
    if (head == nullptr){
        cout << "Browsing history is Empty" << endl;
        return;
    }

    int len = 0;
    WebPage* current = head;
    while (current != nullptr){
        len++;
        current = current -> next;
    }

    if (start < 1 || end > len || start > end){
        cout << "Invalid start or end values" << endl;
        return;
    }

    //when start if first node
    if (start == 1){
        for (int i=0; i < end; ++i){
            WebPage* temp = head;
            head = head -> next;
            delete temp;
        }
    }
    else{
        WebPage* prev = head;
        for (int i = 1; i < start - 1; ++i){
            prev = prev -> next;
        }

        WebPage* current = prev -> next;
        for (int i = start; i <= end; ++i){
            WebPage* temp = current;
            current = current -> next;
            delete temp;
        }

        prev -> next = current;
    }
    }
    // TODO END ===================================================


/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void BrowserHistory::mergeTwoHistories(WebPage *headOne, WebPage * headTwo){

    // TODO START =============================================
    if (headOne == nullptr && headTwo == nullptr){
        head = nullptr;
        return;
    }

    if (headOne == nullptr && headTwo != nullptr){
        head = headTwo;
        return;
    }
    
    if (headTwo == nullptr && headOne != nullptr){
        head = headOne;
        return;
    }

    WebPage* currentOne = headOne;
    WebPage* currentTwo = headTwo;
    head = currentOne;

    while (currentOne != nullptr && currentTwo != nullptr){
        WebPage* nextOne = currentOne -> next;
        WebPage* nextTwo = currentTwo -> next;

        currentTwo -> next = currentOne -> next;
        currentOne -> next = currentTwo;

        currentOne = nextOne;
        currentTwo = nextTwo;
        
    }

    if (currentTwo != nullptr){
        WebPage* current = head;
        while (current -> next != nullptr){
            current = current -> next;
        }
        current -> next = currentTwo;
    }
    // TODO END ==================================================
}
