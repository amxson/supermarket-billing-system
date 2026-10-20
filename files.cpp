#include "files.h"
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <limits>
#include <unordered_set>
#include <vector>

namespace {
constexpr std::size_t maxProducts = 10000;
constexpr std::streamoff maxFileBytes = 2 * 1024 * 1024;
const char* fileName = "products.dat";
const char* temporaryName = "products.dat.tmp";
}

void saveProducts() {
    if (inventory.size() > maxProducts) {
        std::cerr << "Too many products to save.\n";
        return;
    }
    std::vector<int> ids;
    for (const auto& entry : inventory) ids.push_back(entry.first);
    std::sort(ids.begin(), ids.end());
    std::ofstream file(temporaryName, std::ios::trunc);
    if (!file) { std::cerr << "Error saving products.\n"; return; }
    file << "EASYMARKET_V1\n" << ids.size() << '\n';
    file << std::setprecision(std::numeric_limits<double>::max_digits10);
    for (int id : ids) {
        const auto& product = inventory.at(id);
        if (product.id <= 0 || product.categoryId <= 0 || product.name.empty() || product.name.size() > 256 ||
            !std::isfinite(product.price) || product.price < 0 || product.quantity < 0) {
            file.close(); std::remove(temporaryName);
            std::cerr << "Invalid product; existing file was preserved.\n";
            return;
        }
        file << product.id << ' ' << std::quoted(product.name) << ' ' << product.categoryId
             << ' ' << product.price << ' ' << product.quantity << '\n';
    }
    file.flush();
    bool written = static_cast<bool>(file);
    file.close();
    if (!written || file.fail() || std::rename(temporaryName, fileName) != 0) {
        std::remove(temporaryName);
        std::cerr << "Error saving products; existing file was preserved.\n";
    }
}

void loadProducts() {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);
    if (!file) return;
    const auto length = file.tellg();
    if (length < 0 || length > maxFileBytes) { std::cerr << "Invalid product file size.\n"; return; }
    file.seekg(0);
    std::string magic;
    std::getline(file, magic);
    std::size_t count;
    if (magic != "EASYMARKET_V1" || !(file >> count) || count > maxProducts) {
        std::cerr << "Unsupported or invalid product file; inventory unchanged.\n";
        return;
    }
    std::vector<Product> loaded;
    std::unordered_set<int> ids;
    for (std::size_t index = 0; index < count; ++index) {
        Product product{};
        if (!(file >> product.id >> std::quoted(product.name) >> product.categoryId >> product.price >> product.quantity) ||
            product.id <= 0 || product.categoryId <= 0 || product.name.empty() || product.name.size() > 256 ||
            !std::isfinite(product.price) || product.price < 0 || product.quantity < 0 || !ids.insert(product.id).second) {
            std::cerr << "Invalid product record; inventory unchanged.\n";
            return;
        }
        loaded.push_back(product);
    }
    file >> std::ws;
    if (!file.eof()) { std::cerr << "Unexpected product file content; inventory unchanged.\n"; return; }
    for (const auto& product : loaded) insertProductFromFile(product);
}
