#include "../header files/Map.h"

void Map::DisplayMap(int n) {
    wifstream file;

    // Mở file tương ứng với giá trị của n
    if (n == 1) { file.open(L"resource files/map1.txt"); }
    else if (n == 2) { file.open(L"resource files/map2.txt"); }
    else if (n == 3) { file.open(L"resource files/map3.txt"); }
    else if (n == 4) { file.open(L"resource files/map4.txt"); }
    if (!file.is_open()) {
        cerr << "Không thể mở file map.txt" << endl;
        return;
    }

    wstring line;
    // Đọc từng dòng và in ra console
    while (getline(file, line)) {
        wcout << line << endl;
    }

    file.close();  // Đóng file sau khi đọc xong
}