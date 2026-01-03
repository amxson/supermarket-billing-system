#ifndef CART_H
#define CART_H

#include <unordered_map>
#include <vector>
#include <iostream>
using namespace std;

struct CartItem {
    int productId;
    int quantity;
};

// Cart storage
extern unordered_map<int, CartItem> cart;

// Functions
void addToCart();
void addToCartByID(int productId, int quantity);
void removeFromCart(int productId);
void viewCart();
int getCartSize();
double generateBill(); // return total bill

#endif
