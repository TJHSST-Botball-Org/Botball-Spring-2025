#include <iostream>
#include <Robot.h>

int main()
{
    Robot robot;

    // beginning
    robot.openClaw_Entree();
    robot.move_linear(6.25, -46);

    // grabs burger
    robot.closeClaw_Entree();

    // moves back to black tape
    robot.move_linear(6.25, 25);
    robot.turn_around_left_wheel(90.0);

    // move across board and turns to drop off burger
    robot.move_linear(6.25, -43);
    robot.turn_around_left_wheel(90.0);

    // moves back
    robot.move_linear(6.25, -10);
    robot.openClaw_Entree();
    robot.move_linear(6.25, 10);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, -55);
    robot.move_linear(6.25, 10);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, -17);

    // grabs hotdog
    robot.closeClaw_Entree();
    robot.move_linear(6.25, 29);
    robot.turn_around_left_wheel(90.0);
    robot.move_linear(6.25, -53);
    robot.turn_around_left_wheel(90.0);
    robot.move_linear(6.25, -10);
    robot.openClaw_Entree();

    // robot.move(-10000, 1000);
    // robot.openClaw_Entree();
    // robot.closeClaw_Entree();
    // robot.move(-8000, 1000);
    // robot.rotate(-90, 700);
    // robot.move(5000, 1000);
    // robot.rotate(-90, 500);
    // robot.openClaw_Entree();
    // robot.rotate(-90, 500);
    // robot.move(5000, 1000);
    // robot.rotate(90, 700);
    // robot.move(8000, 1000);

    return 0;
}