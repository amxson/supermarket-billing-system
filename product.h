#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
using namespace std;

struct Product {
    int id;
    char name[30];
    float price;
    int quantity;
};


void addProduct();
void displayProducts();
void searchProduct();
void updateProduct();
void deleteProduct();


int getAllProducts(Product arr[], int maxSize);
void insertProductFromFile(const Product& p);

#endif
