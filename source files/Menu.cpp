#include "Menu.h"

// Draws a box with text from a file at specified coordinates.
void drawBox(const char* filename, int width, int posX, int posY, bool isSelected) {
    COORD coord;
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ifstream file(filename);

    // Set text attributes based on selection state
    SetConsoleTextAttribute(hConsole, isSelected ? (14 | (5 << 4)) : (0 | (11 << 4)));

    // Draw the top border of the box
    coord.X = posX;
    coord.Y = posY;
    SetConsoleCursorPosition(hConsole, coord);
    cout << " " << string(width - 2, '-') << " " << endl;

    // Prepare to draw the content of the box
    coord.Y++;
    string line;

    // Draw each line from the file
    while (getline(file, line)) {
        int lineLength = line.length();
        int totalPadding = max(0, width - 2 - lineLength); // Calculate padding

        // Calculate padding in one go to avoid unnecessary calculations
        int leftPadding = totalPadding / 2;
        int rightPadding = totalPadding - leftPadding;

        // Move to the next line in the box
        SetConsoleCursorPosition(hConsole, coord);
        cout << "|" << string(leftPadding, ' ') << line << string(rightPadding, ' ') << "|" << endl;
        coord.Y++;
    }

    // Draw the bottom border of the box
    coord.X = posX;
    SetConsoleCursorPosition(hConsole, coord);
    cout << " " << string(width - 2, '-') << " " << endl;

    // Restore default text color after drawing
    SetConsoleTextAttribute(hConsole, 0 | (7 << 4)); // Default console color
}

// Draws the title from "Menu.txt" at specified coordinates.
void drawTitle(int width, int posX, int posY) {
    COORD coord = { static_cast<SHORT>(posX), static_cast<SHORT>(posY) };
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ifstream file("Menu.txt");

    string line;

    // Move the cursor to the starting position
    SetConsoleCursorPosition(hConsole, coord);

    // Read and print each line
    while (getline(file, line)) {
        // Print the line and move the cursor down
        cout << line << endl;

        // Increment Y position for the next line
        coord.Y++;
        SetConsoleCursorPosition(hConsole, coord);
    }

    file.close(); // Close the file stream
}

void printTitle() {
    static const int boxWidth = 30; // Width of the menu boxes
    static int consoleWidth = getConsoleWidth(); // Get the width of the console once
    static int consoleHeight = getConsoleHeight(); // Get the height of the console once
    static int startY = consoleHeight / 2; // Center Y position, calculated once

    static int positionX = (consoleWidth - boxWidth) / 2; // Center X position, calculated once

    setLocale(); // Set locale
    drawTitle(100, positionX - 4, startY - 18); // Draw title
}

int printOption() {
    static const int boxWidth = 16;   // Width of the menu boxes
    static int consoleWidth = getConsoleWidth(); // Get the width of the console once
    static int consoleHeight = getConsoleHeight(); // Get the height of the console once
    static int startY = consoleHeight / 2; // Center Y position

    static int positionX = (consoleWidth - boxWidth) / 2; // Center X position, calculated once

    HWND consoleWindow = GetConsoleWindow();

    // Store file names
    const char* playFileName = "PlayOpt.txt";
    const char* settingFileName = "SettingOpt.txt";
    const char* rankFileName = "RankOpt.txt";
    const char* exitFileName = "Exit.txt";

    // Preload the files at the start
    ifstream playFile(playFileName);
    ifstream settingFile(settingFileName);
    ifstream rankFile(rankFileName);

    bool leftButtonPressed = false;
    int selection = 0;

    while (true) {
        // Get cursor position
        POINT cursorPos;
        if (GetCursorPos(&cursorPos) && ScreenToClient(consoleWindow, &cursorPos)) {
            int x = cursorPos.x / 8; // Assuming 8 pixels per character
            int y = cursorPos.y / 16; // Assuming 16 pixels per line

            // Determine which box to highlight based on cursor position
            bool isPlayHighlighted = (x >= positionX - 14 && x <= positionX + boxWidth - 7 && y > startY - 9 && y < startY - 3);
            bool isSettingHighlighted = (x >= positionX - 14 && x <= positionX + boxWidth - 7 && y > startY - 1 && y < startY + 5);
            bool isRankHighlighted = (x >= positionX - 14 && x <= positionX + boxWidth - 7 && y > startY + 7 && y < startY + 13);
            bool isExitHighlighted = (x >= positionX - 14 && x <= positionX + boxWidth - 7 && y > startY + 15 && y < startY + 21);

            // Draw boxes based on current highlight states
            drawBox(playFileName, boxWidth + 2, positionX - 2, startY - 8, isPlayHighlighted);
            drawBox(settingFileName, boxWidth + 14, positionX - 7, startY, isSettingHighlighted);
            drawBox(rankFileName, boxWidth + 2, positionX - 2, startY + 8, isRankHighlighted);
            drawBox(exitFileName, boxWidth + 2, positionX - 2, startY + 16, isExitHighlighted);

            // Handle left button click only for the settings box
            if (isPlayHighlighted && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
                if (!leftButtonPressed) { // Trigger only on the first press
                    leftButtonPressed = true;
                    selection = 0; // Set selection to the setting box
                    break;
                }
            }
            else {
                leftButtonPressed = false; // Reset if button is released
            }

            // Handle left button click only for the settings box
            if (isSettingHighlighted && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
                if (!leftButtonPressed) { // Trigger only on the first press
                    leftButtonPressed = true;
                    selection = 1; // Set selection to the setting box
                    break;
                }
            }
            else {
                leftButtonPressed = false; // Reset if button is released
            }

            // Handle left button click only for the settings box
            if (isRankHighlighted && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
                if (!leftButtonPressed) { // Trigger only on the first press
                    leftButtonPressed = true;
                    selection = 2; // Set selection to the setting box
                    break;
                }
            }
            else {
                leftButtonPressed = false; // Reset if button is released
            }

            // Handle left button click only for the settings box
            if (isExitHighlighted && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
                if (!leftButtonPressed) { // Trigger only on the first press
                    leftButtonPressed = true;
                    selection = 3; // Set selection to the setting box
                    break;
                }
            }
            else {
                leftButtonPressed = false; // Reset if button is released
            }

        }

        Sleep(1); // Adjust sleep time as needed
    }

    // Close the file streams when done (this point may not be reached in an infinite loop)
    playFile.close();
    settingFile.close();
    rankFile.close();

    return selection;
}

// Prints the entire menu by calling drawBox for each section.
int Menu::MenuControl() {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    //Hide cursor
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hConsole, &cursorInfo);
    cursorInfo.bVisible = false; // set the cursor visibility
    SetConsoleCursorInfo(hConsole, &cursorInfo);

    setConsoleBackgroundColor(11); // Set background color

    printTitle(); // Draw title
    return printOption(); // Draw options
}