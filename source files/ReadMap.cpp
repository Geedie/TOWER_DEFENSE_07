#include "../header files/ReadMap.h"

void Map::ResizeConsole(int row, int col) {
    // Lấy handle của console
    HWND console = GetConsoleWindow();
    RECT r;
    GetWindowRect(console, &r); // Lấy kích thước hiện tại của console

    // Điều chỉnh kích thước console
    MoveWindow(console, r.left, r.top, row, col, TRUE);
}

void Map::Inputmap() {
    ifstream file("resource files/map1.txt");  // Mở file map.txt

    // Kiểm tra nếu file mở thành công
    if (!file.is_open()) {
        cerr << "Không thể mở file map.txt" << endl;
        return;
    }

    string line;
    // Đọc từng dòng và in ra console
    while (getline(file, line)) {
        cout << line << endl;
    }

    file.close();  // Đóng file sau khi đọc xong
}