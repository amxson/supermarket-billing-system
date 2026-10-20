# Supermarket Billing System

A C++ console project using a hash map for inventory, a binary search tree for categories, a linked list for the cart, and a stack for transaction history. It supports product management, stock reservation in the cart, billing, and a sample promotion code.

## Build and run

Use a C++17 compiler:

```sh
g++ -std=c++17 -Wall -Wextra main.cpp product.cpp cart.cpp category.cpp files.cpp -o supermarket
./supermarket
```

Or use CMake, including the persistence regression test:

```sh
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

Create a category before adding products. Adding an item to the cart reserves stock; removing it returns that stock. Billing clears the cart and records the transaction in memory.

## Persistence

The menu currently keeps inventory and categories in memory. The separate `saveProducts()` and `loadProducts()` helpers are available for explicit integration; they are not called automatically.

The helpers use a versioned text format in `products.dat`, storing each field explicitly. C++ `std::string` objects must never be written as raw bytes: those bytes contain process-local pointers, not portable string data. Loading validates the complete file before applying records and rejects malformed counts, duplicate IDs, negative values, oversized files, and the old raw-memory format. Saving writes a temporary file before replacement. The regression test covers round trips with more than 100 products and malformed-file rejection.

The existing legacy `products.dat` is not migrated or deleted. It is rejected by the new loader; recreate sample inventory through the application. Category definitions and transaction history are not persisted.

This is a data-structures exercise, not a production point-of-sale system. Authentication, taxes, durable sales records, and payment processing are outside its scope.
