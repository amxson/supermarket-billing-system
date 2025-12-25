#include <iostream>
#include <string>
#include "product.h"
#include "cart.h"
#include "category.h"
#include "undo.h"
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
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
}


void viewCategories() {
    cout << "\n=== Categories ===\n";
    displayCategories();
}


void viewProductsByCategory() {
    string cat;
    cout << "Enter category name: ";
    cin.ignore();
    getline(cin, cat);
    displayProductsInCategory(cat);
}


void assignProductToCategory() {
    string cat;
    int id;
    cout << "Enter category name: ";
    cin.ignore();
    getline(cin, cat);
    cout << "Enter Product ID to assign: ";
    cin >> id;
    addProductToCategory(cat, id);
}

int main() {
    loadProducts();

    int choice;
    do {
        clearScreen();
        cout << "=============================\n";
        cout << " SUPER MARKET BILLING SYSTEM \n";
        cout << "=============================\n";
        cout << "1. Add Product\n";
        cout << "2. View Products\n";
        cout << "3. Search Product\n";
        cout << "4. Update Product\n";
        cout << "5. Delete Product\n";
        cout << "6. Add Category\n";
        cout << "7. View Categories\n";
        cout << "8. Assign Product to Category\n";
        cout << "9. View Products by Category\n";
        cout << "10. Add to Cart\n";
        cout << "11. View Cart\n";
        cout << "12. Remove from Cart\n";
        cout << "13. Undo Last Cart Action\n";
        cout << "14. Generate Bill\n";
        cout << "0. Exit\n";
        cout << "Choose: ";
        cin >> choice;

        int id, qty;
        switch(choice) {
            case 1:
                addProduct();
                break;
            case 2:
                displayProducts();
                break;
            case 3:
                searchProduct();
                break;
            case 4:
                updateProduct();
                break;
            case 5:
                deleteProduct();
                break;
            case 6: {
                string cat;
                cout << "Enter new category name: ";
                cin.ignore();
                getline(cin, cat);
                insertCategory(cat);
                break;
            }
            case 7:
                viewCategories();
                break;
            case 8:
                assignProductToCategory();
                break;
            case 9:
                viewProductsByCategory();
                break;
            case 10:
                cout << "Enter Product ID: ";
                cin >> id;
                cout << "Enter Quantity: ";
                cin >> qty;
                addToCart(id, qty);
                break;
            case 11:
                viewCart();
                break;
            case 12:
                cout << "Enter Product ID to remove: ";
                cin >> id;
                removeFromCart(id);
                break;
            case 13:
                undoLastAction();
                break;
            case 14:
                cout << "Total Bill = " << generateBill() << "\n";
                break;
            case 0:
                saveProducts();
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice!\n";
        }

        pauseScreen();

    } while(choice != 0);

    return 0;
}
