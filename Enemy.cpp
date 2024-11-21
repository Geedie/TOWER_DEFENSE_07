#include "Enemy.h"

int Enemy::XEne() const { return x; }
int Enemy::YEne() const { return y; }
int Enemy::PrevX() const { return prevX; }
int Enemy::PrevY() const { return prevY; }
bool Enemy::Alive() const { return alive; }

void Enemy::swapPositions(vector<vector<char>>& map, int x1, int y1, int x2, int y2) {
    char temp = map[y1][x1];
    map[y1][x1] = map[y2][x2];
    map[y2][x2] = temp;
}
// Di chuyển kẻ địch theo đường đi
void Enemy::moveEnemy() {
    prevX = x;
    prevY = y;

    if (waypointIndex < path.size()) {
        int targetX = path[waypointIndex].first;
        int targetY = path[waypointIndex].second;
        int dx = targetX - x;
        int dy = targetY - y;

        if (abs(dx) > abs(dy)) {
            x += (dx > 0) ? 1 : -1;
        }
        else {
            y += (dy > 0) ? 1 : -1;
        }

        if (x == targetX && y == targetY) {
            waypointIndex++;
        }
    }
    else {
        alive = false;
    }
}