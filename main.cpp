#include <iostream>
#include <string>
#include <limits>
#include "product.h"
#include "cart.h"
#include "category.h"
#include "files.h"

using namespace std;

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pauseScreen() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

// ===== VIEW PRODUCTS BY CATEGORY =====
void viewProductsByCategory() {
    int categoryId = selectCategory();
    if (categoryId == -1) return;

    vector<int> productIDs = getProductIDsInCategory(categoryId);
    if (productIDs.empty()) {
        cout << "No products in this category.\n";
        return;
    }

    cout << "\n--- Products in Category ---\n";
    for (int pid : productIDs) {
        displaySingleProduct(pid);
    }
}

// ===== ADD PRODUCT TO CART =====
void addProductToCart() {
    int categoryId = selectCategory();
    if (categoryId == -1) return;

    vector<int> productIDs = getProductIDsInCategory(categoryId);
    if (productIDs.empty()) {
        cout << "No products in this category.\n";
        return;
    }

    cout << "\n--- Products in Category ---\n";
    for (int pid : productIDs) {
        displaySingleProduct(pid);
    }

    int productId, qty;

    cout << "Enter Product ID to add to cart: ";
    cin >> productId;
    if (cin.fail()) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input.\n";
        return;
    }

    if (!productExists(productId)) {
        cout << "Invalid Product ID.\n";
        return;
    }

    cout << "Enter quantity: ";
    cin >> qty;
    if (cin.fail() || qty <= 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid quantity.\n";
        return;
    }

    addToCartByID(productId, qty);
}

int main() {
    loadProducts();

    int choice;
    do {
        clearScreen();
        cout << "=============================\n";
        cout << " SUPER MARKET BILLING SYSTEM \n";
        cout << "=============================\n";
        cout << "1. Add Category\n";
        cout << "2. View Categories\n";
        cout << "3. Add Product\n";
        cout << "4. View All Products\n";
        cout << "5. Search Product\n";
        cout << "6. Update Product\n";
        cout << "7. Delete Product\n";
        cout << "8. View Products by Category\n";
        cout << "9. Change Product Category\n";
        cout << "10. Add to Cart\n";
        cout << "11. View Cart\n";
        cout << "12. Remove from Cart\n";
        cout << "13. Generate Bill\n";
        cout << "0. Exit\n";
        cout << "Choose: ";

        cin >> choice;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            choice = -1;
        }

        int productId, categoryId;

        switch (choice) {
            case 1:
                addCategory();
                break;

            case 2:
                viewCategories();
                break;

            case 3:
                addProduct();
                break;

            case 4:
                displayProducts();
                break;

            case 5:
                searchProduct();
                break;

            case 6:
                updateProduct();
                break;

            case 7:
                deleteProduct();
                break;

            case 8:
                viewProductsByCategory();
                break;

            case 9:
                cout << "Enter Product ID to reassign: ";
                cin >> productId;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input.\n";
                    break;
                }
                categoryId = selectCategory();
                if (categoryId != -1) {
                    addProductToCategory(categoryId, productId);
                    cout << "Product category updated.\n";
                }
                break;

            case 10:
                addProductToCart();
                break;

            case 11:
                viewCart();
                break;

            case 12:
                // show cart first (user-friendly)
                viewCart();

                cout << "\nEnter Product ID to remove: ";
                cin >> productId;
                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Invalid input.\n";
                    break;
                }
                removeFromCart(productId);
                break;

            case 13: {
                double total = generateBill();
                cout << "Total Bill = " << total << endl;
                if (total > 0)
                    cout << "Cart has been cleared after billing.\n";
                break;
            }

            case 0:
                saveProducts();
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid choice!\n";
        }

        if (choice != 0)
            pauseScreen();

    } while (choice != 0);

    return 0;
}
