#include "consoleHandle.h"

// Retrieves the width of the console window.
int getConsoleWidth() {
    CONSOLE_SCREEN_BUFFER_INFO csbi; // Structure to hold console screen buffer info
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); // Get current console info
    return csbi.srWindow.Right - csbi.srWindow.Left + 1; // Calculate width
}

// Retrieves the height of the console window.
int getConsoleHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi; // Structure to hold console screen buffer info
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi); // Get current console info
    return csbi.srWindow.Bottom - csbi.srWindow.Top + 1; // Calculate height
}

void setConsoleBackgroundColor(int backgroundColor) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    // Lay thong tin ve buffer
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    // Kich thuoc buffer
    DWORD written;
    COORD coord = { 0, 0 };
    DWORD size = csbi.dwSize.X * csbi.dwSize.Y;
    // Thay doi mau nen
    SetConsoleTextAttribute(hConsole, (backgroundColor << 4) | 0);
    // To mau cho buffer
    FillConsoleOutputCharacter(hConsole, ' ', size, coord, &written);
    FillConsoleOutputAttribute(hConsole, (backgroundColor << 4) | 15, size, coord, &written);
    // Di chuyen con tro ve vi tri ban dau
    SetConsoleCursorPosition(hConsole, coord);
}

// Resizes the console window to the specified width and height.
void resizeConsole(int width, int height) {
    HWND console = GetConsoleWindow(); // Get the handle to the console window
    RECT r;
    GetWindowRect(console, &r); // Retrieve the current size and position of the console window

    // Move and resize the console window
    MoveWindow(console, r.left, r.top, width, height, TRUE);
}

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

void setLocale() {
    locale::global(locale("en_US.UTF-8"));
    wcout.imbue(locale());
    SetConsoleOutputCP(CP_UTF8);
}

void clearConsole() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Calculate the number of cells in the buffer
    DWORD cells = csbi.dwSize.X * csbi.dwSize.Y;
    DWORD written;
    COORD coord = { 0, 0 }; // Top-left corner

    // Fill the console with spaces
    FillConsoleOutputCharacter(hConsole, ' ', cells, coord, &written);

    // Reset the color attributes
    FillConsoleOutputAttribute(hConsole, csbi.wAttributes, cells, coord, &written);

    // Move the cursor back to the top-left corner
    SetConsoleCursorPosition(hConsole, coord);
}
