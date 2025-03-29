#include <kipr/kipr.h>
#include <iostream>

const int ARM_PORT = 3;
const int CLAW_PORT = 1;
const int RAISED_POSITION = 1220; //FIX THE NUMBER
const int FULLY_RAISED = 1800; 
const int HALF_LOWERED = 487;
const int LOWERED_POSITION = 120; //FIX THE NUMBER
const int CLOSED_POSITION = 280; //FIX THE NUMBER
const int OPEN_POSITION = 1931; //FIX THE NUMBER
const int LEFT_MOTOR_PIN = 3;
const int RIGHT_MOTOR_PIN = 0;
const double PI = 3.141592654;

const double LEFT_TICKS_PER_INCH = 200;
const double RIGHT_TICKS_PER_INCH = 230;

void raise_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos<RAISED_POSITION; servoPos++){
        set_servo_position(ARM_PORT, servoPos);
        msleep(1);
    }
}

void half_lower_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos>HALF_LOWERED; servoPos--)
    {
        set_servo_position(ARM_PORT, servoPos);
        msleep(1);
    }
}

void lower_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos>LOWERED_POSITION; servoPos--){
        set_servo_position(ARM_PORT, servoPos);
        msleep(1);
    }
}

void close_claw()
{
    set_servo_position(CLAW_PORT, CLOSED_POSITION);
    msleep(1000);
}

void open_claw()
{
    set_servo_position(CLAW_PORT, OPEN_POSITION);
    msleep(1000);
}

void p(std::string output)
{
    std::cout << output << std::endl;
}

void wait_for_button()
{
    std::cout << "Waiting for button." << std::endl;
    while (analog(5)>1000)
    {
        msleep(1);
    }
}

void stop()
{
    move_at_velocity(LEFT_MOTOR_PIN, 0);
    move_at_velocity(RIGHT_MOTOR_PIN, 0);
    msleep(100);
}

void move_linear(double speed_inch_per_sec, double distance_inch, int wait_offset_ms=0)
{
    /* 
    	Moves distance_inch at speed_inch_per_sec. Waits an extra wait_offset_ms milliseconds 
        Try to always move at 5 inches per second
        Backwards is negative distance values. Keep speed positive.
    */

    double mult = distance_inch/abs(distance_inch);    
    move_at_velocity(LEFT_MOTOR_PIN, mult*speed_inch_per_sec*LEFT_TICKS_PER_INCH);
    move_at_velocity(RIGHT_MOTOR_PIN, mult*speed_inch_per_sec*RIGHT_TICKS_PER_INCH);
    msleep(abs(distance_inch/speed_inch_per_sec*1000)+wait_offset_ms);
    stop();
}

void turn_around_left_wheel(double degrees, int wait_offset_ms=0)
{
    /* 
        Rotates 90 degrees at a constant speed.
        
        If degrees is positive then clockwise, negative is CCW 
    */
    degrees *= -1;
    double distance = 2*PI*6.5*(degrees/360);
    double mult = distance/abs(distance);
    move_at_velocity(RIGHT_MOTOR_PIN, mult*5*RIGHT_TICKS_PER_INCH);
    msleep(abs(distance/5*1000)+wait_offset_ms);
    stop();
}

void turn_around_right_wheel(double degrees, int wait_offset_ms=0)
{
    /* 
        Rotates 90 degrees at a constant speed.
        
        If degrees is positive then clockwise, negative is CCW 
    */
    double distance = 2*PI*6.5*(degrees/360);
    double mult = distance/abs(distance);
    move_at_velocity(LEFT_MOTOR_PIN, 5*mult*LEFT_TICKS_PER_INCH);
    msleep(abs(distance/5*1000)+wait_offset_ms);
    stop();
}


void rotate_continuous(double speed, int direction)
{
    /* Direction  1 is clockwise, or to the right 
       Direction -1 is counter-clockwise, or to the left */
    move_at_velocity(LEFT_MOTOR_PIN, direction*speed*LEFT_TICKS_PER_INCH);
    move_at_velocity(RIGHT_MOTOR_PIN, -direction*speed*RIGHT_TICKS_PER_INCH);
}

void fully_raise_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos<FULLY_RAISED; servoPos++){
        set_servo_position(ARM_PORT, servoPos);
        msleep(1);
    }
}

int main()
{
    // turn_around_right_wheel(90, 0);
   // move_linear(5,50,0);
    //return 0;
    enable_servos();    
	
    
    
    //wait_for_button();
    // Slide 3
    p("Slide 3");
    raise_arm();
    turn_around_left_wheel(90, 75);
    

    // Slide 4
    //wait_for_button();
    p("Slide 4");
    move_linear(5, -17, 150);
    

   	// Slide 5
    //wait_for_button();
    p("Slide 5");
    turn_around_left_wheel(-90, 75);
    

    // Slide 6
    //wait_for_button();
    p("Slide 6");
    move_linear(5, -14, 0);    
    
    /*
    bb    bb bbb    bb bb bbbbbbbb     bbbbbb  
    bb    bb bbbb   bb bb    bb             bb 
    bb    bb bb bb  bb bb    bb         bbbbb  
    bb    bb bb  bb bb bb    bb        bb      
     bbbbbb  bb   bbbb bb    bb        bbbbbbb 
                                           
    */

    
    
   // Slide 8
    p("Slide 8");
    open_claw();
    lower_arm();

    //wait_for_button();
    // Slide 9
    p("Slide 9");
    move_linear(5, 24, 0);

    //wait_for_button();
    // Slide 10
    p("Slide 10");
    close_claw();
    raise_arm();
    
    //wait_for_button();
    // Slide 11
    p("Slide 11");
    move_linear(5, 9, 0);
    
    //wait_for_button();
    // Slide 12
    p("Slide 12");
    turn_around_right_wheel(90, 60);
    
    
    // Slide 13
	p("Slide 13");
    move_linear(5, 5, 0);
    
    // Slide 14
    p("Slide 14");
    half_lower_arm();
    open_claw();
    
      //Slide 17
    p("Slide 17");
    raise_arm();
    close_claw();

    
    
    
    
    
    //Slide 18
    p("Slide 18");
    move_linear(5, -6);

    //Slide 19
    p("Slide 19");
    turn_around_right_wheel(-90);
    move_linear(5,-3);
    
    //Slide 20
    p("Slide 20");
    move_linear(5, 3.4); // old comment: FIX THIS NUMBER
    

    //Slide 21
    p("Slide 21");
    open_claw();
    lower_arm();
    
    //Slide 22
    p("Slide 22");
    turn_around_right_wheel(-30);
    
    //Slide 23
    p("Slide 23");
    move_linear(5, 3.3);

    //Slide 24
    p("Slide 24");
    turn_around_right_wheel(-30);
    //move_linear(5, X); //FIX THE NUMBER
    
    move_linear(5, -1.5);

    //Slide 25
    p("Slide 25");
    close_claw();
    raise_arm();

    //Slide 26
    p("Slide 26");
    turn_around_right_wheel(60);
    move_linear(5,3);
    turn_around_right_wheel(90, -50);
    
    //Slide 27
    p("Slide 27");
    move_linear(5, 5);

    //Slide 28
    p("Slide 28");
    half_lower_arm();
    open_claw();
    
    
    
    
    
    /*
    
   	// UNIT 3 
    
    wait_for_button();
    // Slide 16
    p("Slide 16");
    raise_arm();
    
    wait_for_button();
    //Slide 17
    p("Slide 17");
    move_linear(5, -6.5);
	
    wait_for_button();
    //Slide 18
    p("Slide 18");
    turn_around_right_wheel(-90, 100);
	    
    wait_for_button();
    //Slide 19
    p("Slide 19");
    move_linear(5, -3);
    
    wait_for_button();
    // Slide 20
    p("Slide 20");
    lower_arm();
    close_claw();
    
    wait_for_button();
    // Slide 21
    p("Slide 21");
    raise_arm();
    
    wait_for_button();
    // Slide 22
    p("Slide 22");
    move_linear(5, 13.75, 0);
    
    wait_for_button();
    // Slide 23
    p("Slide 23");
    turn_around_right_wheel(-90, 0);
    
    
    
    return 0;
    
    wait_for_button();
    // Slide 20
    p("Slide 20");
    lower_arm();
    
    wait_for_button();
    // Slide 21
    p("Slide 21");
    
    return 0;
    
    /*
    
    //Slide 20
    p("Slide 20");
    move_linear(5, X); //FIX THE NUMBER

    //Slide 21
    p("Slide 21");
    turn_around_left_wheel(90, 0);
    
    //Slide 22
    p("Slide 22");
    close_claw();
    
    //Slide 23
    p("Slide 23");
    turn_around_left_wheel(-90, 0);

    //Slide 24
    p("Slide 24");
    move_linear(5, X); //FIX THE NUMBER

    //Slide 25
    p("Slide 25");
    turn_around_left_wheel(90, 0);

    //Slide 26
    p("Slide 26");
    move_linear(5, X); //FIX THE NUMBER
    lower_arm();
    
    //Slide 27
    p("Slide 27");
    open_claw();
    
*/
    
}
