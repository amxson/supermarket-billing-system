#ifndef CATEGORY_H
#define CATEGORY_H

#include <string>
#include <vector>
using namespace std;

struct CategoryNode {
    string name;
    vector<int> productIDs;
    CategoryNode* left;
    CategoryNode* right;
};

extern CategoryNode* root;

void insertCategory(const string& name);
CategoryNode* searchCategory(const string& name);
void addProductToCategory(const string& categoryName, int productID);
void displayCategories();
void displayProductsInCategory(const string& categoryName);

#endif
