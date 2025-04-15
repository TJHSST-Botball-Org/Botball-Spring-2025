#include <iostream>
#include <Robot.h>

int main()
{
    Robot robot;

    // beginning
    robot.close_claw_bottle();
    robot.fold_bottle_arm();
    robot.openClaw_Entree();
    msleep(9000);
    robot.move_linear_until_switch(0, 6.25);
    robot.move_linear(6.25, 2);

    // grabs burger
    robot.closeClaw_Entree();
    msleep(7000);

    // moves back to black tape
    robot.move_linear(6.25, 20);
    robot.turn_around_left_wheel(90);

    // move across board and turns to drop off burger
    robot.move_linear(6.25, -38);
    robot.turn_around_left_wheel(90);

    // moves back
    robot.move_linear(6.25, -10);
    robot.move_linear(6.25, 2);
    robot.openClaw_Entree();

    robot.move_linear(6.25, 10);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, -50);
    robot.move_linear(6.25, 10);
    robot.turn_around_left_wheel(90);
    robot.move_linear_until_switch(0, 6.25);
    robot.move_linear(6.25, 2);

    // grabs hotdog
    robot.closeClaw_Entree();
    robot.move_linear(6.25, 20);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, -35);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, -10);
    robot.move_linear(6.25, 2);
    robot.openClaw_Entree();

    // Plastic Bottles
    robot.turn_around_left_wheel(-6);
    robot.open_claw_bottle();
    robot.bottle_arm_down();
    robot.move_linear(6.25, 13);
    robot.close_claw_bottle();
    robot.bottle_arm_up();
    robot.move_linear(6.25, -3);
    robot.turn_around_left_wheel(90);
    robot.turn_around_left_wheel(95);
    robot.move_linear(6.25, -10);
    robot.move_linear(6.25, 16);
    robot.bottle_arm_down();
    robot.open_claw_bottle();
    robot.bottle_arm_up();

    robot.move_linear(6.25, -5);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, 6.5);
    robot.turn_around_left_wheel(90);
    robot.bottle_arm_down();
    robot.move_linear(6.25, 13);
    robot.close_claw_bottle();
    robot.bottle_arm_up();
    robot.move_linear(6.25, -3);
    robot.turn_around_left_wheel(90);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, -10);
    robot.move_linear(6.25, 16);
    robot.bottle_arm_down();
    robot.open_claw_bottle();
    robot.bottle_arm_up();

    robot.move_linear(6.25, -10);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, 6.4);
    robot.turn_around_left_wheel(90);
    robot.bottle_arm_down();
    robot.move_linear(6.25, 8);
    robot.close_claw_bottle();
    robot.bottle_arm_up();
    robot.move_linear(6.25, -3);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, 4);
    robot.turn_around_left_wheel(70);
    robot.move_linear(6.25, 15);
    robot.open_claw_bottle();
    robot.fold_bottle_arm();

    //---------------------------------
    // moves back
    robot.move_linear(6.25, -10);
    robot.openClaw_Entree();
    robot.turn_around_left_wheel(-140);
    robot.move_linear(6.25, -45);
    robot.move_linear(6.25, 18);
    robot.turn_around_left_wheel(90);
    robot.move_linear_until_switch(0, 6.25);
    robot.move_linear(6.25, 2);

    // grabs taco
    robot.closeClaw_Entree();
    robot.move_linear(6.25, 20);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, -40);
    robot.turn_around_left_wheel(90);
    robot.move_linear(6.25, -13);
    robot.move_linear(6.25, 2);
    robot.openClaw_Entree();

    // // move to water bottles
    // robot.move_linear(6.25, 10);
    // robot.turn_around_left_wheel(90);
    // robot.move_linear(6.25, 20);
    // robot.turn_around_right_wheel(90);
    // robot.move_linear(6.25, 10);
    // robot.openClaw_Bottle();
    // robot.unfold_bottle_arm();
    // robot.closeClaw_Bottle();
    // robot.set_bottle_arm(1300);
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 10);
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 15);
    // robot.openClaw_Bottle();
    // robot.set_bottle_arm(800);
    // robot.move_linear(6.25, -15);
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 8);
    // robot.turn_around_left_wheel(92);
    // robot.unfold_bottle_arm();
    // robot.closeClaw_Bottle();
    // robot.set_bottle_arm(1300);
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 8);
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 15);
    // robot.openClaw_Bottle();
    // robot.set_bottle_arm(800);
    // robot.move_linear(6.25, -15);
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 5);
    // robot.turn_around_left_wheel(92);
    // robot.unfold_bottle_arm();
    // robot.closeClaw_Bottle();
    // robot.set_bottle_arm(1300);
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 5);
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 15);
    // robot.openClaw_Bottle();
    // robot.turn_around_left_wheel(92);
    // robot.move_linear(6.25, 25);

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