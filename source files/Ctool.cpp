#include "../header files/ctool.h"
mutex ctool::mtx;
void ctool::ShowConsoleCursor(bool showFlag) {
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag; // set the cursor visibility
	SetConsoleCursorInfo(out, &cursorInfo);
}
void ctool::GotoXY(int x, int y) {
	COORD crd = { x,y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), crd);
}
void ctool::Draw(char* str, int i, cpoint p[], cpoint& _p) {
	mtx.lock();
	_p = p[i];
	ctool::GotoXY(_p.getX(), _p.getY());
	cout << str;
	mtx.unlock();
}

void ctool::setLocale() {
	// Đặt locale để hỗ trợ ký tự Unicode
	locale::global(locale("en_US.UTF-8"));
	wcout.imbue(locale());
	SetConsoleOutputCP(CP_UTF8);
	SetConsoleCP(CP_UTF8);
}
void ctool::resizeConsole(int width, int height)
{
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE);
}
void ctool::setColor(ConsoleColor backgroundColor, ConsoleColor textColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Thiết lập thuộc tính màu với nền và chữ
	SetConsoleTextAttribute(hConsole, backgroundColor * 16 + textColor);
}

void ctool::setConsoleBackgroundColor(ConsoleColor backgroundColor) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Lấy thông tin kích thước của console
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);

	// Đặt màu nền cho tất cả các ký tự trong console
	DWORD consoleSize = csbi.dwSize.X * csbi.dwSize.Y;
	DWORD charsWritten;

	// Mã màu nền mới
	WORD colorAttribute = backgroundColor << 4; // Dịch màu nền vào 4 bit cao

	// Điền toàn bộ màn hình với màu nền mới
	FillConsoleOutputAttribute(hConsole, colorAttribute, consoleSize, { 0, 0 }, &charsWritten);

	// Di chuyển con trỏ về đầu màn hình
	SetConsoleCursorPosition(hConsole, { 0, 0 });
}
