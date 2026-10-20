#include "product.h"
#include "files.h"
#include <cassert>
#include <cstdio>
#include <fstream>

int main() {
    inventory[1] = Product{1, "Milk with spaces", 1, 12.25, 3};
    for (int id = 2; id <= 150; ++id) inventory[id] = Product{id, "Product", 1, 1.0, 2};
    saveProducts();
    inventory.clear();
    loadProducts();
    assert(inventory.size() == 150);
    assert(inventory.at(1).name == "Milk with spaces");
    assert(inventory.at(1).price == 12.25);
    const auto original = inventory;
    for (const auto* bad : {"EASYMARKET_V1\n1000000000\n", "EASYMARKET_V1\n2\n1 \"new\" 1 2 3\n", "EASYMARKET_V1\n1\n1 \"invalid\" 1 -1 3\n", "old binary format", "EASYMARKET_V1\n2\n1 \"one\" 1 2 3\n1 \"two\" 1 2 3\n"}) {
        { std::ofstream file("products.dat", std::ios::trunc); file << bad; }
        loadProducts();
        assert(inventory.size() == original.size());
        assert(inventory.at(1).name == original.at(1).name);
    }
    std::remove("products.dat");
}
