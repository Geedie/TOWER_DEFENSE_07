#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#pragma once
using namespace std;

void countdown(int seconds) {
    while (seconds >= 0) {
        int minutes = seconds / 60;  // Tính số phút
        int secs = seconds % 60;    // Tính số giây còn lại

        // Hiển thị thời gian còn lại dưới dạng mm:ss
        cout << setw(2) << setfill('0') << minutes << ":"
            << setw(2) << setfill('0') << secs << flush;

        // Tạm dừng 1 giây
        this_thread::sleep_for(chrono::seconds(1));

        seconds--;
    }
}

