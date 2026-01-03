#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <unordered_map>
using namespace std;

struct Product {
    int id;
    string name;
    int categoryId;
    double price;
    int quantity;
};

// inventory (defined in product.cpp)
extern unordered_map<int, Product> inventory;

// core ops
bool productExists(int id);
void addProduct();
void displayProducts();
void displaySingleProduct(int id);
void searchProduct();
void updateProduct();
void deleteProduct();

// file helpers
int getAllProducts(Product arr[], int maxSize);
void insertProductFromFile(const Product& p);

#endif
