/******************************************************************************

 *
 * File Name: HMI.h
 *
 * Description: Header file for the interface ECU 
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/
#ifndef HMI_H_
#define HIMI_H_
#include "std_types.h"
#include "micro_config.h"
#include "keypad.h"
#include "lcd.h"
#include "uart.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define compare_passwords 10
#define open_gate 20
#define new_password 30
#define ready 40
#define theif 50
#define safe 60
#define gate_is_open 70
#define gate_is_closed 80
#define password_size 6
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void initialize_password(void);
void idle_mode(void);
uint8 check_password(uint8 *, uint8 *);
void set_password(void);
void send_password(uint8 *);
void mcu_init(void);
#endif