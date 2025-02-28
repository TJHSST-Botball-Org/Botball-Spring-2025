#include <Robot.h>
#include <iostream>

using namespace std;

Robot::Robot()
{
}

void Robot::move(int dist, int speed)
{
    cmpc(Robot::LEFT_WHEEL_PIN);
    cmpc(Robot::RIGHT_WHEEL_PIN);

    while (gmpc(Robot::LEFT_WHEEL_PIN) < dist)
    {
        mav(Robot::LEFT_WHEEL_PIN, speed);
        mav(Robot::RIGHT_WHEEL_PIN, speed);
    }
}

void Robot::rotate(double angle, int speed)
{
    cmpc(Robot::LEFT_WHEEL_PIN);
    cmpc(Robot::RIGHT_WHEEL_PIN);

    while (gmpc(Robot::LEFT_WHEEL_PIN) < angle)
    {
        mav(Robot::LEFT_WHEEL_PIN, speed);
        mav(Robot::RIGHT_WHEEL_PIN, -speed);
    }
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
}

void Robot::closeClaw_Entree()
{
    enable_servo(Robot::ENTREE_SERVO_PIN);
    set_servo_position(Robot::ENTREE_SERVO_PIN, Robot::ENTREE_CLOSED_POS);
}
