# Connect4DemoBots

These are small robots build with existing VEX 2.0 Cortex.   The software is written using RobotC.

## Functions are:
1) Drive
2) Pick up Wiffle Ball
3) Hold Wiffle Ball
4) Place Wiffle Ball

This robot also does some dance moves such as the twist and the wavy gravy.

This program uses TWO joystickS, BOTH right AND left to drive the robot (TANK DRIVE).  Use notes below to reconfigure which joystick is used.  The joystick buttons are used to raise and lower the arm. The joystick buttons are used to open and close the claw.

## Robot Configuration:
1)  Ch2 is the Y axis for the RIGHT joystick.
2)  Ch3 is the Y axis for the LEFT joystick.  
3)  Button 5U and 5L are on the front left side of the joystick.    
4)  Button 6U and 6L are on the front right side of the joystick.   

## Motors & Sensors:
| [I/O Port] |[Name] |[Type]| [Description] |
|------------|-------|------|---------------|
|Motor - Port 2  | leftMotor   |  PWM Motor   | Left drive motor  |
|Motor - Port 3  | rightMotor  |  PWM Motor   | Right drive motor |
|Motor - Port 5  | clawMotor   |  servo       | Claw control      |
|Motor - Port 6  | armMotor    |  PWM Motor   | Arm motor         |

