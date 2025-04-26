#include <kipr/kipr.h>
#include <iostream>

const int ARM_PORT = 3;
const int CLAW_PORT = 1;
const int RAISED_POSITION = 1100; //FIX THE NUMBER
const int FULLY_RAISED = 1700; 
const int HALF_LOWERED = 487;
const int LOWERED_POSITION = 150; //FIX THE NUMBER
const int CLOSED_POSITION = 800; //FIX THE NUMBER
const int OPEN_POSITION = 2047; //FIX THE NUMBER
const int LEFT_MOTOR_PIN = 3;
const int RIGHT_MOTOR_PIN = 0;
const double PI = 3.141592654;


const double LEFT_TICKS_PER_INCH = 200.7;
const double RIGHT_TICKS_PER_INCH = LEFT_TICKS_PER_INCH*1.214;

const double LEFT_TICKS_PER_INCH_BACKWARDS = 237.5;
const double RIGHT_TICKS_PER_INCH_BACKWARDS = LEFT_TICKS_PER_INCH_BACKWARDS*1.216;


const double ARM_DOWN_LEFT_TICKS_PER_INCH = LEFT_TICKS_PER_INCH;
const double ARM_DOWN_RIGHT_TICKS_PER_INCH = RIGHT_TICKS_PER_INCH;

const double ARM_DOWN_LEFT_TICKS_PER_INCH_BACKWARDS = LEFT_TICKS_PER_INCH_BACKWARDS;
const double ARM_DOWN_RIGHT_TICKS_PER_INCH_BACKWARDS = RIGHT_TICKS_PER_INCH_BACKWARDS;

//const double TURN_AROUND_LEFT_WHEEL_ARM_RAISED_OFFSET = -140;
//const double TURN_AROUND_LEFT_WHEEL_ARM_LOWERED_OFFSET = -70;

//const double TURN_AROUND_RIGHT_WHEEL_ARM_RAISED_OFFSET = -130;
//const double TURN_AROUND_RIGHT_WHEEL_ARM_LOWERED_OFFSET = -140;

const double TURN_AROUND_LEFT_WHEEL_ARM_RAISED_OFFSET = 0;
const double TURN_AROUND_LEFT_WHEEL_ARM_LOWERED_OFFSET = 0;

const double TURN_AROUND_RIGHT_WHEEL_ARM_RAISED_OFFSET = 0;
const double TURN_AROUND_RIGHT_WHEEL_ARM_LOWERED_OFFSET = 0;

void raise_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos<RAISED_POSITION; servoPos+=2){
        set_servo_position(ARM_PORT, servoPos);
        msleep(1);
    }
}

void half_lower_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos>HALF_LOWERED; servoPos-=2)
    {
        set_servo_position(ARM_PORT, servoPos);
        msleep(1);
    }
}

void lower_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos>LOWERED_POSITION; servoPos-=2){
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
    
    // Depending on whether or not the arm is raised, use different ticks per inch values
    if (get_servo_position(ARM_PORT) < 400) 
    {
        // Arm is lowered
        if(distance_inch<0){
            move_at_velocity(LEFT_MOTOR_PIN, mult*speed_inch_per_sec*ARM_DOWN_LEFT_TICKS_PER_INCH_BACKWARDS);
        	move_at_velocity(RIGHT_MOTOR_PIN, mult*speed_inch_per_sec*ARM_DOWN_RIGHT_TICKS_PER_INCH_BACKWARDS);
        }
		else{
        	move_at_velocity(LEFT_MOTOR_PIN, mult*speed_inch_per_sec*ARM_DOWN_LEFT_TICKS_PER_INCH);
        	move_at_velocity(RIGHT_MOTOR_PIN, mult*speed_inch_per_sec*ARM_DOWN_RIGHT_TICKS_PER_INCH);
        }
    }
    else
    {
        // Arm is raised
        if(distance_inch<0){
        	move_at_velocity(LEFT_MOTOR_PIN, mult*speed_inch_per_sec*LEFT_TICKS_PER_INCH_BACKWARDS);
            move_at_velocity(RIGHT_MOTOR_PIN, mult*speed_inch_per_sec*RIGHT_TICKS_PER_INCH_BACKWARDS);
        }
        else{
        	move_at_velocity(LEFT_MOTOR_PIN, mult*speed_inch_per_sec*LEFT_TICKS_PER_INCH);
            move_at_velocity(RIGHT_MOTOR_PIN, mult*speed_inch_per_sec*RIGHT_TICKS_PER_INCH);
        }
    }
    
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
    
    if (get_servo_position(ARM_PORT) < 400) 
    {
        // Arm is lowered
       	msleep(abs(distance/5.35*1000)+TURN_AROUND_LEFT_WHEEL_ARM_LOWERED_OFFSET+wait_offset_ms);
    }
    else
    {
        // Arm is raised
       	msleep(abs(distance/5.35*1000)+TURN_AROUND_LEFT_WHEEL_ARM_RAISED_OFFSET+wait_offset_ms);
    }
    
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
    
    if (get_servo_position(ARM_PORT) < 400) 
    {
        // Arm is lowered
       	msleep(abs(distance/5.28*1000)+TURN_AROUND_RIGHT_WHEEL_ARM_LOWERED_OFFSET+wait_offset_ms);
    }
    else
    {
        // Arm is raised
       	msleep(abs(distance/5.28*1000)+TURN_AROUND_RIGHT_WHEEL_ARM_RAISED_OFFSET+wait_offset_ms);
    }
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

    wait_for_light(0);
    shut_down_in(119);

	enable_servos();
 	disable_servo(0);
    
    //Calibration
	//move_linear(6,30,0);
    //move_linear(6, -30, 0);
    //turn_around_left_wheel(90, 0);
    
    ////wait_for_button()();
    // Slide 3
    p("Slide 3");
    raise_arm();
    turn_around_left_wheel(90, 0);
    
    // Slide 4
    ////wait_for_button()();
    p("Slide 4");
    move_linear(6, -16, 0);

   	// Slide 5
    ////wait_for_button()();
    p("Slide 5");
    turn_around_left_wheel(-90, 0);
    

    // Slide 6
    ////wait_for_button()();
    p("Slide 6");
    move_linear(6, -11.5, 0);    
    
    
    p("Unit 2");
    
    
    
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

    ////wait_for_button()();
    // Slide 9
    p("Slide 9");
    move_linear(6, 21.5, 0);

    ////wait_for_button()();
    // Slide 10
    p("Slide 10");
    close_claw();
    raise_arm();
    
    ////wait_for_button()();
    // Slide 11
    p("Slide 11");
    move_linear(6, 7, 0);
    
    ////wait_for_button()();
    // Slide 12
    p("Slide 12");
    turn_around_right_wheel(90, 0);
    
    
    // Slide 13
	p("Slide 13");
    move_linear(6, 4.5, 0);
    
    // Slide 14
    p("Slide 14");
    half_lower_arm();
    open_claw();
    
      //Slide 17
    p("Slide 17");
    raise_arm();
    close_claw();

    
    
    p("Unit 3");
    //wait_for_button()();
    
    
    






    // UNIT 3 
    //Slide 18
    p("Slide 18");
    move_linear(6, -3);
    //wait_for_button()();

    //Slide 19
    p("Slide 19");
    turn_around_right_wheel(-90);
    move_linear(6,-3);
    //wait_for_button()();
    //Slide 20
    p("Slide 20");
    move_linear(6, 2.5); 
    //wait_for_button()();

    //Slide 21
    p("Slide 21");
    open_claw();
    lower_arm();
    //wait_for_button()();
    
    //Slide 22
    p("Slide 22");
    turn_around_right_wheel(-30);
    //wait_for_button()();
    
    //Slide 23
    p("Slide 23");
    move_linear(6, 2.3);
//wait_for_button()();
    //Slide 24
    p("Slide 24");
    turn_around_right_wheel(-15);
    //move_linear(6, X); //FIX THE NUMBER
    
    move_linear(6, 2);
//wait_for_button()();
    //Slide 25
    p("Slide 25");
    close_claw();
    raise_arm();
//wait_for_button()();
    
    //Slide 26
    p("Slide 26. Turning towards the tray to drop off the vertical set of poms");
    turn_around_right_wheel(45);
    move_linear(6,3.5);
    turn_around_right_wheel(90, 100);
    
    
    //wait_for_button()();
    //Slide 27
    p("Slide 27");
    move_linear(6, 9); // DROPPING THE VERTICAL SET OF POMS
    move_linear(6, -2);
    //wait_for_button()();

    //Slide 28
    p("Slide 28");
    half_lower_arm();
    open_claw();

    
    
    // GETTING THE PICKLES

    
    
    move_linear(6, -8.5);
    raise_arm();
    
    close_claw();
    
    p("We are turning to get to the pickles"); 
   turn_around_left_wheel(-90, 0);
    
    move_linear(6, 9);
    
    turn_around_right_wheel(-90, 0);
    
    // BACK UP AND RAM INTO THE WALL
    move_linear(6, -3);
    
    move_linear(6, 13);
    
    move_linear(6, -1.75);
    
    
    for(int servoPos = get_servo_position(ARM_PORT); servoPos>450; servoPos-=3){
        set_servo_position(ARM_PORT, servoPos);
        msleep(1);
    }
    msleep(1000);
    set_servo_position(CLAW_PORT, 1300);
    msleep(1000);
    lower_arm();
    msleep(500);
    close_claw();
    raise_arm();
    
    
    // DROP OFF THE PICKLE
    
    // Move forward a bit so that we can align
    move_linear(6, 3);
    turn_around_right_wheel(-90);
    msleep(7000);
    
   
    move_linear(6, 7.5);
    
    turn_around_left_wheel(-90);

    // Move forward towards the trays
    move_linear(6, 11);
    move_linear(6, -2);
    
    // Drop the pickle
    half_lower_arm();
    open_claw();

    move_linear(6, 2.1);

    // Wait for the other robot.
    msleep(13000);


    /* GET THE THIRD POM SET */

    raise_arm();

    close_claw();

    // Back up away from the trays
    move_linear(6, -5.5);

    

    // Turn towards the third pom set.
    turn_around_right_wheel(-90);

    // Move towards the third pom set.
    move_linear(6, 11);
    
    open_claw();
    lower_arm();
    
    move_linear(6, 4);
    move_linear(6, -2);

    // Grab the poms.
    open_claw();
    close_claw();
    raise_arm();




    /* PUT THE LAST POM SET IN THE THIRD TRAY. */

    // Back up. This is moving left.
    move_linear(6, -8);
    
    // Turn towards the trays, then move towards them.
    turn_around_right_wheel(90);
    move_linear(6, 8.5);
    move_linear(6, -3.5);

    // Drop the poms.
    half_lower_arm();
    open_claw();


    
    return 0;
  
    
unit5:
    // UNIT 5: GETTING THE PICKLE
    
    p("Slide 37. Move claw to 1300. This makes the claw as small as possible so it doesn't bump into anything but also wide enough to not hit the pickle.");
    set_servo_position(CLAW_PORT, 1300);
    msleep(1000);
   
    
    p("Slide 32. Turn around right wheel -90 degrees");
    turn_around_right_wheel(90, 0);
    //wait_for_button();
    
    p("Slide 33. Back up 6 inches. This is uh towards the right side.");
   	move_linear(5, -9);
    //wait_for_button();
    
    p("Slide 34. Turn around right wheel -90 degrees so that we are facing the pickle");
   	turn_around_right_wheel(90, 0);
    //wait_for_button();
    
    p("Slide 35. Move forward until bump into wall. Then back up.");
   	move_linear(5, 4);
    move_linear(5, -2);
    //wait_for_button();
    
    p("Slide 38. Lower arm");
    lower_arm();
    set_servo_position(ARM_PORT, 0);
    msleep(500);
    
    p("Slide 39. Close claw. Raise arm. Back out.");
    close_claw();
    raise_arm();
    move_linear(5, -5);
    
    p("Slide 40. Turn around -90 degrees around the right wheel");
    turn_around_right_wheel(-90, 0);
    
    p("Slide 41. Move forward 4.5 inches.");
    move_linear(5, 4.5);
    
    p("Slide 42. Turn around left wheel -90 degrees.");
    turn_around_left_wheel(-90, 0);
    
    p("Slide 43. Move forward so that the pickle is over the trays");
    move_linear(5, 3);
    
    p("Slide 44. Drop the pickle.");
    half_lower_arm();
    open_claw();
    
    // TOMATO
    
    p("Back up towards the tomato so that we are aligned.");
    move_linear(6, -12);
    
    
    return 0;
    
    

    // BLOCK OF CODE THAT GRABS AND THEN PLACES THE PICKEL
    
  //wait_for_button();
    raise_arm();
     //wait_for_button();
    close_claw();
      // wait_for_button();
    
    move_linear(6, -8);
       //wait_for_button();
    turn_around_left_wheel(90, 0);
      wait_for_button();
    move_linear(6, -2.5);
       //wait_for_button();
    turn_around_right_wheel(90, 0);
       //wait_for_button();
    set_servo_position(ARM_PORT, 400);
    msleep(1000);
       //wait_for_button();
	move_linear(6, 3);
       //wait_for_button();
    move_linear(6, -2);
       //wait_for_button();
    set_servo_position(CLAW_PORT, 600);
    msleep(1000);
       //wait_for_button();
    lower_arm();
       //wait_for_button();
    close_claw();
    
    p("RAISING ARM");
    raise_arm();
    p("OOK");
    
   
	turn_around_right_wheel(-90, 0);
    move_linear(6, 7.5);
    turn_around_left_wheel(-90, 0);
    move_linear(6, 7.5);
    half_lower_arm();
    open_claw();
    
    // dropped pickle
    p("dropped pickle");
    
    
    // BLOCK OF CODE THAT GETS THE TOMATO
    
    //wait_for_button();
    raise_arm();
     //wait_for_button();
    close_claw();
      // wait_for_button();
    
    move_linear(6, -8);
       //wait_for_button();
    turn_around_left_wheel(90, 0);
      // wait_for_button();
    move_linear(6, -2.5);
       //wait_for_button();
    turn_around_right_wheel(90, 0);
       //wait_for_button();
    set_servo_position(ARM_PORT, 400);
    msleep(1000);
       //wait_for_button();
	move_linear(6, 3);
       //wait_for_button();
    move_linear(6, -4);
       //wait_for_button();
    set_servo_position(CLAW_PORT, 600);
    msleep(1000);
       //wait_for_button();
    lower_arm();
       //wait_for_button();
    close_claw();
    
    p("RAISING ARM");
    raise_arm();
    p("OOK");
   
	turn_around_right_wheel(-90, 0);
    move_linear(6, 7.5);
    turn_around_left_wheel(-90, 0);
    move_linear(6, 7.5);
    half_lower_arm();
    open_claw();
    
    
    return 0;
    
    
    p("unit 5");
    // UNIT 5
    
    close_claw();
    raise_arm();
    move_linear(6, -11.3);
    
    turn_around_right_wheel(95,0);
    
    move_linear(6, 26.5);
    turn_around_left_wheel(-180, 0);
    
    //wait_for_button()();
    turn_around_right_wheel(5, 0);
    open_claw();
    lower_arm();
    
    move_linear(6, 5);
    
    /*
    
   	// UNIT 3 
    
    //wait_for_button()();
    // Slide 16
    p("Slide 16");
    raise_arm();
    
    //wait_for_button()();
    //Slide 17
    p("Slide 17");
    move_linear(6, -6.5);
	
    //wait_for_button()();
    //Slide 18
    p("Slide 18");
    turn_around_right_wheel(-90, 0);
	    
    //wait_for_button()();
    //Slide 19
    p("Slide 19");
    move_linear(6, -3);
    
    //wait_for_button()();
    // Slide 20
    p("Slide 20");
    lower_arm();
    close_claw();
    
    //wait_for_button()();
    // Slide 21
    p("Slide 21");
    raise_arm();
    
    //wait_for_button()();
    // Slide 22
    p("Slide 22");
    move_linear(6, 13.75, 0);
    
    //wait_for_button()();
    // Slide 23
    p("Slide 23");
    turn_around_right_wheel(-90, 0);
    
    
    
    return 0;
    
    //wait_for_button()();
    // Slide 20
    p("Slide 20");
    lower_arm();
    
    //wait_for_button()();
    // Slide 21
    p("Slide 21");
    
    return 0;
    
    /*
    
    //Slide 20
    p("Slide 20");
    move_linear(6, X); //FIX THE NUMBER

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
    move_linear(6, X); //FIX THE NUMBER

    //Slide 25
    p("Slide 25");
    turn_around_left_wheel(90, 0);

    //Slide 26
    p("Slide 26");
    move_linear(6, X); //FIX THE NUMBER
    lower_arm();
    
    //Slide 27
    p("Slide 27");
    open_claw();
   
*/
    
}