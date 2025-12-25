#include "undo.h"
#include "cart.h"
#include "product.h"
#include <unordered_map>
#include <iostream>
using namespace std;

extern unordered_map<int, Product> inventory;
extern CartNode* head;
stack<Action> undoStack;

void pushAction(Action a) { undoStack.push(a); }

void undoLastAction() {
    if (undoStack.empty()) {
        cout << "Nothing to undo.\n";
        return;
    }

    Action a = undoStack.top();
    undoStack.pop();

    if (a.type == ADD) {
        removeFromCart(a.productID);
        cout << "Undo: added product removed from cart.\n";
    } else if (a.type == REMOVE) {
        addToCart(a.productID, a.quantity);
        cout << "Undo: removed product restored to cart.\n";
    }
}
