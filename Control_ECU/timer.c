/******************************************************************************
 *
 * Module: TIMER1
 *
 * File Name: timer.c
 *
 * Description: Source file for the AVR TIMER1 driver
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/

#include "timer.h"

/*******************************************************************************
 *                           Global Variables                                  *
 *******************************************************************************/

/* Global variables to hold the address of the call back function in the application */
static volatile void (*g_callBackPtr)(void) = NULL;

/*******************************************************************************
 *                       Interrupt Service Routines                            *
 *******************************************************************************/

ISR(TIMER1_OVF_vect)
{
    (*g_callBackPtr)();
}

ISR(TIMER1_COMPA_vect)
{
    (*g_callBackPtr)();
}

ISR(TIMER1_COMPB_vect)
{

    (*g_callBackPtr)();
}

/*******************************************************************************
 *                      Functions Definitions                                  *
 *******************************************************************************/
void Timer1_init(const Timer_ConfigType *Config_Ptr)
{
    if (Config_Ptr->mode == NORMAL_MODE)
    {
        SET_BIT(TCCR1A, FOC1A);
        SET_BIT(TCCR1A, FOC1B);
        TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock & 0x7);
        TCNT1 = Config_Ptr->initial_value;
        SET_BIT(TIMSK, TOIE1);
    }
    else if (Config_Ptr->mode == COMPARE_MODE)
    {
        if (Config_Ptr->channel == 'A' || Config_Ptr->channel == 'a')
        {
            SET_BIT(TCCR1A, FOC1A);
            SET_BIT(TCCR1A, FOC1B);
            SET_BIT(TCCR1B, WGM12);
            TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock & 0x7);
            TCNT1 = Config_Ptr->initial_value;
            OCR1A = Config_Ptr->compare_value;
            SET_BIT(TIMSK, OCIE1A);
        }
        else if (Config_Ptr->channel == 'B' || Config_Ptr->channel == 'b')
        {
            SET_BIT(TCCR1A, FOC1A);
            SET_BIT(TCCR1A, FOC1B);
            SET_BIT(TCCR1B, WGM12);
            TCCR1B = (TCCR1B & 0xF8) | (Config_Ptr->clock & 0x7);
            TCNT1 = Config_Ptr->initial_value;
            OCR1B = Config_Ptr->compare_value;
            SET_BIT(TIMSK, OCIE1B);
        }
    }
}

/*
/* Description: Function to set the Call Back function address.
*/
void Timer1_setCallBack(void (*a_ptr)(void))
{
    /* Save the address of the Call back function in a global variable */
    g_callBackPtr = a_ptr;
}

/*
/* Description: Function to disable the Timer1 to stop the Timer1 Driver
*/
void Timer1_DeInit(void)
{
    /* Clear All Timer1 Registers */
    TCCR1A = 0;
    TCCR1B = 0;
    OCR1A = 0;
    CLEAR_BIT(TIMSK, OCIE1A);

    /* Disable the TIMER1 interrupt */
    CLEAR_BIT(TIMSK, OCIE1B);
}
