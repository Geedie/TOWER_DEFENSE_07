#pragma once

#include "../header files/Menu.h"
#include "../header files/consoleHandle.h"
#include "../header files/Setting.h"
#include "../header files/Music.h"
#include "../header files/UI.h"
#include "../header files/MainGame.h"
#include <Windows.h>
#include <mmsystem.h>

#pragma comment(lib, "winmm.lib")

using namespace std;

int main()
{
    resizeConsole(1500, 800);
    Menu menu;
    Setting setting;
    Music music;

    bool MusicOn = true;

    int choice;

    PlaySound(TEXT("resource files/BgSound.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);

backMenu:
    while (true)
    {
        Sleep(100);
        choice = menu.MenuControl();
        if (choice == 3)
            break;
        switch (choice)
        {
        case 0:
            switch (printPlayMenu())
            {
            case 0:
                goto backMenu;
                break;
            case 1:
                switch (printGameModeOption())
                {
                case 0:
                    goto backMenu;
                    break;
                case 1:
                    newGame();
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            break;
        case 1:
            switch (setting.SettingControl())
            {
            case 0:
                goto backMenu;
                break;
            case 1:
                music.MusicControl(MusicOn);
                break;
            }
            break;
        case 2:
            printRankingBoard();
            break;
        default:
            break;
        }
    }

    clearConsole();
    return 0;
}

