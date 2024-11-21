#include "Ctool.h"
mutex Ctool::mtx;  // Định nghĩa mutex

void Ctool::ShowConsoleCursor(bool showFlag) {
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void Ctool::GotoXY(int x, int y) {
    COORD crd = { x, y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
}

void Ctool::Draw(char* str, int i, Cpoint p[], Cpoint& _p) {
    mtx.lock();
    _p = p[i];
    Ctool::GotoXY(_p.getX(), _p.getY());
    cout << str;
    mtx.unlock();
}

void Ctool::setLocale() {
    locale::global(locale("en_US.UTD-8"));
    wcout.imbue(locale());
    SetConsoleOutputCP(CP_UTF8);
}
