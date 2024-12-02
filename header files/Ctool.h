#pragma once

#ifndef _CTOOL_H_
#define _CTOOL_H_

#include "cpoint.h"
#include <mutex>
#include <windows.h>
#include <iostream>

using namespace std;

enum ConsoleColor {
    Black = 0,
    DarkBlue = 1,
    DarkGreen = 2,
    DarkCyan = 3,
    DarkRed = 4,
    DarkMagenta = 5,
    DarkYellow = 6,
    LightGray = 7,
    DarkGray = 8,
    Blue = 9,
    Green = 10,
    Cyan = 11,
    Red = 12,
    Magenta = 13,
    Yellow = 14,
    White = 15
};

class ctool {
public:
    static mutex mtx;
    static void ShowConsoleCursor(bool);
    static void GotoXY(int x, int y);
    static void Draw(char*, int, cpoint[], cpoint&);
    static void setLocale();
    static void resizeConsole(int, int);
    static void setColor(ConsoleColor, ConsoleColor);
    static void setConsoleBackgroundColor(ConsoleColor);
};

#endif