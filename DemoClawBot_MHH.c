#pragma config(Sensor, dgtl1,  armLoweringLimit, sensorDigitalIn)
#pragma config(Sensor, dgtl2,  armRaisingLimit, sensorDigitalIn)
#pragma config(Motor,  port2,           leftMotor,     tmotorServoContinuousRotation, openLoop, reversed)
#pragma config(Motor,  port3,           rightMotor,    tmotorServoContinuousRotation, openLoop)
#pragma config(Motor,  port5,           clawMotor,     tmotorServoStandard, openLoop)
#pragma config(Motor,  port6,           armMotor,      tmotorServoContinuousRotation, openLoop)
//*!!Code automatically generated by 'ROBOTC' configuration wizard               !!*//

/*----------------------------------------------------------------------------------------------*\
|*                                - Clawbot DOUBLE Joystick Control -                           *|
|*                                      ROBOTC on VEX 2.0 Cortex                                *|
|*                                                                                              *|
|*  This program uses TWO joystickS, BOTH right AND left to drive the robot (TANK DRIVE).       *|
|*  Use notes below to reconfigure which joystick is used.                                      *|
|*  The joystick buttons are used to raise and lower the arm.                                   *|
|*  The joystick buttons are used to open and close the claw.                                   *|
|*                                                                                              *|
|*                                        ROBOT CONFIGURATION                                   *|
|*  NOTES:                                                                                      *|
|*      1)  Ch2 is the Y axis for the RIGHT joystick.                                           *|
|*      2)  Ch3 is the Y axis for the LEFT joystick.                                            *|
|*      3)  Button 5U and 5L are on the front left side of the joystick.                        *|
|*      4)  Button 6U and 6L are on the front right side of the joystick.                       *|
|*                                                                                              *|
|*    MOTORS & SENSORS:                                                                         *|
|*    [I/O Port]        [Name]          [Type]                               [Description]      *|
|*    Motor - Port 2   leftMotor     PWM Motor                             Left drive motor     *|
|*    Motor - Port 3   rightMotor    PWM Motor                             Right drive motor    *|
|*    Motor - Port 5   clawMotor     servo                                 Claw control         *|
|*    Motor - Port 6   armMotor      PWM Motor                             Arm motor            *|
\*----------------------------------------------------------------------------------------------*/

// joystick button functions
#define RAISE_ARM_BUTTON    vexRT[Btn5U]
#define LOWER_ARM_BUTTON    vexRT[Btn5D]
#define CLOSE_CLAW_BUTTON   vexRT[Btn6U]
#define OPEN_CLAW_BUTTON    vexRT[Btn6D]
// just having fun with these:
#define CW_BUTTON           vexRT[Btn8R]
#define TWIST_BUTTON        vexRT[Btn8D]    // in memory of Chubby Checkers
#define CCW_BUTTON          vexRT[Btn8L]
#define ARM_WAVY_BUTTON     vexRT[Btn8U]    // in memory of Wavy Gravy


//+++++++++++++++++++++++++++++++++++++++++++++| MAIN |+++++++++++++++++++++++++++++++++++++++++++
task main ()
{
    int   counter10ms = 0;                            // initialize the timer

    while(1 == 1)                                   // infinite loop
    {
        if (CW_BUTTON)
        {
            motor[leftMotor]  = 64;                 // darn the torpedoes, half speed ahead
            motor[rightMotor] = -64;                // half speed reverse
        }
        else if (CCW_BUTTON)
        {
            motor[leftMotor]  = -64;                // reverse
            motor[rightMotor] = 64;                 // forward
        }
        else if (TWIST_BUTTON)
        {
            if ((counter10ms && 0x00000020) == 0)   // bit 5 (decimal 32) changes every 320ms
            {
                motor[leftMotor]  = 64;             // clockwise
                motor[rightMotor] = -64;
            }
            else
            {
                motor[leftMotor]  = -64;            // counterclockwise
                motor[rightMotor] = 64;
            }
        }
        else if ( (ARM_WAVY_BUTTON)
                && (SensorValue[armLoweringLimit] == 0) // don't move if on limits
                && (SensorValue[armRaisingLimit] == 0) )
        {
            if ( (counter10ms && 0x00000020) == 0)  // bit 5 (decimal 32) changes every 320ms
          {
            motor[armMotor] = 64;                   // Arm goes up
          }
          else
          {
            motor[armMotor] = -64;                  // Arm goes down
          }
        }
        else                                        // default if no buttons pressed
        {
            // tank drive
            motor[leftMotor]  = vexRT[Ch3] / 2;     // half speed (third speed got stuck)
            motor[rightMotor] = vexRT[Ch2] / 2;     // "
        }

        // Raise, lower or do not move arm (at half max speed)
        if ( ( RAISE_ARM_BUTTON == 1) && (SensorValue[armRaisingLimit] == 0) )
        {
            motor[armMotor] = 64;                   //...raise the arm.
        }
        else if ( (LOWER_ARM_BUTTON == 1) && ( SensorValue[armLoweringLimit] == 0) )
        {
            motor[armMotor] = -64;                  //...lower the arm.
        }
        else                                        // Else (neither button is pressed)...
        {
            motor[armMotor] = 0;                    //...stop the arm.
        }

        // Open, close or do not more claw
        if (CLOSE_CLAW_BUTTON == 1)                 // If Button 6U is pressed...
        {
            motor[clawMotor] = 127;                 //...close the gripper.
        }
        else if (OPEN_CLAW_BUTTON == 1)             // Else, if button 6D is pressed...
        {
            motor[clawMotor] = -127;                //...open the gripper.
        }
        else                                        // Else (neither button is pressed)...
        {
            // the claw will stay at its previous position
        }


        //10ms between executions of the infinite loop
        wait1Msec(10);
        counter10ms += 1;                           // increment the counter of 10ms loops
    }
}
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
