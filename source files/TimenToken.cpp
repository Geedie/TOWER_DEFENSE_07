#include<TimenToken.h>

//Đếm giờ mỗi  màn chơi 
void countdown(int seconds) {
    while (seconds >= 0) {
        int minutes = seconds / 60;  // Tính số phút
        int secs = seconds % 60;    // Tính số giây còn lại

        // Hiển thị thời gian còn lại dưới dạng mm:ss
        cout << setw(2) << setfill('0') << minutes << ":"
            << setw(2) << setfill('0') << secs << flush;

        this_thread::sleep_for(chrono::seconds(1));

        seconds--;
    }
}



int reward(bool enemyDies, string type, Token& token) {
    if (!enemyDies) return 0;

    int rewardAmount = 0;
    if (type == "ene1") rewardAmount = 50;
    else if (type == "ene2") rewardAmount = 100;
    else if (type == "ene3") rewardAmount = 150;

    token.value = token.baseValue + rewardAmount;
    return rewardAmount;
}

// Usage example:
void gameLoop() {
    Token token;
    while (true) {
        token.updateBaseToken(); // Cập nhật token theo thời gian
        // Xử lý game logic và gọi reward() khi cần
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}