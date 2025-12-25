#include "files.h"
#include <fstream>
#include <iostream>

using namespace std;

void saveProducts() {
    ofstream file("products.dat", ios::binary);
    if (!file) {
        cout << "Error saving products!\n";
        return;
    }

    Product arr[100];
    int count = getAllProducts(arr, 100);

    file.write((char*)&count, sizeof(count));
    file.write((char*)arr, sizeof(Product) * count);

    file.close();
}

void loadProducts() {
    ifstream file("products.dat", ios::binary);
    if (!file) return;

    int count;
    Product arr[100];

    file.read((char*)&count, sizeof(count));
    file.read((char*)arr, sizeof(Product) * count);

    for (int i = 0; i < count; i++) {
        insertProductFromFile(arr[i]);
    }

    file.close();
}
