#include <iostream>
#include <Robot.h>

int main()
{
    Robot robot;
    // initializing robot

    //robot moves to the entree
    robot.openClaw_Entree();
    robot.move(10000, 1000); //um need to find dist and speed

    //grabs entrees 
    robot.closeClaw_Entree();

    // second move to the water bottles
    robot.rotate(180.0, 100); //needs to turn 180 degrees
    while(!robot.rightSensor() && !robot.leftSensor())
    {
        robot.move(1,100);
    }
    //pause robot momentarily (?)
    robot.rotate(67.0, 100);

    while(!robot.rightSensor() && !robot.leftSensor())
    {
        robot.move(1,100);
    }

    robot.move(10000,-100); //moving backwards x amount
    robot.rotate(90.0, 1000);

    //grab first two bottles
    robot.openClaw_Bottle();
    robot.move_bottle_arm(int pos, int duration);
    robot.closeClaw_Bottle();
    robot.move_bottle_arm(int pos, int duratiom);
    
    // u turn
    robot.rotate(180., 10000);
    
    //put water bottles into food station
    robot.move_bottle_arm(int pos, int duration);
    robot.openClaw_Bottle();
    
    //move to the 1st tray
    robot.rotate(double angle, int speed); 
    robot.move(int dist, int speed);
    robot.rotate(double angle, int speed);
    
    //drop off entree in first tray CLOSEST TO BEV STATION
    robot.openClaw_Entree();

    //ROUND 2 begins
    //move back to entree zone
    robot.rotate(double angle, int speed);
    robot.move(int dist, int speed);
    robot.rotate(double angle, int speed);
    robot.move(int dist, int speed);

    //grabs entrees 
    robot.closeClaw_Entree();

    // second move to the water bottles
    robot.move(); //move backwards
    robot.rotate(180, 100);
    robot.move(10000, 1000);
    robot.rotate(67, 100);

    //grab 2nd bottle
    robot.openClaw_Bottle();
    robot.move_bottle_arm(int pos, int duration);
    robot.closeClaw_Bottle();
    robot.move_bottle_arm(int pos, int duratiom);
    
    // u turn
    robot.rotate(180, 10000);
    
    //put water bottles into food station
    robot.move_bottle_arm(int pos, int duration);
    robot.openClaw_Bottle();
    
    //move to the 1st tray
    robot.rotate(double angle, int speed); 
    robot.move(int dist, int speed);
    robot.rotate(double angle, int speed);
    
    //drop off entree in first tray CLOSEST TO BEV STATION
    robot.openClaw_Entree();

    //round 3

    //move back to entree zone
    robot.rotate(double angle, int speed);
    robot.move(int dist, int speed);
    robot.rotate(double angle, int speed);
    robot.move(int dist, int speed);
    
    //grabs entrees 
    robot.closeClaw_Entree();
    
    // second move to the water bottles
    robot.move(); //move backwards
    robot.rotate(180, 100);
    robot.move(10000, 1000);
    robot.rotate(67, 100);
    
    //grab 2nd bottle
    robot.openClaw_Bottle();
    robot.move_bottle_arm(int pos, int duration);
    robot.closeClaw_Bottle();
    robot.move_bottle_arm(int pos, int duratiom);
        
    // u turn
    robot.rotate(180, 10000);
        
    //put water bottles into food station
    robot.move_bottle_arm(int pos, int duration);
    robot.openClaw_Bottle();
        
    //move to the 1st tray
    robot.rotate(double angle, int speed); 
    robot.move(int dist, int speed);
    robot.rotate(double angle, int speed);
        
    //drop off entree in first tray CLOSEST TO BEV STATION
    robot.openClaw_Entree();

    return 0;
}
