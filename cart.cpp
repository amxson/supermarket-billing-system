#include "cart.h"
#include "product.h"
#include "undo.h"
#include <iostream>
#include <unordered_map>
using namespace std;

extern unordered_map<int, Product> inventory;
CartNode* head = nullptr;

void addToCart(int id, int qty) {
    if (!inventory.count(id)) { cout << "Product does not exist.\n"; return; }
    if (inventory[id].quantity < qty) { cout << "Not enough stock.\n"; return; }

    CartNode* newNode = new CartNode{id, qty, head};
    head = newNode;

    Action a{ADD, id, qty};
    pushAction(a);

    inventory[id].quantity -= qty;
    cout << "Added to cart.\n";
}

void viewCart() {
    if (!head) { cout << "Cart is empty.\n"; return; }
    CartNode* temp = head;
    cout << "\n--- Cart ---\n";
    while (temp) {
        cout << "ID: " << temp->productID << " | " 
             << inventory[temp->productID].name
             << " x " << temp->quantity << endl;
        temp = temp->next;
    }
}

float generateBill() {
    if (!head) { cout << "Cart is empty.\n"; return 0; }
    float total = 0;
    CartNode* temp = head;
    while (temp) {
        Product &p = inventory[temp->productID];
        total += p.price * temp->quantity;
        temp = temp->next;
    }
    clearCart();
    return total;
}

void removeFromCart(int id) {
    if (!head) { cout << "Cart is empty.\n"; return; }
    CartNode* temp = head;
    CartNode* prev = nullptr;
    while (temp) {
        if (temp->productID == id) {
            Action a{REMOVE, id, temp->quantity};
            pushAction(a);

            if (prev) prev->next = temp->next;
            else head = temp->next;

            inventory[id].quantity += temp->quantity;
            delete temp;
            cout << "Removed product ID " << id << " from cart.\n";
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Product not found in cart.\n";
}

void clearCart() {
    while (head) {
        CartNode* temp = head;
        inventory[temp->productID].quantity += temp->quantity;
        head = head->next;
        delete temp;
    }
}
