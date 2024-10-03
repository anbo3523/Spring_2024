#include "ShowCatalog.hpp"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::ShowCatalog()
{
    root = nullptr;
}

/* Completed functions. DO NOT MODIFY*/
void destroyNode(ShowItem *current)
{
    if (current != nullptr)
    {
        destroyNode(current->left);
        destroyNode(current->right);

        delete current;
        current = nullptr;
    }
}

/* Completed functions. DO NOT MODIFY*/
ShowCatalog::~ShowCatalog()
{
    destroyNode(root);
}

/* Completed functions. DO NOT MODIFY*/
void printShowHelper(ShowItem *m)
{
    if (m != nullptr)
    {
        cout << "Show: " << m->title << " " << m->userRating << endl;
        printShowHelper(m->left);
        printShowHelper(m->right);
    }
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::printShowCatalog()
{
    if (root == nullptr)
    {
        cout << "Tree is Empty. Cannot print" << endl;
        return;
    }
    printShowHelper(root);
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *getShowHelper(ShowItem *current, string title)
{
    if (current == NULL)
        return NULL;

    if (current->title == title)
        return current;

    if (current->title > title)
        return getShowHelper(current->left, title);

    return getShowHelper(current->right, title);
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::getShow(string title)
{
    ShowItem *node = getShowHelper(root, title);
    if (node != nullptr)
    {
        cout << "Show Info:" << endl;
        cout << "==================" << endl;
        cout << "Title :" << node->title << endl;
        cout << "Year :" << node->year << endl;
        cout << "Show Rating :" << node->showRating << endl;
        cout << "User Rating :" << node->userRating << endl;
        return;
    }

    cout << "Show not found." << endl;
}

/* Completed functions. DO NOT MODIFY*/
ShowItem *addNodeHelper(ShowItem *current, ShowItem *newNode)
{
    if (current == nullptr)
    {
        return newNode;
    }

    if (current->title > newNode->title)
    {
        current->left = addNodeHelper(current->left, newNode);
    }
    else
    {
        current->right = addNodeHelper(current->right, newNode);
    }

    return current;
}

/* Completed functions. DO NOT MODIFY*/
void ShowCatalog::addShowItem(string title, int year, string showRating, float userRating)
{
    if (root == nullptr)
    {
        root = new ShowItem(title, year, showRating, userRating);
        return;
    }

    root = addNodeHelper(root, new ShowItem(title, year, showRating, userRating));
}
ShowItem* minValueNode(ShowItem* node)
{
    ShowItem* current = node;

    while (current && current -> left != nullptr)
        current = current -> left;
    
    return current;
}
void removeShowHelper(ShowItem*& root, std::string title)
{
    if(root == nullptr)
        return;

    if(title < root -> title)
        removeShowHelper(root -> left, title);
    else if (title > root -> title)
        removeShowHelper(root -> right, title);
    else{
        //Node is leaf
        if(root -> left == nullptr && root -> right == nullptr){
            delete root;
            root = nullptr;
        }
        //Node has 1 left child
        else if (root -> right == nullptr){
            ShowItem* temp = root;
            root = root -> left;
            delete temp;
        }
        //node has 1 right
        else if (root -> left == nullptr){
            ShowItem* temp = root;
            root = root -> right;
            delete temp;
        }
        //Both left and right
        else{
            ShowItem* successor = root -> right;
            while (successor -> left != nullptr){
                successor = successor -> left;
            }

            root -> title = successor -> title;
            root -> year = successor -> year;
            root -> showRating = successor ->showRating;
            root -> userRating = successor -> userRating;

            removeShowHelper(root -> right, successor -> title);
        }
    }
}
void ShowCatalog::removeShow(std::string title)
{
    removeShowHelper(root, title);
}
ShowItem* getParent(ShowItem* root, std::string title)
{
    if(root == nullptr || root -> title == title)
        return nullptr;
    
    ShowItem* parent = nullptr;
    while (root != nullptr){
        if(title < root -> title){
            parent = root;
            root = root -> left;
        }
        else if (title > root -> title){
            parent = root;
            root = root -> right;
        }
        else{
            break;
        }
    }
    return parent;
}
ShowItem* rightRotateHelper(ShowItem* root, std::string title)
{
    if(root == nullptr)
        return root;
    
    ShowItem* node = getShowHelper(root, title);

    if(node == nullptr || node -> left == nullptr)
        return root;

    ShowItem* y = node -> left;
    node -> left = y -> right;
    y -> right = node;

    ShowItem* parent = getParent(root, title);
    if(parent == nullptr)
        return y;
    if(parent -> left == node)
        parent -> left = y;
    else
        parent -> right = y;

    return root == node ? y : root;
}
void ShowCatalog::rightRotate(std::string title)
{
    root = rightRotateHelper(root, title);
}

ShowItem* leftRotateHelper(ShowItem* root, std::string title)
{
    if(root == nullptr)
        return nullptr;
    
    ShowItem* node = getShowHelper(root, title);
    if (node == nullptr || node -> right == nullptr)
        return root;
    
    ShowItem* y = node -> right;
    node -> right = y -> left;
    y -> left = node;

    ShowItem* parent = getParent(root, title);
    if(parent == nullptr)
        return y;
    if (parent -> left == node)
        parent -> left = y;
    else
        parent -> right = y;
    return root == node ? y : root;
}
void ShowCatalog::leftRotate(std::string title)
{
    root = leftRotateHelper(root, title);
}
