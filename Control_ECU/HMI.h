/******************************************************************************

 *
 * File Name: HMI.h
 *
 * Description: Header file for the control ECU 
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/
#ifndef HMI_H_
#define HMI_H_

#include "std_types.h"
#include "micro_config.h"
#include "common_macros.h"
#include "i2c.h"
#include "external_eeprom.h"
#include "uart.h"
#include "timer.h"
#include "buzzer.h"
#include "motor.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define address 0x05
#define compare_passwords 10
#define open_gate 20
#define new_password 30
#define ready 40
#define theif 50
#define safe 60
#define gate_open 70
#define gate_closed 80
#define password_size 6
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void initialize_password(void);
uint8 check_password(void);
void get_password(void);
void authenticate_password(void);
void save_password(void);
void mcu_init(void);
void open(void);
void alarm_on(void);
void alarm_off(void);
void open_mechanism(void);
void idle_mode(void);
#endif