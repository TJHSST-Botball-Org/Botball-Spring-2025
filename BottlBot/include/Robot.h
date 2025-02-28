#pragma once
#include <kipr/wombat.h>

class Robot
{

private:
    static constexpr int LEFT_WHEEL_PIN = 0;
    static constexpr int RIGHT_WHEEL_PIN = 1;

    static constexpr int ENTREE_SERVO_PIN = 0;
    static constexpr int ENTREE_OPEN_POS = 1230;
    static constexpr int ENTREE_CLOSED_POS = 1670;

    static constexpr int BOTTLE_ARM_PIN = 2;
    static constexpr int BOTTLE_CLAW_PIN = 1;
    static constexpr int BOTTLE_OPEN_POS = 300;
    static constexpr int BOTTLE_CLOSED_POS = 90;

    static constexpr double RIGHT_WHEEL_CONSTANT = 0.5;

public:
    Robot();

    void move(int dist, int speed);
    void rotate(double angle, int speed);

    void move_bottle_arm(int position, int duration);

    void openClaw_Bottle();
    void closeClaw_Bottle();

    void openClaw_Entree();
    void closeClaw_Entree();
};