#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
using namespace std;

// ===== BST NODE =====
struct CategoryNode {
    int id;
    string name;
    vector<int> productIDs;
    CategoryNode* left;
    CategoryNode* right;
};

// ===== CORE BST OPS =====
void insertCategory(int id, const string& name);
CategoryNode* searchCategoryByID(int id);
void displayCategories();

// ===== PRODUCT ↔ CATEGORY LINKING =====
void addProductToCategory(int categoryId, int productId);
void removeProductFromCategory(int categoryId, int productId);
vector<int> getProductIDsInCategory(int categoryId);

// ===== USER HELPERS =====
int selectCategory();        
void addCategory();         
void viewCategories();      

#endif
