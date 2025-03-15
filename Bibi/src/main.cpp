#include <iostream>
#include <Robot.h>

int main()
{
    Robot robot;
    robot.move(-10000, 1000);
    robot.openClaw_Entree();
    robot.closeClaw_Entree();
    robot.move(-8000, 1000);
    robot.rotate(-90, 700);
    robot.move(5000, 1000);
    robot.rotate(-90, 500);
    robot.openClaw_Entree();
    robot.rotate(-90, 500);
    robot.move(5000, 1000);
    robot.rotate(90, 700);
    robot.move(8000, 1000);

    return 0;
}