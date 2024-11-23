//#include <Windows.h>
//#include <iostream>
//#include"ConsoleSetting.h"
//using namespace std;
//
//void SetWindowInfo(HANDLE hConsole, const SMALL_RECT& rect) {
//    SetConsoleWindowInfo(hConsole, TRUE, &rect);
//}
//
//BOOL ShowScrollBar(HWND hWnd, int wBar, BOOL bShow) {
//    return ::ShowScrollBar(hWnd, wBar, bShow); // Sử dụng toán tử phạm vi để gọi hàm API
//}
//
//void ShowScrollbar(BOOL Show) {
//    HWND hWnd = GetConsoleWindow();
//    ShowScrollBar(hWnd, SB_BOTH, Show);
//}
//
////BOOL DeleteMenu(HMENU hMenu, UINT uPosition, UINT uFlags) {
////    return ::DeleteMenu(hMenu, uPosition, uFlags); // Gọi hàm API
////}
//
//void DisableCtrButton(bool Close, bool Min, bool Max) {
//    HWND hWnd = GetConsoleWindow();
//    HMENU hMenu = GetSystemMenu(hWnd, FALSE);
//
//    if (Close) {
//        DeleteMenu(hMenu, SC_CLOSE, MF_BYCOMMAND);
//    }
//    if (Min) {
//        DeleteMenu(hMenu, SC_MINIMIZE, MF_BYCOMMAND);
//    }
//    if (Max) {
//        DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);
//    }
//}
//
//void SetBufferSize(HANDLE hConsole, int width, int height) {
//    COORD newSize;
//    newSize.X = static_cast<SHORT>(width);
//    newSize.Y = static_cast<SHORT>(height);
//    if (!SetConsoleScreenBufferSize(hConsole, newSize)) {
//        std::cerr << "Failed to set buffer size. Error: " << GetLastError() << std::endl;
//    }
//}
//
//void SetWindowSize(SHORT width, SHORT height) {
//    HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    SMALL_RECT windowSize;
//    windowSize.Top = 0;
//    windowSize.Left = 0;
//    windowSize.Right = width - 1;  // Giảm 1 vì RIGHT là chỉ số cuối cùng
//    windowSize.Bottom = height - 1; // Giảm 1 vì BOTTOM là chỉ số cuối cùng
//
//    if (!SetConsoleWindowInfo(hStdout, TRUE, &windowSize)) {
//        std::cerr << "Failed to set window size. Error: " << GetLastError() << std::endl;
//    }
//}
//
////void ConsoleSetting::ShowConsoleCursor(bool showFlag) {
////    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
////    CONSOLE_CURSOR_INFO cursorInfo;
////    GetConsoleCursorInfo(out, &cursorInfo);
////    cursorInfo.bVisible = showFlag; // set the cursor visibility
////    SetConsoleCursorInfo(out, &cursorInfo);
////}