/******************************************************************************
 *
 * Module: MOTOR
 *
 * File Name: motor.h
 *
 * Description: Header file for the MOTOR driver
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/
#ifndef MOTOR_H_
#define MOTOR_H_
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define MOTOR_CTRL_PORT PORTA
#define MOTOR_CTRL_PORT_DIR DDRA
#define MOTOR_PIN1 PA0
#define MOTOR_PIN2 PA1
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void MOTOR_init(void);
void MOTOR_clockwise(void);
void MOTOR_AntiClockwise(void);
void MOTOR_stop(void);
#endif
