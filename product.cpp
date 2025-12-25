#include "product.h"
#include <iostream>
#include <unordered_map>

using namespace std;

// hash table inventory
unordered_map<int, Product> inventory;

void addProduct() {
    Product p;
    cout << "Enter Product ID: ";
    cin >> p.id;

    if (inventory.count(p.id)) {
        cout << "Product already exists!\n";
        return;
    }

    cout << "Enter Product Name: ";
    cin >> p.name;
    cout << "Enter Price: ";
    cin >> p.price;
    cout << "Enter Quantity: ";
    cin >> p.quantity;

    inventory[p.id] = p;
    cout << "Product added successfully.\n";
}

void displayProducts() {
    if (inventory.empty()) {
        cout << "No products available.\n";
        return;
    }

    cout << "\n--- Product List ---\n";
    for (auto &item : inventory) {
        Product p = item.second;
        cout << "ID: " << p.id
             << " | Name: " << p.name
             << " | Price: " << p.price
             << " | Qty: " << p.quantity << endl;
    }
}

void searchProduct() {
    int id;
    cout << "Enter Product ID to search: ";
    cin >> id;

    if (inventory.count(id)) {
        Product p = inventory[id];
        cout << "Found: " << p.name
             << " | Price: " << p.price
             << " | Qty: " << p.quantity << endl;
    } else {
        cout << "Product not found.\n";
    }
}

void updateProduct() {
    int id;
    cout << "Enter Product ID to update: ";
    cin >> id;

    if (!inventory.count(id)) {
        cout << "Product not found.\n";
        return;
    }

    cout << "Enter new price: ";
    cin >> inventory[id].price;
    cout << "Enter new quantity: ";
    cin >> inventory[id].quantity;

    cout << "Product updated successfully.\n";
}

void deleteProduct() {
    int id;
    cout << "Enter Product ID to delete: ";
    cin >> id;

    if (inventory.erase(id)) {
        cout << "Product deleted.\n";
    } else {
        cout << "Product not found.\n";
    }
}

// ===== file handling helpers =====
int getAllProducts(Product arr[], int maxSize) {
    int count = 0;
    for (auto &item : inventory) {
        if (count >= maxSize) break;
        arr[count++] = item.second;
    }
    return count;
}

void insertProductFromFile(const Product& p) {
    inventory[p.id] = p;
}
