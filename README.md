Supermarket Billing System (Console Version)

A console-based supermarket management and billing system in C++ that handles inventory, categories, cart operations, and billing.
This project demonstrates practical usage of DSA concepts like hash maps, linked lists, and BSTs, while providing an intuitive command-line interface.

Features
Inventory Management

Add, update, search, and delete products.

Products have ID, name, price, quantity, and can be assigned to categories.

Data stored in unordered_map for fast access.

Categories (BST)

Organize products using a Binary Search Tree.

View all categories and products under a specific category.

Assign products to categories for better organization.

Cart Management (Linked List)

Add products to the cart (choose by product ID).

Remove specific items from the cart.

View current cart items with quantities and prices.

Billing

Generate a total bill for the current cart.

Automatically updates inventory quantities.

Admin Operations

Admin can manage products and categories.

Admin functionality is integrated with regular actions (menu-based).

Data Structures Used
Feature	Data Structure
Inventory	unordered_map (Hash Map)
Categories	BST (Binary Search Tree)
Cart	Linked List
Undo Last Action	Not included (removed)
How to Run
Compile the code:
g++ main.cpp product.cpp cart.cpp category.cpp files.cpp -o supermarket

Run the executable:
./supermarket    # Linux/Mac
supermarket.exe  # Windows

Follow the menu:

Add products, create categories, assign products to categories

Add items to cart, view cart, remove items

Generate bill when done

File Structure
project/
├── main.cpp          # Main console interface
├── product.h/cpp     # Product operations (CRUD)
├── category.h/cpp    # Categories (BST)
├── cart.h/cpp        # Cart operations (Linked List)
├── files.h/cpp       # File operations (optional, currently inactive)
└── README.md         # Project description and instructions

Usage Example

Add products:

Enter Product ID: 101
Enter Product Name: Milk
Enter Price: 15
Enter Quantity: 20


Create categories:

Enter new category name: Beverages
Assign Product ID 101 to Beverages


Add to cart:

Enter Product ID to add to cart: 101
Enter Quantity: 2


Remove from cart:

Current Cart:
ID: 101 | Name: Milk | Qty: 2 | Price: 15

Enter Product ID to remove: 101


Generate bill:

Total Bill = 30
Cart cleared after billing.

Notes

Undo feature has been removed for simplicity.

File saving/loading is optional and currently inactive; inventory resets on each run.

Designed to be modular, so GUI can be added later without touching the logic.

Demonstrates practical use of DSA concepts in a real-world application.

Console interface ensures fast development and easy testing.
