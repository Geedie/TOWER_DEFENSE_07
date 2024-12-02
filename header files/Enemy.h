#pragma once
#include "Bullet.h"
// Đối tượng kẻ địch
class Enemy {
private:
    int x, y;               // Tọa độ của kẻ địch
    bool alive;             // Trạng thái sống/chết của kẻ địch
    int prevX, prevY;
    int waypointIndex; 
    int health=1;// Chỉ số của điểm dừng tiếp theo trên đường đi
    vector<pair<int, int>> path; // Các điểm dừng trên đường đi của kẻ địch
public:
    int XEne() const;
    int YEne() const;
    int PrevX() const;
    int PrevY() const;
    bool Alive() const;
    int Health();
    void isAlive(bool check) {
        this->alive = check;
    }
    bool getAlive() {
        return alive;
    }
    // Hàm khởi tạo kẻ địch với tọa độ bắt đầu và đường đi
    Enemy(int startX, int startY, vector<pair<int, int>> path)
        : x(startX), y(startY), alive(true), waypointIndex(0), path(path) {}
    void swapPositions(vector<vector<char>>& map, int x1, int y1, int x2, int y2);
    // Di chuyển kẻ địch theo đường đi
    void moveEnemy();
    void reduceHealth(int dame);
};

