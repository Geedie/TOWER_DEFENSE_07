#include "Map.h"
#include "Ctool.h"
#include "Bullet.h"
#include "Tower.h"
#include "Enemy.h"

mutex screenMutex;



void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void clearMessage() {
    // Xóa thông báo dưới màn hình
    setCursorPosition(0, SCREEN_HEIGHT + 1);
    cout << string(SCREEN_WIDTH, ' '); // Sử dụng SCREEN_WIDTH thay vì 50

    // Xóa thông báo giữa màn hình
    setCursorPosition(0, TOWER_Y + 2);
    cout << string(SCREEN_WIDTH, ' '); // Sử dụng SCREEN_WIDTH thay vì 50
}

void clearOldPosition(int x, int y) {
    setCursorPosition(x, y);
    cout << " ";
}

void drawScreen(vector<Enemy>& enemies, Tower& tower, const vector<pair<int, int>>& path) {
    screenMutex.lock();

    /*for (const auto& waypoint : path) {
        setCursorPosition(waypoint.first, waypoint.second);
        wcout << "*";
    }*/

    for (auto& enemy : enemies) {
        if (enemy.Alive()) {
            clearOldPosition(enemy.PrevX(), enemy.PrevY());
            setCursorPosition(enemy.XEne(), enemy.YEne());
            wcout << "E";
        }
    }

    setCursorPosition(tower.X(), tower.Y());
    wcout << "T";

    for (auto& bullet : tower.Bullets()) {
        clearOldPosition(static_cast<int>(bullet.XBull() - bullet.Dx()), static_cast<int>(bullet.YBull() - bullet.Dy()));
        setCursorPosition(static_cast<int>(bullet.XBull()), static_cast<int>(bullet.YBull()));
        wcout << "+";
    }

    screenMutex.unlock();
}

void checkCollisions(vector<Enemy>& enemies, Tower& tower) {
    for (auto& enemy : enemies) {
        for (size_t i = 0; i < tower.Bullets().size(); i++) {
            if (enemy.isAlive() && static_cast<int>(tower.Bullets()[i].XBull()) == enemy.XEne() && static_cast<int>(tower.Bullets()[i].YBull()) == enemy.YEne()) {
                enemy.isAlive();
                tower.Bullets().erase(tower.Bullets().begin() + i);
                break;
            }
        }
    }
}

bool startNewLevel(int level) {
    clearMessage(); 
    setCursorPosition(0, SCREEN_HEIGHT + 10);
    wcout << "Level " << level << " - Press Enter to start.";
    cin.get();
    clearMessage();  // Xóa dòng thông báo sau khi nhấn Enter
    return true;
}

void setupEnemies(vector<Enemy>& enemies, int level, const vector<pair<int, int>>& path) {
    enemies.clear();
    int enemyCount = 3 + level * 2;

    for (int i = 0; i < enemyCount; i++) {
        enemies.emplace_back(99, 1, path);
    }
}

int main() {
    Ctool::setLocale();
    int level = 1;
    Map a;
    a.DisplayMap1();
    Tower tower(TOWER_X, TOWER_Y);
    const vector<pair<int, int>> path = {
        {99, 1}, {99, 10}, {39, 10}, {39, 32}, {122, 32}, {SCREEN_WIDTH - 1, 0}
    };

    while (true) {
        vector<Enemy> enemies;
        setupEnemies(enemies, level, path);

        if (!startNewLevel(level)) break;

        while (true) {
            bool allEnemiesDefeated = true;

            for (auto& enemy : enemies) {
                if (enemy.Alive()) {
                    enemy.moveEnemy();
                    allEnemiesDefeated = false;
                }
            }

            for (auto& enemy : enemies) {
                if (enemy.Alive()) {
                    tower.shoot(enemy);
                }
            }

            tower.updateBullets();
            checkCollisions(enemies, tower);
            drawScreen(enemies, tower, path);

            if (allEnemiesDefeated) {
                setCursorPosition(0, TOWER_Y + 2);
                wcout << "All enemies defeated! Level " << level << " completed!" << endl;
                level++;
                break;
            }

            this_thread::sleep_for(chrono::milliseconds(200 - level * 20));
        }
    }
    return 0;
}