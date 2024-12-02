#include "UI.h"
#include <fstream>
#include <string>
#include <conio.h>
#include <codecvt>
#include "ConsoleSetting.h"

#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")


using namespace std;

void printImageToConsole(const char* filename, int x, int y, ConsoleColor bgColor, ConsoleColor TextColor)
{
	// Sử dụng cách đọc file để in ra màn hình console Tiêu đề

	wifstream inFile;
	inFile.open(filename);

	inFile.imbue(locale(locale(), new codecvt_utf8<wchar_t>));

	if (inFile.is_open())
	{
		ctool::setColor(bgColor, TextColor);
		wstring temp;
		int i = y;
		ctool::GotoXY(x, i);
		while (!inFile.eof())
		{
			i++;
			getline(inFile, temp);
			wcout << temp;
			ctool::GotoXY(x, i);
			// Gán từng dòng và in ra màn hình đến khi hết file .txt
		}
	}
	inFile.close();
}


void printRankingBoard()
{
	ctool::setConsoleBackgroundColor(Cyan);


	printImageToConsole("RankingTitle.txt", 40, 1, Cyan, Black);

	ctool::GotoXY(0, 8);
	for (int i = 0; i < 120; i++)
	{
		cout << "=";
	}

	ctool::GotoXY(15, 7);
	cout << "Top";

	ctool::GotoXY(35, 7);
	cout << "Player";

	ctool::GotoXY(100, 7);
	cout << "Score";

	// Tại đây sẽ sử dụng đọc file để in ra bảng xếp hạng.
	// ...

	POINT cursorPos;
	HWND consoleWindow = GetConsoleWindow();
	while (true) {
		if (GetCursorPos(&cursorPos) && ScreenToClient(consoleWindow, &cursorPos)) {
			int x = cursorPos.x / 8;  // 8 là giả định về kích cỡ ký tự ngang
			int y = cursorPos.y / 16; // 16 là giả định về kích cỡ ký tự dọc

			// In ra màn hình console nút Back to menu, cho phép người chơi quay trở lại giao diện menu
			if (x >= 1 && x <= 15 && y >= 1 && y <= 3) { // Kiểm tra vị trí con chuột
				ctool::setColor(Green, DarkMagenta);

				ctool::GotoXY(1, 1);
				wcout << L"╔══════════════╗";
				ctool::GotoXY(1, 2);
				wcout << L"║ Back to Menu ║";
				ctool::GotoXY(1, 3);
				wcout << L"╚══════════════╝";

				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // Kiểm tra click chuột
				{
					break;
				}
			}
			else {
				ctool::setColor(LightGray, DarkMagenta);

				ctool::GotoXY(1, 1);
				wcout << L"╔══════════════╗";
				ctool::GotoXY(1, 2);
				wcout << L"║ Back to Menu ║";
				ctool::GotoXY(1, 3);
				wcout << L"╚══════════════╝";
			}
		}
	}

	Sleep(100);

	ctool::setColor(Black, LightGray);
	system("cls");
}

int printGameModeOption() {
	// Hàm in ra các lựa chọn mức độ cho trò chơi
	// Khi bấm chọn một mức độ, hàm sẽ trả về giá trị int tương ứng sau:
	//		Easy: return 1
	//		Normal: return 2
	//		Hard: return 3

	system("cls");  // Xóa màn hình trước khi in ra

	ctool::setConsoleBackgroundColor(Cyan);

	printImageToConsole("GameModeTitle.txt", 40, 1, Cyan, DarkRed);

	printImageToConsole("EasyTitle.txt", 69, 10, Yellow, DarkMagenta); // Tọa độ (60, 10) -> (79, 14)
	printImageToConsole("NormalTitle.txt", 65, 16, Yellow, DarkMagenta);// (60, 16) -> (87, 20)
	printImageToConsole("HardTitle.txt", 69, 22, Yellow, DarkMagenta); // (60, 22) -> (79, 26)

	POINT cursorPos;
	HWND consoleWindow = GetConsoleWindow();
	int selectedOption = 0;

	// Vòng lặp kiểm tra sự kiện chuột
	while (true) {
	ChooseOption:
		bool Exit = false;
		while (true) {
			if (GetCursorPos(&cursorPos) && ScreenToClient(consoleWindow, &cursorPos)) {
				int x = cursorPos.x / 8;  // 8 là giả định về kích cỡ ký tự ngang
				int y = cursorPos.y / 16; // 16 là giả định về kích cỡ ký tự dọc

				/*ctool::GotoXY(100, 20);
				cout << "                     ";
				ctool::GotoXY(100, 20);
				cout << x << ", " << y;*/

				// Kiểm tra click chuột trong vùng "Easy"
				if (x >= 63 && x <= 81 && y >= 10 && y <= 14) {
					printImageToConsole("EasyTitle.txt", 69, 10, Green, DarkMagenta);
					printImageToConsole("NormalTitle.txt", 65, 16, Yellow, DarkMagenta);
					printImageToConsole("HardTitle.txt", 69, 22, Yellow, DarkMagenta);

					if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						selectedOption = 1;
						break;
					}
				}
				// Kiểm tra click chuột trong vùng "Normal"
				else if (x >= 60 && x <= 85 && y >= 16 && y <= 20) {
					printImageToConsole("EasyTitle.txt", 69, 10, Yellow, DarkMagenta);
					printImageToConsole("NormalTitle.txt", 65, 16, Green, DarkMagenta);
					printImageToConsole("HardTitle.txt", 69, 22, Yellow, DarkMagenta);

					if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						selectedOption = 2;
						break;
					}
				}
				// Kiểm tra click chuột trong vùng "Hard"
				else if (x >= 63 && x <= 81 && y >= 22 && y <= 26) {
					printImageToConsole("EasyTitle.txt", 69, 10, Yellow, DarkMagenta);
					printImageToConsole("NormalTitle.txt", 65, 16, Yellow, DarkMagenta);
					printImageToConsole("HardTitle.txt", 69, 22, Green, DarkMagenta);

					if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						selectedOption = 3;
						break;
					}
				}
				else
				{
					printImageToConsole("EasyTitle.txt", 69, 10, Yellow, DarkMagenta); // Tọa độ (60, 10) -> (79, 14)
					printImageToConsole("NormalTitle.txt", 65, 16, Yellow, DarkMagenta);// (60, 16) -> (87, 20)
					printImageToConsole("HardTitle.txt", 69, 22, Yellow, DarkMagenta); // (60, 22) -> (79, 26)
				}

				// In ra màn hình console nút Back to menu, cho phép người chơi quay trở lại giao diện menu
				if (x >= 1 && x <= 15 && y >= 1 && y <= 3) { // Kiểm tra vị trí con chuột
					ctool::setColor(Green, DarkMagenta);

					ctool::GotoXY(1, 1);
					wcout << L"╔══════════════╗";
					ctool::GotoXY(1, 2);
					wcout << L"║ Back to Menu ║";
					ctool::GotoXY(1, 3);
					wcout << L"╚══════════════╝";

					if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // Kiểm tra click chuột
					{
						selectedOption = 0;
						Exit = true;
						break;
					}
				}
				else {
					ctool::setColor(LightGray, DarkMagenta);

					ctool::GotoXY(1, 1);
					wcout << L"╔══════════════╗";
					ctool::GotoXY(1, 2);
					wcout << L"║ Back to Menu ║";
					ctool::GotoXY(1, 3);
					wcout << L"╚══════════════╝";
				}
			}
			Sleep(50);  // Giảm tải CPU
		}

		if (Exit)
			break;

		ctool::setColor(Blue, Yellow);
		for (int i = 29; i < 36; i++)
			for (int j = 60; j < 95; j++)
			{
				ctool::GotoXY(j, i);
				cout << " ";
			}

		ctool::GotoXY(65, 30);
		cout << "Start game with ";
		switch (selectedOption)
		{
		case 1:
			cout << "Easy mode?";
			break;
		case 2:
			cout << "Normal mode?";
			break;
		case 3:
			cout << "Hard mode?";
			break;
		default:
			break;
		}

		while (true) {
			if (GetCursorPos(&cursorPos) && ScreenToClient(consoleWindow, &cursorPos)) {
				int x = cursorPos.x / 8;  // 8 là giả định về kích cỡ ký tự ngang
				int y = cursorPos.y / 16; // 16 là giả định về kích cỡ ký tự dọc

				if (x >= 62 && x <= 68 && y >= 32 && y <= 34) {
					ctool::setColor(Green, Black);
					ctool::GotoXY(68, 32);
					wcout << L"╔═════╗";
					ctool::GotoXY(68, 33);
					wcout << L"║ YES ║";
					ctool::GotoXY(68, 34);
					wcout << L"╚═════╝";

					if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						break;
					}
				}
				else if (x >= 73 && x <= 79 && y >= 32 && y <= 34) {
					ctool::setColor(Green, Black);
					ctool::GotoXY(80, 32);
					wcout << L"╔═════╗";
					ctool::GotoXY(80, 33);
					wcout << L"║ NO  ║";
					ctool::GotoXY(80, 34);
					wcout << L"╚═════╝";

					if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
					{
						ctool::setColor(Cyan, Black);
						for (int i = 29; i < 36; i++)
							for (int j = 60; j < 95; j++)
							{
								ctool::GotoXY(j, i);
								cout << " ";
							}
						goto ChooseOption;
					}
				}
				else {
					ctool::setColor(LightGray, Black);

					ctool::GotoXY(68, 32);
					wcout << L"╔═════╗";
					ctool::GotoXY(68, 33);
					wcout << L"║ YES ║";
					ctool::GotoXY(68, 34);
					wcout << L"╚═════╝";

					ctool::GotoXY(80, 32);
					wcout << L"╔═════╗";
					ctool::GotoXY(80, 33);
					wcout << L"║ NO  ║";
					ctool::GotoXY(80, 34);
					wcout << L"╚═════╝";
				}
			}
		}
		break;
	}

	ctool::setColor(Black, LightGray);

	system("cls");

	return selectedOption;
}

int printPlayMenu()
{
	system("cls");  // Xóa màn hình trước khi in ra

	ctool::setConsoleBackgroundColor(Cyan);

	printImageToConsole("PlayTitle.txt", 60, 1, Cyan, DarkRed);

	printImageToConsole("PlayNewTitle.txt", 20, 10, Yellow, DarkMagenta);
	printImageToConsole("PlayRecentTitle.txt", 80, 10, Yellow, DarkMagenta);

	POINT cursorPos;
	HWND consoleWindow = GetConsoleWindow();
	int selectedOption = 0;

	// Vòng lặp kiểm tra sự kiện chuột
	while (true) {
		if (GetCursorPos(&cursorPos) && ScreenToClient(consoleWindow, &cursorPos)) {
			int x = cursorPos.x / 8;  // 8 là giả định về kích cỡ ký tự ngang
			int y = cursorPos.y / 16; // 16 là giả định về kích cỡ ký tự dọc

			if (x >= 18 && x <= 63 && y >= 10 && y <= 24) {
				printImageToConsole("PlayNewTitle.txt", 20, 10, Green, DarkMagenta);
				printImageToConsole("PlayRecentTitle.txt", 80, 10, Yellow, DarkMagenta);

				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					selectedOption = 1;
					break;
				}
			}
			else if (x >= 73 && x <= 124 && y >= 10 && y <= 24) {
				printImageToConsole("PlayRecentTitle.txt", 80, 10, Green, DarkMagenta);
				printImageToConsole("PlayNewTitle.txt", 20, 10, Yellow, DarkMagenta);

				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000)
				{
					selectedOption = 2;
					break;
				}
			}
			else {
				printImageToConsole("PlayNewTitle.txt", 20, 10, Yellow, DarkMagenta);
				printImageToConsole("PlayRecentTitle.txt", 80, 10, Yellow, DarkMagenta);
			}

			// In ra màn hình console nút Back to menu, cho phép người chơi quay trở lại giao diện menu
			if (x >= 1 && x <= 15 && y >= 1 && y <= 3) { // Kiểm tra vị trí con chuột
				ctool::setColor(Green, DarkMagenta);

				ctool::GotoXY(1, 1);
				wcout << L"╔══════════════╗";
				ctool::GotoXY(1, 2);
				wcout << L"║ Back to Menu ║";
				ctool::GotoXY(1, 3);
				wcout << L"╚══════════════╝";

				if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) // Kiểm tra click chuột
				{
					selectedOption = 0;
					break;
				}
			}
			else {
				ctool::setColor(LightGray, DarkMagenta);

				ctool::GotoXY(1, 1);
				wcout << L"╔══════════════╗";
				ctool::GotoXY(1, 2);
				wcout << L"║ Back to Menu ║";
				ctool::GotoXY(1, 3);
				wcout << L"╚══════════════╝";
			}
		}

		Sleep(50);
	}

	ctool::setColor(Black, LightGray);
	system("cls");
	return selectedOption;
}

//int main()
//{
//	ctool::setLocale();
//	//ctool::resizeConsole(1400, 800);
//	ctool::ShowConsoleCursor(false);
//
//	ConsoleSetting setting;
//	setting.ShowScrollbar(false);
//	setting.SetBufferSize(180, 45);
//	setting.SetWindowSize(180, 45);
//
//	PlaySound(TEXT("BgSound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
//
//	//printRankingBoard();
//
//	/*while (true)
//	{*/
//		switch (printPlayMenu())
//		{
//		case 1:
//			switch (printGameModeOption())
//			{
//			case 1:
//				PlaySound(NULL, 0, 0);
//				printRankingBoard();
//				break;
//			default:
//				break;
//			}
//
//			//cout << printGameModeOption();
//			break;
//		case 2:
//			break;
//		default:
//			break;
//		}
//	/*}*/
//	
//	
//	
//	
//	ctool::setColor(Black, LightGray);
//	return 0;
//}
