#include "fundamentals.hpp"

void insertStockInfo(stockInfo stocks[], string company_name, double stock_prices_arr[], int index) {
    stockInfo newStock;
    newStock.company_name = company_name;

    for (int i=0; i < 5; ++i)
    {
        newStock.stock_prices_arr[i] = stock_prices_arr[i];
    }

    //Calculating Average
    double sum = 0.0;
    for (int i=0; i < 5; ++i)
    {
        sum += stock_prices_arr[i];
    }
    
    newStock.average = sum / 5.0;

    //Add struct to array
    stocks[index] = newStock;
    return;
}

void displaySortedStocks(stockInfo stock, ofstream& file){
    //sorting stocks in ascending order
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4 - i; ++j)
        {
            if (stock.stock_prices_arr[j] > stock.stock_prices_arr[j+1])
            {
                //Swapping
                double temp = stock.stock_prices_arr[j];
                stock.stock_prices_arr[j] = stock.stock_prices_arr[j+1];
                stock.stock_prices_arr[j+1] = temp;
            }
        }
    }
    
    //Print to standard output
    cout << stock.company_name << "," << stock.average << ",";
    for (int i = 0; i < 5; ++i)
    {
        cout << stock.stock_prices_arr[i];
        if (i <4)
        {
            cout << ",";
        }
    }
    cout << endl;

    //Print to file
    file << stock.company_name << "," << stock.average << ",";
    for (int i = 0; i < 5; ++i)
    {
        file << stock.stock_prices_arr[i];
        if (i < 4)
        {
            file << ",";
        }
    }
    file << endl;
    return;
}