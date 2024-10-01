/*************************************************************/
/*                BrowserHistory Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of BrowserHistory    */
/*     This class uses a linked-list of WebPage structs to   */
/*     represent the schedule of web pages                   */
/*************************************************************/

#include "browserHistory.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
BrowserHistory::BrowserHistory() {
    /*
    DO NOT MODIFY THIS
    This constructor is already complete. 
    */
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    /* finished. do not touch. */
    return (head == NULL);
}

/*
 * Purpose: prints the current list of pages 
 * in the given format.
 * [ID::1]-(URL::url1) -> ... -> NULL
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() {
    cout << "== CURRENT BROWSER HISTORY ==" << endl;
    if (isEmpty()){
        cout << "Empty History" << endl;
    }
    else{
        WebPage* tmp = head;
        while (tmp != nullptr){
            cout  <<  "[ID:: "  <<  tmp->id  <<  "]-(URL::"  <<  tmp->url  <<  ") -> ";
            tmp = tmp -> next;
        }
    }
    cout  <<  "NULL\n===\n";
}

/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) {
    if (previousPage == nullptr){
        //Inserting at the beginning.
        newPage -> next = head;
        head = newPage;
        cout  <<  "adding: "  <<  "["  <<  newPage->id  <<  "]-"  <<  newPage->url  <<  " (HEAD)\n";
    }
    else{
        //Inserting after previousPage
        newPage -> next = previousPage -> next;
        previousPage -> next = newPage;
        cout  <<  "adding: "  <<  "["  <<  newPage->id  <<  "]-"  <<  newPage->url  <<  " (prev: "  <<  "["  <<  previousPage->id  <<  "])\n";
    }   
}

/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {
    //creating instances of WebPage structs and adding them to browserhistory linked lists
    WebPage* page1 = new WebPage;
    page1 -> id = 10;
    page1 -> views = 0;
    page1 -> url = "https://www.colorado.edu/";
    page1 -> owner = "";
    addWebPage (nullptr,page1);

    WebPage* page2 = new WebPage;
    page2 -> id = 11;
    page2 -> views = 0;
    page2 -> url = "https://www.wikipedia.org/";
    page2 -> owner = "";
    addWebPage (page1,page2);

    WebPage* page3 = new WebPage;
    page3 -> id = 12;
    page3 -> views = 0;
    page3 -> url = "https://brilliant.org/";
    page3 -> owner = "";
    addWebPage (page2,page3);

    WebPage* page4 = new WebPage;
    page4 -> id = 13;
    page4 -> views = 0;
    page4 -> url = "https://www.khanacademy.org/";
    page4 -> owner = "";
    addWebPage (page3,page4);

    WebPage* page5 = new WebPage;
    page5 -> id = 14;
    page5 -> views = 0;
    page5 -> url = "https://www.numberphile.com/";
    page5 -> owner = "";
    addWebPage (page4,page5);
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) {
    //Traversing list
    WebPage* current = head;
    while (current != nullptr){
        if (current -> id == id)
        return current;
        current = current -> next;
    }
    return nullptr;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) {
    WebPage* current = head;
    while (current != nullptr){
        if (current -> url == url){
        return current;
        }
        current = current -> next;
    }
    return nullptr;
}

/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {
    WebPage* page = searchPageByURL(url);
    if (page != nullptr){
        page -> owner = owner;
        cout  <<  "The owner ("  <<  owner  <<  ") has been added for the ID - "<<  page->id  <<  "\n";
    }
    else{
        cout << "Page not found\n";
    }
}

void BrowserHistory::updateViews(string url) {
    WebPage* current = head;
    while (current != nullptr){
        current -> views++;
        current = current -> next;
    }
}
