#include "motor.h"
/*
/* Description : Function to initialize the Motor
/* 1.set the first pin to output pin  
/* 2.set the second pin to output pin
/* 3.clear the first pin to stop the motor
/* 4.clear the second pin to stop the motor
*/
void MOTOR_init(void)
{
    SET_BIT(MOTOR_CTRL_PORT_DIR, MOTOR_PIN1);
    SET_BIT(MOTOR_CTRL_PORT_DIR, MOTOR_PIN2);
    CLEAR_BIT(MOTOR_CTRL_PORT, MOTOR_PIN1);
    CLEAR_BIT(MOTOR_CTRL_PORT, MOTOR_PIN2);
}
/*
/* Description : Function to start the Motor clockwise
/* 1.clear the first pin 
/* 2.set the second pin 
*/
void MOTOR_clockwise(void)
{
    CLEAR_BIT(MOTOR_CTRL_PORT, MOTOR_PIN1);
    SET_BIT(MOTOR_CTRL_PORT, MOTOR_PIN2);
}
/*
/* Description : Function to start the Motor anti clockwise
/* 1.set the first pin 
/* 2.clear the second pin 
*/
void MOTOR_AntiClockwise(void)
{
    SET_BIT(MOTOR_CTRL_PORT, MOTOR_PIN1);
    CLEAR_BIT(MOTOR_CTRL_PORT, MOTOR_PIN2);
}
/*
/* Description : Function to stop the Motor
/* 1.clear the first pin to stop the motor
/* 2.clear the second pin to stop the motor
*/
void MOTOR_stop(void)
{
    CLEAR_BIT(MOTOR_CTRL_PORT, MOTOR_PIN1);
    CLEAR_BIT(MOTOR_CTRL_PORT, MOTOR_PIN2);
}