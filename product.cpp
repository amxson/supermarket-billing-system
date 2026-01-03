#include "product.h"
#include "category.h"
#include <iostream>
using namespace std;

// ===== INVENTORY =====
unordered_map<int, Product> inventory;

// ===== CHECK =====
bool productExists(int id) {
    return inventory.count(id);
}

// ===== ADD PRODUCT =====
void addProduct() {
    Product p;

    cout << "Enter Product ID: ";
    cin >> p.id;

    if (inventory.count(p.id)) {
        cout << "Product already exists.\n";
        return;
    }

    cout << "Enter Product Name: ";
    cin.ignore();
    getline(cin, p.name);

    int catId = selectCategory();
    if (catId == -1) return;
    p.categoryId = catId;

    cout << "Enter Price: ";
    cin >> p.price;

    cout << "Enter Quantity: ";
    cin >> p.quantity;

    inventory[p.id] = p;
    addProductToCategory(p.categoryId, p.id);

    cout << "Product added successfully.\n";
}

// ===== DISPLAY ALL =====
void displayProducts() {
    if (inventory.empty()) {
        cout << "No products available.\n";
        return;
    }

    cout << "\n--- Products ---\n";
    for (auto& it : inventory) {
        Product& p = it.second;
        cout << "ID: " << p.id
             << " | Name: " << p.name
             << " | Category ID: " << p.categoryId
             << " | Price: " << p.price
             << " | Qty: " << p.quantity << endl;
    }
}

// ===== DISPLAY ONE =====
void displaySingleProduct(int id) {
    if (!inventory.count(id)) return;

    Product& p = inventory[id];
    cout << "ID: " << p.id
         << " | Name: " << p.name
         << " | Price: " << p.price
         << " | Qty: " << p.quantity << endl;
}

// ===== SEARCH =====
void searchProduct() {
    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    if (!inventory.count(id)) {
        cout << "Product not found.\n";
        return;
    }

    displaySingleProduct(id);
}

// ===== UPDATE =====
void updateProduct() {
    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    if (!inventory.count(id)) {
        cout << "Product not found.\n";
        return;
    }

    Product& p = inventory[id];
    cout << "New price: ";
    cin >> p.price;
    cout << "New quantity: ";
    cin >> p.quantity;

    cout << "Product updated.\n";
}

// ===== DELETE =====
void deleteProduct() {
    int id;
    cout << "Enter Product ID: ";
    cin >> id;

    if (!inventory.count(id)) {
        cout << "Product not found.\n";
        return;
    }

    int catId = inventory[id].categoryId;
    removeProductFromCategory(catId, id);
    inventory.erase(id);

    cout << "Product deleted.\n";
}

// ===== FILE HELPERS =====
int getAllProducts(Product arr[], int maxSize) {
    int count = 0;
    for (auto& it : inventory) {
        if (count >= maxSize) break;
        arr[count++] = it.second;
    }
    return count;
}

void insertProductFromFile(const Product& p) {
    inventory[p.id] = p;
    addProductToCategory(p.categoryId, p.id);
}
