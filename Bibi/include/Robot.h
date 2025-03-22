#pragma once
#include <kipr/wombat.h>

class Robot
{

private:
    static constexpr int LEFT_WHEEL_PIN = 0;
    static constexpr int RIGHT_WHEEL_PIN = 1;

    static constexpr int ENTREE_SERVO_PIN = 2;
    static constexpr int ENTREE_OPEN_POS = 1425;
    static constexpr int ENTREE_CLOSED_POS = 2047;

    static constexpr int BOTTLE_ARM_PIN = 1;
    static constexpr int BOTTLE_CLAW_PIN = 0;
    static constexpr int BOTTLE_OPEN_POS = 1080;
    static constexpr int BOTTLE_CLOSED_POS = 1730;
    static constexpr int BOTTLE_ARM_CLOSED_POS = 0;
    static constexpr int BOTTLE_ARM_OPEN_POS = 1542;

    static constexpr double LEFT_TICKS_PER_INCH = 230;
    static constexpr double RIGHT_TICKS_PER_INCH = 240;

    static constexpr double PI = 3.141592654;

public:
    Robot();

    void move_linear(double speed_inch_per_sec, double distance_inch, int wait_offset_ms = 0);
    void turn_around_left_wheel(double degrees, int wait_offset_ms = 0);
    void turn_around_right_wheel(double degrees, int wait_offset_ms = 0);
    void stop();

    void move_bottle_arm(int position, int duration);

    void openClaw_Bottle();
    void closeClaw_Bottle();

    void openClaw_Entree();
    void closeClaw_Entree();
    void fold_bottle_arm();
    void unfold_bottle_arm();
    void set_bottle_arm(int pos);
};