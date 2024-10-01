#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/browserHistory.hpp"

using namespace std;

void displayMenu();

int main(int argc, char* argv[]) {

    // DO NOT MODIFY THIS.
    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }
    // DO NOT MODIFY ABOVE.

    BrowserHistory history;
    
    int option;

    do{
        displayMenu();
        cin >> option;
        cin.ignore();

        switch (option){
            case 1:{
                history.buildBrowserHistory();
                history.displayHistory();
                break;
            }
            case 2:{
                history.displayHistory();
                break;
            }
            case 3:{
                    string url, previousUrl;
                    int id;
                    cout << "Enter the new web page's url:\n";
                    getline(cin, url);

                    do{
                        cout << "Enter the new web page's id:\n";
                        cin >> id;
                        cin.ignore(); // Ignore newline character from previous cin

                        if (history.searchPageByID(id)){
                            cout << "This ID already exists. Try again.\n";
                        }
                    }
                    while (history.searchPageByID(id));

                        bool validPreviousUrl = false;
                        while(!validPreviousUrl){
                            cout<< "Enter the previous page's url (or First):\n";
                            getline(cin, previousUrl);

                            if(previousUrl == "First" || history.searchPageByURL(previousUrl) != nullptr){
                                validPreviousUrl = true;
                            }
                            else{
                                cout << "INVALID(previous page url)... Please enter a VALID previous page url!" << endl;
                            }
                        }


                        if (previousUrl == "First") {
                            // Adding the new page at the beginning
                            WebPage* newPage = new WebPage;
                            newPage -> id = id;
                            newPage -> url = url;
                            newPage -> views = 0;
                            newPage -> owner = ""; // Assuming owner is empty initially
                            history.addWebPage(nullptr, newPage);
                    } 
                    else{
                        // Adding the new page after the specified previous page
                        WebPage* previousPage = history.searchPageByURL(previousUrl);
                        if (previousPage != nullptr) {
                            WebPage* newPage = new WebPage;
                            newPage -> id = id;
                            newPage -> url = url;
                            newPage -> views = 0;
                            newPage -> owner = ""; // Assuming owner is empty initially
                            history.addWebPage(previousPage, newPage);
                        }
                        else {
                            cout << "INVALID (previous page url)... Please enter a VALID previous page url!" << endl;
                        }  
                    }
                    break;
            }
            case 4: {
                string url, owner;
                bool validURL = false;

                do{ 
                    cout << "Enter url of the web page to add the owner:\n";
                    getline(cin, url);

                    WebPage* page = history.searchPageByURL(url);
                    if (page){
                        cout << "Enter the owner:";
                        getline(cin, owner);
                        history.addOwner(url, owner);
                        validURL = true; //exit loop
                    }    
                    else{
                        cout << "Page not found. Try again.\n" << endl;
                    }   
                    }
                while (!validURL);

                    break; 
            }
            case 5: {
                string url;
                bool found = false;
                while (!found){
                    cout << "Enter url of the web page to check the view count: ";
                    getline(cin, url);
                    WebPage* page = history.searchPageByURL(url);
                    if(page != nullptr){
                        cout << "\nView count for URL - " << url << " is " << page -> views << endl;
                        found = true; //exiting loop if found
                    }
                    else{
                        cout << "\nPage not found. Try again." <<endl;
                    }
                }
                break;
            }
            case 6: {
                cout << "Quitting...Goodbye!\n";
                break;
            }
            }
        } 
        while (option != 6);
        return 0;
    }




/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    // COMPLETE: You DO NOT need to edit this
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build history " << endl;
    cout << " 2. Display history " << endl;
    cout << " 3. Add web page " << endl;
    cout << " 4. Add owner" << endl;
    cout << " 5. View count for a web page" << endl;
    cout << " 6. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
