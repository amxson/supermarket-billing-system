#ifndef CART_H
#define CART_H

struct CartNode {
    int productID;
    int quantity;
    CartNode* next;
};

void addToCart(int id, int qty);
void viewCart();
float generateBill();
void removeFromCart(int id);
void clearCart();

#endif
