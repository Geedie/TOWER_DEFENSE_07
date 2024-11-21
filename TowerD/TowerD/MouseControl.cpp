//#include "oclConsole.h"
//#include<algorithm>
//using namespace std;
//
//class MouseControl : public olcConsoleGameEngine
//{
//private:
//    int posX = 10;
//    int posY = 5;
//public:
//    MouseControl() {
//        m_sAppName = L"Cursor Position";
//    }
//
//protected:
//    virtual bool OnUserCreate() override {
//        return true;
//    }
//
//    virtual bool OnUserUpdate(float fElapsedTime) override {
//        DrawString(1, 1, L"Cursor Position", FG_WHITE);
//        if (!bScreenCleared) {
//            Clear(0);
//            bScreenCleared = true;
//        }
//        if (m_mouse[0].bPressed) { // ấn chọn -> chọn các button trên giao diện và thực thi 
//            DrawString(1, 3, L"Left Mouse Button Pressed", FG_RED);
//        }
//
//        DrawString(1, 2, L"Mouse Position: " + to_wstring(m_mousePosX) + L", " + to_wstring(m_mousePosY), FG_GREEN); //sử dụng (m_mousePosX/Y) để định vị và tô sáng button được chọn
//
//        return true;
//    }
//};
//
//
//class Object : public olcConsoleGameEngine {
//private:
//    int PosX = 0;
//    int PosY = 0;
//public:
//
//};
//
//
//
////test
//int main()
//{
//    MouseControl game;
//    game.ConstructConsole(160, 100, 8, 8); // Thiết lập kích thước console
//    game.Start(); // Bắt đầu game engine
//
//    return 0;
//}