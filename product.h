#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

struct Product {
    int id;
    string name;
    float price;
    int quantity;
};

// Product management functions
void addProduct();
void updateProduct();
void deleteProduct();
void searchProduct();
void displayProducts();

#endif
