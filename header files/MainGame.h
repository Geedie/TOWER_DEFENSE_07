#pragma once

#include "../header files/Map.h"
#include "../header files/Ctool.h"
#include "../header files/Bullet.h"
#include "../header files/Tower.h"
#include "../header files/Enemy.h"
#include "../header files/ConsoleSetting.h"

void setCursorPosition(int x, int y);
void clearMessage();
void clearOldPosition(int x, int y);
void drawScreen(vector<Enemy>& enemies, Tower& tower, const vector<pair<int, int>>& path);
void checkCollisions(vector<Enemy>& enemies, Tower& tower);
bool startNewLevel(int level);
void setupEnemies(vector<Enemy>& enemies, int level, const vector<pair<int, int>>& path, int x, int y);
int newGame();