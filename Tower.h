#pragma once
#include "Bullet.h"
#include "Enemy.h"
// Đối tượng tháp
class Tower {
private:
    int x, y;              // Tọa độ của tháp
    vector<Bullet> bullets; // Danh sách các viên đạn
public:
    vector<Bullet> Bullets() {
        return bullets;
    }
    int X() { return x; }
    int Y() { return y; }
    Tower(int posX, int posY) : x(posX), y(posY) {}

    // Bắn đạn nếu kẻ địch trong tầm bắn
    void shoot(Enemy& enemy);
    // Cập nhật vị trí của đạn
    void updateBullets();
};
