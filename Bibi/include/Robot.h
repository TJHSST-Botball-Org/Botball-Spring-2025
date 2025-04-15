#pragma once
#include <kipr/wombat.h>

class Robot
{

private:
    static constexpr int LEFT_WHEEL_PIN = 0;
    static constexpr int RIGHT_WHEEL_PIN = 1;

    static constexpr int ENTREE_SERVO_PIN = 2;
    static constexpr int ENTREE_OPEN_POS = 520;
    static constexpr int ENTREE_CLOSED_POS = 866;

    static constexpr int BOTTLE_ARM_PIN = 1;
    static constexpr int BOTTLE_CLAW_PIN = 0;
    static constexpr int BOTTLE_OPEN_POS = 1432;
    static constexpr int BOTTLE_CLOSED_POS = 1890;
    static constexpr int BOTTLE_ARM_FOLD_POS = 250;
    static constexpr int BOTTLE_ARM_UP_POS = 1133;
    static constexpr int BOTTLE_ARM_DOWN_POS = 1610; // 1582

    static constexpr double LEFT_TICKS_PER_INCH = 226;
    static constexpr double RIGHT_TICKS_PER_INCH = 240;

    static constexpr int ENTREE_SWITCH_PIN = 0;

    static constexpr double PI = 3.141592654;

public:
    Robot();
    ~Robot();

    void move_linear(double speed_inch_per_sec, double distance_inch, bool stopAtEnd = 1, int wait_offset_ms = 0);
    void move_linear_until_switch(bool forward, double speed_inch_per_sec, int wait_offset_ms = 0);
    void turn_around_left_wheel(double degrees, int wait_offset_ms = 0);
    void turn_around_right_wheel(double degrees, int wait_offset_ms = 0);
    void stop();

    void move_bottle_arm(int position, int duration);

    void open_claw_bottle();
    void close_claw_bottle();

    void openClaw_Entree();
    void closeClaw_Entree();
    void bottle_arm_up();
    void bottle_arm_down();
    void fold_bottle_arm();
    void set_bottle_arm(int pos, int deltaTime);
};