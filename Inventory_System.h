#pragma once

#include "product.h"
#include "Hashtable.h"
#include "csvparser.h"
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using std::string;
using std::vector;
using std::cout;
using std::endl;

class InventorySystem{
private:
    Hashtable<string, Product> inventory;

    public:
    InventorySystem() : inventory(10000){}

    void loadData(const string& filename){
        cout << "loading inventory" << endl;
        vector<Product> products = CSVParser::parseCSV(filename);
        for(const auto& product : products){
            inventory.insert(product.getId(), product);
        }
        cout << "loaded inventory with " << inventory.size() << " products" << endl;
    }

    bool findProduct(const string& inventory_id)
    {
        Product product;
        if(inventory.find(inventory_id, product)){
            product.display();
            return true;
        } else {
            cout << "not found" << endl;
            return false;
        }
    }

 bool listInventory(const string& category)
    {
        vector<Product> matching_products;
        vector<Product> all_products = inventory.getAllValues();

         string search = category;//gpt
         std::transform(search.begin(), search.end(), search.begin(), ::tolower);//gpt

        for (const auto& product : all_products)
        {
            vector<string> categories = product.getCategories();
            
            for(const auto& cat : categories)
            {
                string lower_cat = cat;//gpt
                std::transform(lower_cat.begin(), lower_cat.end(), lower_cat.begin(), ::tolower);//gpt
                if (lower_cat.find(search)!= string::npos)// gpt
                {
                    matching_products.push_back(product);
                    break;
                }
            }
        }

        if(matching_products.empty()){
            cout << "No category" << endl;
            return false;
        }
        cout << "Products in category" << category <<  endl;

        for(const auto& product : matching_products){

            cout << "ID:" << product.getId() << "  Name: " << product.getName() << endl;
        }

        cout << "Total products found" << matching_products.size() << endl;
        return true;
    }
};