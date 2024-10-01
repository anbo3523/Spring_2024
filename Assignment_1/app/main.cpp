#include <iostream>
#include <fstream>
#include "../code/fundamentals.hpp"
#include <sstream>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    // TODO
    ifstream inputFile(argv[1]);
    if(!inputFile.is_open())
    {
        cout << "There was an error opening the file:" << argv[1] << endl;
        return 1;
    }

    const int MAX_STOCKS = 6;
    stockInfo stocks[MAX_STOCKS];
    int currentIndex = 0;

    string line;
    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string companyName;
        double prices[5];

        getline(ss, companyName, ',');
        for (int i = 0; i < 5; ++i)
        {
            string priceStr;
            getline(ss, priceStr, ',');
            prices[i] = stod(priceStr);
        }

        insertStockInfo(stocks, companyName, prices, currentIndex);
        currentIndex++;
    }

    inputFile.close();

    //Display and store stocks
    ofstream outputFile(argv[2]);
    for (int i = 0; i < currentIndex; ++i)
    {
        displaySortedStocks(stocks[i], outputFile);
    }

    outputFile.close();

    return 0;
}