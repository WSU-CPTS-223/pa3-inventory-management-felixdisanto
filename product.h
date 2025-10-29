#pragma once



#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using std::string;
using std::vector;
using std::endl;
using std::cout;

class Product{
private:
    string uniq_id;
    string product_name;
    string brand_name;
    string asin;
    vector<string> categories;
    string selling_price;
    string list_price;  
public:

Product() = default;
 
Product(const string& id, const string& name, 
            const string& brand, const string& asin_code,
            const vector<string>& cats, 
            const string& s_price, const string& l_price) 
            : uniq_id(id), product_name(name), brand_name(brand), asin(asin_code), categories(cats), selling_price(s_price), list_price(l_price) {}

//getter

string getId() const {
    return uniq_id;
}

string getName() const {
    return product_name;
}

string getbrand() const {
    return brand_name;
}

string getAsin() const {
    return asin;
}

vector<string> getCategories() const {
    return categories;
}

string getSellingPrice() const {
    return selling_price;
}

string getListPrice() const {
    return list_price;
}


// display everything about the product

void display() const{
   
    cout << "Uniq ID: " << uniq_id << endl;
    cout << "Product Name: " << product_name << endl;
    cout << "Brand Name: " << brand_name << endl;
    cout << "ASIN: " << asin << endl;
    cout << "Categories: ";

    if (categories.empty())
    {
        cout << "NA";
    }
    else
    {
        for (size_t i = 0; i < categories.size(); ++i)
        {
            cout << categories[i];

            if (i < categories.size() - 1)
                cout << " | ";
        }
    }
    cout << endl;
    cout << "listing Price: " << list_price << endl;
    cout << "Selling Price: " << selling_price << endl;
}
};
