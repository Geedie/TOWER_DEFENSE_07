#include "Tower.h"

// Bắn đạn nếu kẻ địch trong tầm bắn
void Tower::shoot(Enemy& enemy) {
    if (abs(enemy.XEne() - x) <= TOWER_RANGE && abs(enemy.YEne() - y) <= TOWER_RANGE) {
        // Tạo viên đạn hướng về phía kẻ địch
        bullets.emplace_back(x, y, enemy.XEne(), enemy.XEne(), BULLET_SPEED);
    }
}

// Cập nhật vị trí của đạn
void Tower::updateBullets() {
    for (auto& bullet : bullets) {
        bullet.moveBullet(); // Di chuyển đạn
    }
    // Xóa các viên đạn ra khỏi màn hình khi đi ra ngoài giới hạn
    bullets.erase(remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {
        return b.outOfBounds();
        }), bullets.end());
}