#include "product.h"
#include "category.h"
#include <iostream>
#include <limits>
#include <cctype>   // for isalpha
using namespace std;

// ===== INVENTORY =====
unordered_map<int, Product> inventory;

// ===== HELPER TO GET VALID INT =====
int getValidInt(const string& prompt, int minValue = numeric_limits<int>::min()) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minValue) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number";
            if (minValue != numeric_limits<int>::min()) cout << " >= " << minValue;
            cout << ".\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // clear leftover input
            return value;
        }
    }
}

// ===== HELPER TO GET VALID DOUBLE =====
double getValidDouble(const string& prompt, double minValue = 0.0) {
    double value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < minValue) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number >= " << minValue << ".\n";
        } else {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
    }
}

// ===== HELPER TO GET VALID STRING =====
string getValidString(const string& prompt) {
    string s;
    while (true) {
        cout << prompt;
        getline(cin, s);
        bool valid = true;
        for (char c : s) {
            if (!isalpha(c) && c != ' ') { // allow spaces
                valid = false;
                break;
            }
        }
        if (!valid || s.empty()) {
            cout << "Invalid name. Only alphabetic characters and spaces allowed.\n";
        } else {
            return s;
        }
    }
}

// ===== CHECK =====
bool productExists(int id) {
    return inventory.count(id);
}

// ===== ADD PRODUCT =====
void addProduct() {
    Product p;

    p.id = getValidInt("Enter Product ID: ", 1);

    if (inventory.count(p.id)) {
        cout << "Product already exists.\n";
        return;
    }

    p.name = getValidString("Enter Product Name: ");

    int catId = selectCategory();
    if (catId == -1) return;
    p.categoryId = catId;

    p.price = getValidDouble("Enter Price: ", 0.0);
    p.quantity = getValidInt("Enter Quantity: ", 0);

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

// ===== DISPLAY SINGLE =====
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
    int id = getValidInt("Enter Product ID: ", 1);

    if (!inventory.count(id)) {
        cout << "Product not found.\n";
        return;
    }

    displaySingleProduct(id);
}

// ===== UPDATE =====
void updateProduct() {
    int id = getValidInt("Enter Product ID: ", 1);

    if (!inventory.count(id)) {
        cout << "Product not found.\n";
        return;
    }

    Product& p = inventory[id];
    p.price = getValidDouble("New price: ", 0.0);
    p.quantity = getValidInt("New quantity: ", 0);

    cout << "Product updated.\n";
}

// ===== DELETE =====
void deleteProduct() {
    int id = getValidInt("Enter Product ID: ", 1);

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
