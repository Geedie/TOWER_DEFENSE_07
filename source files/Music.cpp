#include "../header files/Music.h"

void drawMusicTitle(int width, int posX, int posY) {
	COORD coord = { static_cast<SHORT>(posX), static_cast<SHORT>(posY) };
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	ifstream file("resource files/MusicTitle.txt");

	string line;

	SetConsoleCursorPosition(hConsole, coord);

	while (getline(file, line)) {
		SetConsoleCursorPosition(hConsole, coord);
		cout << line << endl;
		coord.Y++;
	}

	file.close();
}

void printMusicTitle() {
	static const int boxWidth = 30; // Width of the menu boxes
	static int consoleWidth = getConsoleWidth(); // Get the width of the console once
	static int consoleHeight = getConsoleHeight(); // Get the height of the console once
	static int startY = consoleHeight / 2; // Center Y position, calculated once

	static int positionX = (consoleWidth - boxWidth) / 2; // Center X position, calculated once

	setLocale(); // Set locale
	drawMusicTitle(100, positionX - 4, startY - 18); // Draw title
}

void drawBackgroundMusicBox(const char* filename, int width, int posX, int posY, bool isSelected, bool isChosen) {
	COORD coord;
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	ifstream file(filename);

	if (!isSelected) {
		if (isChosen) {
			SetConsoleTextAttribute(hConsole, 11 | (0 << 4));
		}
		else {
			SetConsoleTextAttribute(hConsole, 0 | (11 << 4));
		}
	}
	else {
		SetConsoleTextAttribute(hConsole, 11 | (0 << 4));
	}

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

		// Calculate left and right padding
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
}

void printBackgroundMusic(bool& MusicOn) {
	static const int boxWidth = 30; // Width of the menu boxes
	static int consoleWidth = getConsoleWidth(); // Get the width of the console once
	static int consoleHeight = getConsoleHeight(); // Get the height of the console once
	static int startY = consoleHeight / 2; // Center Y position, calculated once

	static int positionX = (consoleWidth - boxWidth) / 2; // Center X position, calculated once

	HWND consoleWindow = GetConsoleWindow();

	drawBackgroundMusicBox("resource files/BackgroundMusic.txt", boxWidth + 12, positionX - 36, startY - 8, true, false);

	bool leftButtonPressed = false;
	bool isSelected = true;
	int selection = 0;
	if (!MusicOn) {
		selection = 1;
	}

	while (true) {
		// Get cursor position
		POINT cursorPos;
		if (GetCursorPos(&cursorPos) && ScreenToClient(consoleWindow, &cursorPos)) {
			int x = cursorPos.x / 8; // Assuming 8 pixels per character
			int y = cursorPos.y / 16; // Assuming 16 pixels per line

			bool isOnHighlighted = (x > positionX + 12 && x < positionX + 22 && y > startY - 9 && y < startY - 3);
			bool isOffHighlighted = (x > positionX + 22 && x < positionX + 36 && y > startY - 9 && y < startY - 3);
			bool isBackHighlighted = (x >= positionX - 16 && x <= positionX + boxWidth - 3 && y > startY + 7 && y < startY + 14);

			drawBackgroundMusicBox("resource files/BackToMenu.txt", boxWidth + 16, positionX - 7, startY + 8, isBackHighlighted, false);

			if (MusicOn) {
				drawBackgroundMusicBox("resource files/OnOption.txt", boxWidth - 20, positionX + 24, startY - 8, isOnHighlighted, true);
				drawBackgroundMusicBox("resource files/OffOption.txt", boxWidth - 16, positionX + 36, startY - 8, isOffHighlighted, false);
			}
			else {
				drawBackgroundMusicBox("resource files/OnOption.txt", boxWidth - 20, positionX + 24, startY - 8, isOnHighlighted, false);
				drawBackgroundMusicBox("resource files/OffOption.txt", boxWidth - 16, positionX + 36, startY - 8, isOffHighlighted, true);
			}

			// Handle left button click only for the settings box
			if (isOnHighlighted && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
				if (!leftButtonPressed) { // Only on the first press
					leftButtonPressed = true;
					MusicOn = true;
					PlaySound(TEXT("resource files/BgSound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
				}
			}
			else {
				leftButtonPressed = false; // Reset if button is released
			}
			// Handle left button click only for the settings box
			if (isOffHighlighted && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
				if (!leftButtonPressed) { // Only on the first press
					leftButtonPressed = true;
					MusicOn = false;
					PlaySound(NULL, 0, 0);
				}
			}
			else {
				leftButtonPressed = false; // Reset if button is released
			}


			if (isBackHighlighted && (GetAsyncKeyState(VK_LBUTTON) & 0x8000)) {
				if (!leftButtonPressed) { // Only on the first press
					leftButtonPressed = true;
					break;
				}
			}
			else {
				leftButtonPressed = false; // Reset if button is released
			}
		}
	}
}

void Music::MusicControl(bool& MusicOn) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	//Hide cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsole, &cursorInfo);
	cursorInfo.bVisible = false; // set the cursor visibility
	SetConsoleCursorInfo(hConsole, &cursorInfo);

	setConsoleBackgroundColor(11); // Set background color

	printMusicTitle();
	printBackgroundMusic(MusicOn);
}