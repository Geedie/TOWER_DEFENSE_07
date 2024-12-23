#pragma once
#ifndef TIMENTOKEN_H
#define TIMENTOKEN_H

#include <iostream>
#include <chrono>
#include <thread>
#include <iomanip>
#pragma once
using namespace std;

class Token {
public:
    int value;
    int baseValue;

    Token() : value(0), baseValue(0) {}

    void updateBaseToken() {
        auto now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();
        auto current_seconds = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
        baseValue = current_seconds * 5;
        value = baseValue;
    }
};

void countdown(int seconds);
int reward(bool enemyDies, string type, Token& token);
void gameLoop();
#endif