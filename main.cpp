#include <iostream>
#include <string>
#include <sstream>
#include "Inventory_System.h"
using std::string;


using namespace std;

InventorySystem inventorySystem;

void printHelp()
{
    cout << "Supported list of commands: " << endl;
    cout << " 1. find <inventoryid> - Finds if the inventory exists. If exists, prints details. If not, prints 'Inventory not found'." << endl;
    cout << " 2. listInventory <category_string> - Lists just the id and name of all inventory belonging to the specified category. If the category doesn't exists, prints 'Invalid Category'.\n"
         << endl;
    cout << " Use quit to quit the REPL" << endl;
}

bool validCommand(string line)
{
    return (line == "help") ||
           (line.rfind("find", 0) == 0) ||
           (line.rfind("listInventory") == 0);
}

void evalCommand(string line)
{
    if (line == "help")
    {
        printHelp();
    }
    // if line starts with find
    else if (line.rfind("find", 0) == 0)
    {
        stringstream ss(line);
        string command;
        string inventoryId;
        ss >> command >> inventoryId;

    if(inventoryId.empty()){
    cout << "no id" << endl;
    return;
    }
    inventorySystem.findProduct(inventoryId);

    cout << "find command for id: " << inventoryId << "" << endl;
    }
    

    else if (line.rfind("listInventory") == 0)
    {
        stringstream ss(line);
        string command;
        string category;
        ss >> command >> category;

        if(category.empty()){
            cout << "no category" << endl;
            return;
         }
         inventorySystem.listInventory(category);
    }
}

void bootStrap()
{
    cout << "\n Welcome to Amazon Inventory Query System" << endl;
    cout << " enter quit to exit. or help to list supported commands." << endl;
    cout << "\n> ";

     string csv_file = "marketing_sample_for_amazon_com-ecommerce__20200101_20200131__10k_data-1.csv";
    cout << "Loading csv " << endl;
     inventorySystem.loadData(csv_file);
    cout << "Done" << endl;
}


int main(int argc, char const *argv[])
{
    string line;
    bootStrap();
    while (getline(cin, line) && line != "quit")
    {
        if (validCommand(line))
        {
            evalCommand(line);
        }
        else
        {
            cout << "Command not supported. Enter help for list of supported commands" << endl;
        }
        cout << "> ";
    }
    return 0;
}
