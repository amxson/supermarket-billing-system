#include "cart.h"
#include "product.h"
#include <iostream>
#include <unordered_map>

using namespace std;

// ===== Cart storage =====
unordered_map<int, CartItem> cart;

// ===== Add to cart by asking for ID & quantity =====
void addToCart() {
    int productId, quantity;
    cout << "Enter product ID: ";
    cin >> productId;

    if (!productExists(productId)) {
        cout << "Invalid product ID.\n";
        return;
    }

    cout << "Enter quantity: ";
    cin >> quantity;

    if (quantity <= 0) {
        cout << "Quantity must be greater than zero.\n";
        return;
    }

    Product &p = inventory[productId];

    if (quantity > p.quantity) {
        cout << "Not enough stock! Available: " << p.quantity << endl;
        return; 
    }

    if (cart.find(productId) != cart.end()) {
        cart[productId].quantity += quantity;
    } else {
        cart[productId] = {productId, quantity};
    }

    p.quantity -= quantity;
    cout << "Product added to cart.\n";
}

// ===== Add directly by ID & quantity =====
void addToCartByID(int productId, int quantity) {
    if (!productExists(productId)) {
        cout << "Invalid product ID.\n";
        return;
    }

    if (quantity <= 0) {
        cout << "Quantity must be greater than zero.\n";
        return;
    }

    Product &p = inventory[productId];

    if (quantity > p.quantity) {
        cout << "Not enough stock! Available: " << p.quantity << endl;
        return; 
    }

    if (cart.find(productId) != cart.end()) {
        cart[productId].quantity += quantity;
    } else {
        cart[productId] = {productId, quantity};
    }

    p.quantity -= quantity;
    cout << "Product added to cart.\n"; 
}

// ===== Remove item from cart =====
void removeFromCart(int productId) {
    auto it = cart.find(productId);
    if (it != cart.end()) {
        inventory[productId].quantity += it->second.quantity;
        cart.erase(it);
        cout << "Product removed from cart.\n";
    } else {
        cout << "Product not found in cart.\n";
    }
}

// ===== View cart =====
void viewCart() {
    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return;
    }

    cout << "Cart Items:\n";
    for (auto &item : cart) {
        Product &p = inventory[item.second.productId];
        cout << "ID: " << p.id
             << " | Name: " << p.name
             << " | Price: " << p.price
             << " | Qty: " << item.second.quantity
             << " | Total: " << p.price * item.second.quantity
             << endl;
    }
}

// ===== Get number of items in cart =====
int getCartSize() {
    return cart.size();
}

// ===== Generate bill and return total =====
double generateBill() {
    if (cart.empty()) {
        cout << "Cart is empty.\n";
        return 0.0;
    }

    double total = 0.0;
    for (auto &item : cart) {
        Product &p = inventory[item.second.productId];
        total += p.price * item.second.quantity;
    }

    cout << "Bill generated. Total = " << total << endl;

    cart.clear();
    return total;
}
