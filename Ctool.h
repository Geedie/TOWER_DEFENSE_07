#pragma once
#include "cpoint.h"
#include <mutex>
#include <windows.h>
#include <iostream>
using namespace std;

class Ctool {
public:
    static mutex mtx;  // Khai b�o mutex
    static void ShowConsoleCursor(bool);
    static void GotoXY(int x, int y);
    static void Draw(char*, int, Cpoint[], Cpoint&);
    static void setLocale();
};