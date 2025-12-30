Supermarket Billing System (Console Version)

A console-based supermarket management and billing system in C++ that handles inventory, categories, cart operations, undo functionality, and billing. This project demonstrates practical usage of DSA concepts like hash maps, linked lists, stacks, and BSTs, all while providing an intuitive command-line interface.

Features
Inventory Management

Add, update, search, and delete products.

Products have ID, name, price, quantity, and can be assigned to categories.

Data stored in unordered_map for fast access.

Categories (BST)

Organize products by categories using a Binary Search Tree.

View all categories and products under a specific category.

Assign products to categories for better organization.

Cart Management (Linked List)

Add products to the cart (choose by product name or ID).

Remove specific items from the cart.

View current cart items with quantities and prices.

Undo Feature (Stack)

Undo the last cart action (add or remove product) using a stack.

Billing

Generate a total bill for the current cart.

Automatically updates inventory quantities.

Admin Operations

Admin can manage products and categories.

Admin functionality is separate from regular user actions.

File Handling

Save and load product data from file.

Inventory persists between program runs.

Data Structures Used
Feature	Data Structure
Inventory	unordered_map (Hash Map)
Categories	BST (Binary Search Tree)
Cart	Linked List
Undo Last Action	Stack
How to Run

Compile the code:

g++ main.cpp product.cpp cart.cpp category.cpp undo.cpp files.cpp -o supermarket


Run the executable:

./supermarket    # Linux/Mac
supermarket.exe  # Windows


Follow the menu:

Use numbers to select actions

Add products, create categories, assign products to categories

Add items to cart, view cart, remove items, undo last action

Generate bill when done

File Structure
project/
├── main.cpp          # Main console interface
├── product.h/cpp     # Product operations (CRUD)
├── category.h/cpp    # Categories (BST)
├── cart.h/cpp        # Cart operations (Linked List)
├── undo.h/cpp        # Undo stack operations
├── files.h/cpp       # File save/load
└── README.md         # This file

Usage Example

Add products:

Enter Product ID: 101
Enter Product Name: Milk
Enter Price: 15
Enter Quantity: 20


Create categories:

Enter new category name: Beverages
Assign Product ID 101 to Beverages


Add to cart and undo:

Enter Product ID to add to cart: 101
Enter Quantity: 2
Undo last cart action → product removed


Generate bill:

Total Bill = 30

Notes

Console interface ensures fast development and easy testing.

Designed to be modular, so GUI can be added later without touching the logic.

Demonstrates practical use of DSA in real-world applications.
