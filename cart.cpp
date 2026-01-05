#include "cart.h"
#include "product.h"
#include <iostream>
#include <stack>
#include <string>
using namespace std;

// ===== Linked List Head =====
CartItem* head = nullptr;

// ===== Stack for transaction history =====
stack<TransactionItem> transactionHistory;

// ===== Add to cart (interactive) =====
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

    Product& p = inventory[productId];

    if (quantity > p.quantity) {
        cout << "Not enough stock! Available: " << p.quantity << endl;
        return;
    }

    // check if product already exists in cart
    CartItem* curr = head;
    while (curr) {
        if (curr->productId == productId) {
            curr->quantity += quantity;
            p.quantity -= quantity;
            cout << "Product quantity updated in cart.\n";
            return;
        }
        curr = curr->next;
    }

    // insert new node at head
    CartItem* newNode = new CartItem{productId, quantity, head};
    head = newNode;
    p.quantity -= quantity;

    cout << "Product added to cart.\n";
}

// ===== Add to cart by ID & quantity =====
void addToCartByID(int productId, int quantity) {
    if (!productExists(productId)) {
        cout << "Invalid product ID.\n";
        return;
    }

    if (quantity <= 0) {
        cout << "Quantity must be greater than zero.\n";
        return;
    }

    Product& p = inventory[productId];

    if (quantity > p.quantity) {
        cout << "Not enough stock! Available: " << p.quantity << endl;
        return;
    }

    CartItem* curr = head;
    while (curr) {
        if (curr->productId == productId) {
            curr->quantity += quantity;
            p.quantity -= quantity;
            cout << "Product quantity updated in cart.\n";
            return;
        }
        curr = curr->next;
    }

    CartItem* newNode = new CartItem{productId, quantity, head};
    head = newNode;
    p.quantity -= quantity;

    cout << "Product added to cart.\n";
}

// ===== Remove from cart =====
void removeFromCart(int productId) {
    CartItem* curr = head;
    CartItem* prev = nullptr;

    while (curr) {
        if (curr->productId == productId) {
            inventory[productId].quantity += curr->quantity;

            if (prev)
                prev->next = curr->next;
            else
                head = curr->next;

            delete curr;
            cout << "Product removed from cart.\n";
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    cout << "Product not found in cart.\n";
}

// ===== View cart =====
void viewCart() {
    if (!head) {
        cout << "Cart is empty.\n";
        return;
    }

    cout << "Cart Items:\n";
    CartItem* curr = head;

    while (curr) {
        Product& p = inventory[curr->productId];
        cout << "ID: " << p.id
             << " | Name: " << p.name
             << " | Price: " << p.price
             << " | Qty: " << curr->quantity
             << " | Total: " << p.price * curr->quantity
             << endl;

        curr = curr->next;
    }
}

// ===== Cart size =====
int getCartSize() {
    int count = 0;
    CartItem* curr = head;
    while (curr) {
        count++;
        curr = curr->next;
    }
    return count;
}

// ===== Generate bill (with promocode) =====
double generateBill() {
    if (!head) {
        cout << "Cart is empty.\n";
        return 0.0;
    }

    double total = 0.0;
    CartItem* curr = head;

    // temporary stack to reverse order for correct transaction history
    stack<TransactionItem> tempStack;

    while (curr) {
        Product& p = inventory[curr->productId];
        total += p.price * curr->quantity;

        tempStack.push({curr->productId, curr->quantity, false});
        curr = curr->next;
    }

    // push reversed transactions to main transaction stack
    while (!tempStack.empty()) {
        transactionHistory.push(tempStack.top());
        tempStack.pop();
    }

    // ===== PROMOCODE CHECK =====
    cout << "Do you have a promocode? (y/n): ";
    char ans;
    cin >> ans;
    double discount = 0.0;

    if (ans == 'y' || ans == 'Y') {
        cout << "Enter promocode: ";
        string code;
        cin >> code;

        if (code == "super1") {
            discount = 0.10;
            cout << "Promocode applied! 10% discount.\n";
        } else {
            cout << "Invalid promocode.\n";
        }
    }

    double discountedTotal = total - (total * discount);

    // push end marker for this transaction
    transactionHistory.push({0, 0, true});

    // clear cart
    while (head) {
        CartItem* temp = head;
        head = head->next;
        delete temp;
    }

    cout << "Bill generated. Total = " << discountedTotal << endl;
    return discountedTotal;
}

// ===== View transaction history =====
void viewTransactionHistory() {
    if (transactionHistory.empty()) {
        cout << "No transactions yet.\n";
        return;
    }

    stack<TransactionItem> tempStack = transactionHistory;
    cout << "\n--- Transaction History ---\n";

    while (!tempStack.empty()) {
        TransactionItem item = tempStack.top();
        tempStack.pop();

        if (item.isEnd) {
            cout << "=== End of Transaction ===\n";
        } else {
            Product& p = inventory[item.productId];
            cout << "ID: " << p.id
                 << " | Name: " << p.name
                 << " | Qty: " << item.quantity
                 << " | Total: " << p.price * item.quantity
                 << endl;
        }
    }
}
