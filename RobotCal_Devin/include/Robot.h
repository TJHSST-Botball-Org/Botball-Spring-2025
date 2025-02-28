#pragma once
#include <kipr/wombat.h>

class Robot
{

private:
    static constexpr int LEFT_WHEEL_PIN = 0;
    static constexpr int RIGHT_WHEEL_PIN = 1;

    static constexpr double RIGHT_WHEEL_CONSTANT = 0.5;

public:
    Robot();

    void move(int dist, int speed);
    void rotate(double angle, int speed);
};