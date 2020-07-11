
/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer.h
 *
 * Description: Header file for the AVR TIMER1 driver
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/

#ifndef TIMER1_H_
#define TIMER1_H_
#include "std_types.h"
#include "common_macros.h"
#include "micro_config.h"

/*******************************************************************************
 *                         Types Declaration                                   *
 *******************************************************************************/
typedef enum
{
    NO_CLOCK,
    F_CPU_CLOCK,
    F_CPU_8,
    F_CPU_64,
    F_CPU_256,
    F_CPU_1024
} Timer_Clock;

typedef enum
{
    NORMAL_MODE,
    COMPARE_MODE
} Timer_mode;

typedef struct
{
    Timer_Clock clock;
    Timer_mode mode;
    uint8 channel;
    uint16 initial_value;
    uint16 compare_value;
} Timer_ConfigType;

/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
/*
/* Description : Function to initialize the ICU driver
/* 	1. Set the required clock.
/* 	2. Set the required mode.
/*  3. Set the required initial value.
/*  4. Set the required compare value.
/* 	5. Enable the Input Capture Interrupt.
/* 	6. Initialize Timer1 Registers
*/
void Timer1_init(const Timer_ConfigType *Config_Ptr);

/*
/* Description: Function to set the Call Back function address.
*/
void Timer1_setCallBack(void (*a_ptr)(void));

/*
/* Description: Function to disable the Timer1 to stop the ICU Driver
*/
void Timer1_DeInit(void);

#endif /* ICU_H_ */
