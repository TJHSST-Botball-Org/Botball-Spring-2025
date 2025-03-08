#include <kipr/kipr.h>
#include <iostream>

const int ARM_PORT = 3;
const int CLAW_PORT = 1;
const int RAISED_POSITION = 0; //FIX THE NUMBER
const int LOWERED_POSITION = 1800; //FIX THE NUMBER
const int CLOSED_POSITION = 135; //FIX THE NUMBER
const int OPEN_POSITION = 1170; //FIX THE NUMBER
const int LEFT_MOTOR_PIN = 3;
const int RIGHT_MOTOR_PIN = 0;
const double PI = 3.141592654;

const double LEFT_TICKS_PER_INCH = 208;
const double RIGHT_TICKS_PER_INCH = 241;

void raise_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos>RAISED_POSITION; servoPos--){
        set_servo_position(ARM_PORT, servoPos);
        msleep(1);
    }
}

void lower_arm()
{
    for(int servoPos = get_servo_position(ARM_PORT); servoPos<LOWERED_POSITION; servoPos++){
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
    while (!get_digital_value(4))
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
    move_at_velocity(LEFT_MOTOR_PIN, mult*5*LEFT_TICKS_PER_INCH);
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

int main()
{
    enable_servos();
    raise_arm();
    close_claw();
    
    // Slide 3
    p("Slide 3");
    raise_arm();
    turn_around_left_wheel(90, 70);
    
    // Slide 4
    p("Slide 4");
    move_linear(5, -6.4);
    
    
   	// Slide 5
    p("Slide 5");
    turn_around_right_wheel(-90, 200);
    
    
    // Slide 6
    p("Slide 6");
    move_linear(5, -7.75);
    lower_arm();
    
    open_claw();
    move_linear(5, 14);
    close_claw();
    raise_arm();
    disable_servos();
    return 0;
}

/*
                           --------------------                           
                      ------------------------------                      
                   ------------------------------------                   
                 -------===========================-----=                 
               --==========------------------=============-               
             ========-------------::----------------=========             
            =====----------------:=+:-------------------======            
          ====-------------------+##*-----------------------====          
         -==--------------------=#%%#*:------------------------=          
        -=---------------:-----+#%%%%#+:-----------:-------------         
       =----------::----:*=---+*%%%%%%%+----*------:--------------        
       -----------::---:**---+*%%%%%%%%%+---**-----::-------------        
      -----------:::--:***---*#%%%%%%%%%#=--#%*----:::------------        
      ------:---::=:-:*%**--**%%%%%%%%%%%#--#%%*----:::------------       
     -------:--::++::=%%**-=%*%%%%%%%%%%%%*-#%%%=--*=::------------       
     -------:-::+*+:-%%%#*-#%#%%%%%%%%%%%%%=#%%%%==%#+:------------       
     -------:-:+**+:=:=+*+=-#%%%%%%%%%%%%%#:=***=:-%%#+:-----------       
    ::-----:::-***-=%#-::::*#%%%%%%%%%%%%%%%+:-::-#=-%#=-----------:      
    ::------::-**-##*:-----:%%%%%%%%%%%%%%@+:-----:+#-##=-----------      
    ::------:-=*-*%#:--:::---%%%%%%%%%%%%%%:--:::--:##:%#-----------      
    ::--------=*-%@+:-::::--:%%%%%%%%%%%%%#:-::::--:+@=#%-:---------      
    ::--------=+-@@=--::::--:%%%%%%%%%%%%%#:-::::--:=@=*%=:---------      
    ::--------++-@@+:-=-::---%%%%%%%%%%%%%%:-=-::--:*@-#%+:---------      
    ::--------+*=%@%-@@@*-=-=%%%%%%%%%%%%%%:%@%:---:%%+%%+:---------      
    :::-------+**#%@#+#+---:%%%%%%%%%%%%%%%#:+=---:%@%%%%+:---------      
    :::-------+**#%%%%=::-+%%%%%%%%%%%%%%%%%#-::-*%%%%%%%+:---------      
    :::-------+**#%%%%####%%%%%%%%%%%%%%%%%%%%###%%%%%%%%+:---------      
    :::-------+**#%%%%%%%%%%%%%%%%%*%%%%%%%%%%%%%%%%%%%%%-:---------      
    :::-------=***%%%%%%%%%%%%%%%%*%%%%%%%%%%%%%%%%%%%%%#::---------      
    :::--------***%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%=:::--------      
    :::-------:+**#%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%#::::--------      
    :::-------:-***#%%%%%%%%%%%#-+++++++-#%%%%%%%%%%%%%-::::--------      
    :::-------:::+***%%%%%%%%%%%=*******=%%%%%%%%%%%%#-:::::--------      
    :::-------:::::=***%%%%%%%%%*#*#####*%%%%%%%%%%%=:::::::--------      
    :::-------::::::::+**#%%%%%%%#**##*#%%%%%%%%%+::::::::::--------      
    ::::------:::::::::::=*#%%%%%%%%%%%%%%%%%#=:::::::::::::--------      
    ::::-------:::::::::::::-+*%%%%%%%%%%%#*+:::::::::::::::--------      
    ::::-------::::::::::::::****+**********+:::::::::::::::-----:--      
    ::::-------::::::::::::=****************+%+::::::::::::------:--      
    ::::-------:::::::::::*******************%@=:::::::::::-----::--      
    :::::------:::::::::=##*+***************#*%@%+-:.::::::-----::--      
    :::::------:::: :=*####****************%%#@@@@@@+-:::::-----::--      
    ::::::-----::-=***#####**************#%%%#@@@@@@@@@*-::-----::--      
    ::::::-----=*##########*+***********%%%%%#@@@@@@@@@@-::----:::--      
     ::::::----=############+++**+******%#*##%@@@@@@@@@@-::----:::--      
     ::::::----=############*************#%%*@@@@@@@@@@%:::---::::-       
     :::::::----#############+********#%%%%%%@@@@@@@@@@+:::--:::=:-       
     -:#*::::---+############+******#%%%%%%*@@@@@@@@@@%-::--:::#:-%#      
   +*%--@*::::--=#############====********+%@@@@@@@@@@%:::--::%==@@@%+    
  #@*+*:#@*::::--*#####%%@@@%#+==+*********@@@@@@@@@@@=:::-:-%#*@@@%+++   
  +*#@*+-@@#:::::=##%@@@@@@@@@%==+*******+@@@@@@@@@@@%:::::-%@@@%*+*%#=   
 ++****%*-+%%=:::-%@@@@@@@@@@@@#=********%@@@@@@@@@@@+::::=%@@#++##****=  
 +*******%#++##-::-@@@@@@@@@@@@%=*******+@@@@@@@@@@@#:::-#@#++*#*******+  
 +********+#%*+++::=+++*@@@@@@@@#*******%@@@@@@+++*%-:-*#++##***********+ 
=*+***********%%#%#-=%*#@@@@@@@@@*******@@@@@@%+###:-=++##*************+*=
=**+*****************%+#@@@@@@@@@#*****@@@@@@@%+%*+**%****************+**+
*/