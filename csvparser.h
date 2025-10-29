#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "product.h"
using std::string;
using std::vector;
using std::ifstream;
using std::stringstream;


class CSVParser{
private:

static vector<string> parseline(const string& line){
 vector<string> fields;
 string field;
 bool inQuotes = false;

 for (size_t i = 0; i < line.length(); ++i)
 {
     char currentChar = line[i];

     if (currentChar == '"')
     {
         inQuotes = !inQuotes;
     }
     else if (currentChar == ',' && !inQuotes)
     {
         fields.push_back(field);
         field.clear();
     }
     else
     {
         field += currentChar;
     }
     
 }

 fields.push_back(field);
 return fields;
}

//take care of muktiple categories for an item
static vector<string> splitCategories(const string& categoryField){
    vector<string> categories;
    
    if(categoryField.empty()){
        categories.push_back("NA");
        return categories;
    }

    stringstream ss(categoryField);
    string category;

    while(getline(ss, category, '|')){
        categories.push_back(category);
    }

    if(categories.empty()){
        categories.push_back("NA");
    }
    return categories;


}

public:

static vector<Product> parseCSV(const string& filename){
    vector<Product> products;
    ifstream file(filename);

    if(!file.is_open()){
        cout << "Error opening file: " << filename << endl;
        return products;
    }
    string line;
    getline(file, line);
   // cout << "Header: " << line << endl; /////

   int line_num = 1;

   while(getline(file, line)){
    line_num++;

    if(line.empty()){
        continue;
    }

    vector<string> fields = parseline(line);

    //cout << "Line " << line_num << " has " << fields.size() << " fields" << endl; ///////

    if(fields.size()< 28){
       // cout << "Not enough fields" << endl;
      // cout << "Skipping line " << line_num << " (not enough fields)" << endl;/////
        continue;
    }
    //cout << "ID: " << fields[0] << " | Name: " << fields[1] << endl;  ///////
    string uniq_id = fields[0];
    string product_name = fields[1];
    string brand_name = fields[2];
    string asin = fields[3];
    string categoryField = fields[4];
    string listing_price = fields.size() > 6 ? fields[6] : "";
    string selling_price = fields.size() > 7 ? fields[7] : "";
 
    vector<string> categories = splitCategories(categoryField);

    Product product(uniq_id, product_name, brand_name, asin, categories, selling_price, listing_price);
    products.push_back(product);
}
    file.close();
    cout << "loaded csv" << endl;
    return products;




}
};