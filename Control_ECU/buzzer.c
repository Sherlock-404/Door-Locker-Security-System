/******************************************************************************

 *
 * File Name: buzzer.c
 *
 * Description: source file for the Buzzer 
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/
#include "buzzer.h"
/*
/* Description : Function to initialize the buzzer driver
/* 	1. Set the buzzer pin as output pin
/* 	2. clear the buzzer pin to stop the buzzer
*/
void Buzzer_init(void)
{
    SET_BIT(BUZZER_CTRL_PORT_DIR, BUZZER_PIN);
    CLEAR_BIT(BUZZER_CTRL_PORT, BUZZER_PIN);
}
/*
/* Description : Function to start the buzzer 
/*  Set the buzzer pin to start
*/
void Buzzer_on(void)
{
    SET_BIT(BUZZER_CTRL_PORT, BUZZER_PIN);
}
/*
/* Description : Function to stop the buzzer 
/*  clear the buzzer pin to stop
*/
void Buzzer_off(void)
{
    CLEAR_BIT(BUZZER_CTRL_PORT, BUZZER_PIN);
}