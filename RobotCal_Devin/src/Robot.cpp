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

    double currentVelLeft = speed;
    double currentVelRight = speed;

    double lastPosLeft = gmpc(Robot::LEFT_WHEEL_PIN);
    double lastPosRight = gmpc(Robot::RIGHT_WHEEL_PIN);
    double currentPosLeft = gmpc(Robot::LEFT_WHEEL_PIN);
    double currentPosRight = gmpc(Robot::RIGHT_WHEEL_PIN);

    while (currentPosLeft < dist)
    {

        currentVelRight = speed + (currentPosLeft - currentPosRight) * RIGHT_WHEEL_CONSTANT;
        move_at_velocity(Robot::LEFT_WHEEL_PIN, currentVelLeft);
        move_at_velocity(Robot::RIGHT_WHEEL_PIN, currentVelRight);

        lastPosLeft = currentPosLeft;
        lastPosRight = currentPosRight;
        currentPosLeft = gmpc(Robot::LEFT_WHEEL_PIN);
        currentPosRight = gmpc(Robot::RIGHT_WHEEL_PIN);
    }
}

void Robot::rotate(double angle, int speed)
{
}
