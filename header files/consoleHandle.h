#ifndef CONSOLE_HANDLE_H
#define CONSOLE_HANDLE_H

#include <windows.h>
#include <locale>
#include <iostream>

using namespace std;

int getConsoleWidth();

int getConsoleHeight();

void setConsoleBackgroundColor(int backgroundColor);

void resizeConsole(int width, int height);

void setLocale();

void clearConsole();

#endif
