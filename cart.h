#ifndef CART_H
#define CART_H

#include <stack>
#include <iostream>
using namespace std;

// ===== Linked List Node for Cart =====
struct CartItem {
    int productId;
    int quantity;
    CartItem* next;
};

// ===== Transaction Item (for stack) =====
struct TransactionItem {
    int productId;
    int quantity;
    bool isEnd;  // marks end of one transaction
};

// ===== Linked List Head =====
extern CartItem* head;

// ===== Stack for transaction history =====
extern stack<TransactionItem> transactionHistory;

// ===== Cart operations =====
void addToCart();
void addToCartByID(int productId, int quantity);
void removeFromCart(int productId);
void viewCart();
int getCartSize();
double generateBill();                  

// ===== Transaction history =====
void viewTransactionHistory();

#endif
