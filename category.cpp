#include "category.h"
#include "product.h"
#include <iostream>
#include <unordered_map>
using namespace std;

extern unordered_map<int, Product> inventory;

CategoryNode* root = nullptr;

void insertCategory(const string& name) {
    CategoryNode** curr = &root;
    while (*curr) {
        if (name < (*curr)->name) curr = &(*curr)->left;
        else if (name > (*curr)->name) curr = &(*curr)->right;
        else return;
    }
    *curr = new CategoryNode{name, {}, nullptr, nullptr};
}

CategoryNode* searchCategory(const string& name) {
    CategoryNode* curr = root;
    while (curr) {
        if (name == curr->name) return curr;
        else if (name < curr->name) curr = curr->left;
        else curr = curr->right;
    }
    return nullptr;
}

void addProductToCategory(const string& categoryName, int productID) {
    CategoryNode* cat = searchCategory(categoryName);
    if (!cat) {
        insertCategory(categoryName);
        cat = searchCategory(categoryName);
    }
    cat->productIDs.push_back(productID);
}

void displayCategories() {
    vector<CategoryNode*> stack;
    CategoryNode* curr = root;
    while (curr || !stack.empty()) {
        while (curr) {
            stack.push_back(curr);
            curr = curr->left;
        }
        curr = stack.back(); stack.pop_back();
        cout << "- " << curr->name << endl;
        curr = curr->right;
    }
}

void displayProductsInCategory(const string& categoryName) {
    CategoryNode* cat = searchCategory(categoryName);
    if (!cat) {
        cout << "Category not found.\n";
        return;
    }
    cout << "--- Products in " << cat->name << " ---\n";
    for (int id : cat->productIDs) {
        if (inventory.count(id)) {
            Product &p = inventory[id];
            cout << "ID: " << p.id << " | " << p.name 
                 << " | Price: " << p.price 
                 << " | Qty: " << p.quantity << endl;
        }
    }
}
