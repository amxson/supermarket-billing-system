#ifndef UNDO_H
#define UNDO_H

#include <stack>
#include "cart.h"

enum ActionType { ADD, REMOVE };

struct Action {
    ActionType type;
    int productID;
    int quantity;
};

extern std::stack<Action> undoStack;

void pushAction(Action a);
void undoLastAction();

#endif
