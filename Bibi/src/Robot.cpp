#include <Robot.h>
#include <iostream>

using namespace std;

Robot::Robot()
{
}

void Robot::stop()
{
    move_at_velocity(Robot::LEFT_WHEEL_PIN, 0);
    move_at_velocity(Robot::RIGHT_WHEEL_PIN, 0);
    msleep(100);
}

void Robot::move_linear(double speed_inch_per_sec, double distance_inch, int wait_offset_ms)
{
    /*
        Moves distance_inch at speed_inch_per_sec. Waits an extra wait_offset_ms milliseconds
        Try to always move at 5 inches per second
        Backwards is negative distance values. Keep speed positive.
    */

    double mult = distance_inch / abs(distance_inch);
    cout << "Left : " << mult * speed_inch_per_sec * Robot::LEFT_TICKS_PER_INCH << endl;
    cout << "Right : " << mult * speed_inch_per_sec * Robot::RIGHT_TICKS_PER_INCH << endl;
    move_at_velocity(Robot::LEFT_WHEEL_PIN, mult * speed_inch_per_sec * Robot::LEFT_TICKS_PER_INCH);
    move_at_velocity(Robot::RIGHT_WHEEL_PIN, mult * speed_inch_per_sec * Robot::RIGHT_TICKS_PER_INCH);
    msleep(abs(distance_inch / speed_inch_per_sec * 1000) + wait_offset_ms);
    stop();
}

void Robot::turn_around_left_wheel(double degrees, int wait_offset_ms)
{
    /*
        Rotates 90 degrees at a constant speed.

        If degrees is positive then clockwise, negative is CCW
    */
    degrees *= -1;
    double distance = 2 * Robot::PI * 11.8 * (degrees / 360);
    double mult = distance / abs(distance);
    move_at_velocity(Robot::RIGHT_WHEEL_PIN, mult * 5 * Robot::RIGHT_TICKS_PER_INCH);
    msleep(abs(distance / 5 * 1000) + wait_offset_ms); // 5 inches per second
    stop();
}
void Robot::turn_around_right_wheel(double degrees, int wait_offset_ms)
{
    /*
        Rotates 90 degrees at a constant speed.
        If degrees is positive then clockwise, negative is CCW
    */
    double distance = 2 * PI * 11.8 * (degrees / 360);
    double mult = distance / abs(distance);
    move_at_velocity(Robot::LEFT_WHEEL_PIN, mult * 5 * Robot::LEFT_TICKS_PER_INCH);
    msleep(abs(distance / 5 * 1000) + wait_offset_ms); // 5 inches per second
    stop();
}

void Robot::move_bottle_arm(int position, int duration)
{
    enable_servo(Robot::BOTTLE_ARM_PIN);
    set_servo_position(Robot::BOTTLE_ARM_PIN, position);
    msleep(duration);
}

void Robot::openClaw_Bottle()
{
    enable_servo(Robot::BOTTLE_CLAW_PIN);
    set_servo_position(Robot::BOTTLE_CLAW_PIN, Robot::BOTTLE_OPEN_POS);
    msleep(1000);
}

void Robot::closeClaw_Bottle()
{
    enable_servo(Robot::BOTTLE_CLAW_PIN);
    set_servo_position(Robot::BOTTLE_CLAW_PIN, Robot::BOTTLE_CLOSED_POS);
    msleep(1000);
}

void Robot::openClaw_Entree()
{
    enable_servo(Robot::ENTREE_SERVO_PIN);
    set_servo_position(Robot::ENTREE_SERVO_PIN, Robot::ENTREE_OPEN_POS);
    msleep(1000);
}

void Robot::closeClaw_Entree()
{
    enable_servo(Robot::ENTREE_SERVO_PIN);
    set_servo_position(Robot::ENTREE_SERVO_PIN, Robot::ENTREE_CLOSED_POS);
    msleep(1000);
}

void Robot::set_bottle_arm(int pos)
{
    enable_servo(Robot::BOTTLE_ARM_PIN);
    set_servo_position(Robot::BOTTLE_ARM_PIN, pos);
    msleep(1000);
}
void Robot::fold_bottle_arm()
{
    set_bottle_arm(Robot::BOTTLE_ARM_CLOSED_POS);
}
void Robot::unfold_bottle_arm()
{
    set_bottle_arm(Robot::BOTTLE_ARM_OPEN_POS);
}