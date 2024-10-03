#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

ShowCatalog::ShowCatalog() {
    root = nullptr;
}
void destroyRecursive(ShowItem* s);

ShowCatalog::~ShowCatalog() {
    destroyRecursive(root);
    root = nullptr;
}
//helper function for destructor. starts off with 
void destroyRecursive(ShowItem* node){
    if (node){
        destroyRecursive(node -> left);
        destroyRecursive(node -> right);
        delete node;
    }
}

//helper fuction for printShowCatalog. Will traverse the tree in preorder and print the value at that node. 
void preorderTraversal(ShowItem* s){
    if (s != nullptr){
        cout << "Show: " << s -> title << " " << s -> userRating << endl;

        //traversing the left side of the tree
        preorderTraversal(s -> left);

        //traversing the right side of the tree
        preorderTraversal(s -> right);
    }
}
void ShowCatalog::printShowCatalog() {
    if (root == nullptr){
        cout << "Tree is Empty. Cannot print" << endl;
    }
    else{
        //starting preordertraversal from the root
        preorderTraversal(root);
    }
}
ShowItem* findShow(ShowItem* node, string title){
    if (node == nullptr || node -> title == title){
        return node;
    }
    if (title < node -> title){
        return findShow(node -> left, title);
    }
    else{
        return findShow(node -> right, title);
    }
}
void ShowCatalog::getShow(string title) {
    ShowItem* node = findShow(root, title);
    if (node == nullptr){
        cout << "Show not found." << endl;
    }
    else{
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << node -> title << endl;
        cout << "Year :" << node -> year << endl;
        cout << "Show Rating :" << node -> showRating << endl;
        cout << "User Rating :" << node -> userRating << endl;
    }
}
ShowItem* addShowItemHelper(ShowItem* node, string title, int year, string showRating, float userRating){
    if (node == nullptr){
        return new ShowItem(title, year, showRating, userRating);
    }

    if(title < node -> title){
        node -> left = addShowItemHelper(node -> left, title, year, showRating, userRating);
    }
    else{
        node -> right = addShowItemHelper(node -> right, title, year, showRating, userRating);
    }

    return node;
}
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating) {
    root = addShowItemHelper(root, title, year, showRating, userRating);
}

void printLeafNodesHelper(ShowItem* node){
    if(node!= nullptr){
        if (node -> left == nullptr && node -> right == nullptr){
            cout << node -> title << endl;
        }
        else{
            printLeafNodesHelper(node -> left);
            printLeafNodesHelper(node -> right);
        }
    }
}
void ShowCatalog::printLeafNodes() {
    printLeafNodesHelper(root);
}
void searchShowsHelper(ShowItem* node, char titleChar){
    if(node != nullptr){
        if(node -> title[0] == titleChar){
            cout << node -> title << "(" << node -> year << ") " << node -> userRating << endl;
        }
        searchShowsHelper(node -> left, titleChar);
        searchShowsHelper(node -> right, titleChar);
    }
}
void ShowCatalog::searchShows(char titleChar) {
    cout << "Shows that starts with " << titleChar << ":" << endl;
    searchShowsHelper(root, titleChar);
}
void displayNumShowRatingHelper(ShowItem* node, string showRating, int &count){
    if (node != nullptr){
        if (node -> showRating == showRating){
            count++;
        }
        displayNumShowRatingHelper(node -> left, showRating, count);
        displayNumShowRatingHelper(node -> right, showRating, count);
    }
}
void ShowCatalog::displayNumShowRating(int &count, string showRating) {
    count = 0;
    displayNumShowRatingHelper(root, showRating, count);
}
