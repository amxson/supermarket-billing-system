#ifndef CART_H
#define CART_H

using namespace std;

// ===== Linked List Node =====
struct CartItem {
    int productId;
    int quantity;
    CartItem* next;
};

// ===== Cart operations =====
void addToCart();                       
void addToCartByID(int productId, int quantity);
void removeFromCart(int productId);
void viewCart();
int getCartSize();
double generateBill();                  

#endif
