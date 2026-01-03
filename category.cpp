#include "category.h"
#include <iostream>
#include <limits>
using namespace std;

// ===== BST ROOT =====
CategoryNode* root = nullptr;

// ===== INSERT CATEGORY =====
void insertCategory(int id, const string& name) {
    CategoryNode** curr = &root;

    while (*curr) {
        if (id < (*curr)->id)
            curr = &((*curr)->left);
        else if (id > (*curr)->id)
            curr = &((*curr)->right);
        else
            return; 
    }

    *curr = new CategoryNode{id, name, {}, nullptr, nullptr};
}

// ===== SEARCH BY ID =====
CategoryNode* searchCategoryByID(int id) {
    CategoryNode* curr = root;

    while (curr) {
        if (id == curr->id) return curr;
        if (id < curr->id) curr = curr->left;
        else curr = curr->right;
    }
    return nullptr;
}

// ===== DISPLAY ALL CATEGORIES (INORDER, recursive) =====
void displayCategoriesHelper(CategoryNode* node) {
    if (!node) return;

    displayCategoriesHelper(node->left);
    cout << "ID: " << node->id << " | Name: " << node->name << endl;
    displayCategoriesHelper(node->right);
}

void displayCategories() {
    if (!root) {
        cout << "No categories available.\n";
        return;
    }
    cout << "\n--- Categories ---\n";
    displayCategoriesHelper(root);
}

// ===== ADD PRODUCT TO CATEGORY =====
void addProductToCategory(int categoryId, int productId) {
    CategoryNode* cat = searchCategoryByID(categoryId);
    if (!cat) return;

    for (int id : cat->productIDs)
        if (id == productId) return;

    cat->productIDs.push_back(productId);
}

// ===== REMOVE PRODUCT FROM CATEGORY =====
void removeProductFromCategory(int categoryId, int productId) {
    CategoryNode* cat = searchCategoryByID(categoryId);
    if (!cat) return;

    auto& v = cat->productIDs;
    for (auto it = v.begin(); it != v.end(); ++it) {
        if (*it == productId) {
            v.erase(it);
            return;
        }
    }
}

// ===== GET PRODUCT IDS =====
vector<int> getProductIDsInCategory(int categoryId) {
    CategoryNode* cat = searchCategoryByID(categoryId);
    if (!cat) return {};
    return cat->productIDs;
}

// ===== USER: ADD CATEGORY =====
void addCategory() {
    int id;
    string name;

    cout << "Enter Category ID: ";
    cin >> id;

    if (searchCategoryByID(id)) {
        cout << "Category already exists.\n";
        return;
    }

    cout << "Enter Category Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    insertCategory(id, name);
    cout << "Category added.\n";
}

// ===== USER: VIEW =====
void viewCategories() {
    displayCategories();
}

// ===== USER: SELECT CATEGORY =====
int selectCategory() {
    if (!root) {
        cout << "No categories available.\n";
        return -1;
    }

    displayCategories();

    int id;
    cout << "Enter Category ID: ";
    cin >> id;

    if (!searchCategoryByID(id)) {
        cout << "Invalid category.\n";
        return -1;
    }

    return id;
}
