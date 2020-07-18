/******************************************************************************
 *
 * File Name: HMI.c
 *
 * Description: source file for the control ECU 
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/
#include "HMI.h"
static uint8 g_tick = 0;
Timer_ConfigType timer_config = {
    F_CPU_1024,
    COMPARE_MODE,
    'A',
    0,
    54688,
};
static uint8 Entered_password[password_size];
/******************************************************************************/
/*
/* Description : Function to check the correctness of entered password
/* 	1. get the original password from eeprom 
/* 	2. compare between the entered password and the original password
/*  3. retrun 0 if false , 1 if true
*/
uint8 check_password(void)
{
    uint8 password[password_size];
    for (int i = 0; i < password_size; i++)
    {
        EEPROM_readByte(address + i, &password[i]);
        _delay_ms(10);
        if (password[i] != Entered_password[i])
        {

            return (0);
        }
    }

    return (1);
}
/******************************************************************************/
/*
/* Description : Function to get passwords from the other ecu
/* 	 store the incoming bytes in global array
*/
void get_password(void)
{
    UART_sendByte(ready);
    for (int i = 0; i < password_size; i++)
    {
        Entered_password[i] = UART_recieveByte();
    }
}
/******************************************************************************/
/*
/* Description : Function to authenticate the password for the other ecu
/* 	call check_password function if it returns 1 then send TRUE to the other ecu
/*  if it returns 0 then send FALSE to the other ecu 
*/
void authenticate_password(void)
{
    if (check_password())
    {
        while (UART_recieveByte() != ready)
        {
        }
        UART_sendByte(TRUE);
    }
    else
    {
        while (UART_recieveByte() != ready)
        {
        }
        UART_sendByte(FALSE);
    }
}
/******************************************************************************/
/*
/* Description : Function to save the password in eeprom
/* get the byte and store it in eepron on continuous addresses
*/
void save_password(void)
{
    UART_sendByte(ready);
    for (int i = 0; i < password_size; i++)
    {
        EEPROM_writeByte((address + i), UART_recieveByte());
        _delay_ms(10);
    }
}
/******************************************************************************/
/*
/* Description : Function to initialize the mcu
/* 1.initialize the uart
/* 2.initialize the eeprom
/* 3.send ready to the other ecu
*/
void mcu_init(void)
{
    UART_init();
    _delay_ms(10);
    EEPROM_init();
    UART_sendByte(ready);
}
/******************************************************************************/
/*
/* Description : Function to start the alarm
/* 1.set the I bit
/* 2.initialize the buzzer 
/* 3.set the buzzer on 
/* 4.set the call back function that will disable the buzzer after 15 secs
/* 5.initialize the timer
*/
void alarm_on(void)
{
    SET_BIT(SREG, 7);
    Timer1_setCallBack(alarm_off);
    Buzzer_init();
    Buzzer_on();
    Timer1_init(&timer_config);
}
/******************************************************************************/
/*
/* Description : call back Function to stop the buzzer after 15 secs
/* 1.increment counter  
/* 2.if the counter reaches 2 turn off the buzzer 
/* 3.send "safe" message to the other ecu  
/* 4.disable the timer
*/
void alarm_off(void)
{
    g_tick++;
    if (g_tick == 2)
    {
        Buzzer_off();
        g_tick = 0;
        UART_sendByte(safe);
        Timer1_DeInit();
    }
}
/******************************************************************************/
/*
/* Description : Function to open the gate 
/* 1.set the I bit
/* 2.start the motor clock wise 
/* 3.set the call back function that will reverse the motor after 15 secs
/* 4.initialize the timer
*/
void open(void)
{
    g_tick = 0;
    SET_BIT(SREG, 7);
    Timer1_setCallBack(open_mechanism);
    MOTOR_init();
    MOTOR_clockwise();
    Timer1_init(&timer_config);
}
/******************************************************************************/
/*
/* Description : call back Function to reverse the motor after 15 secs and stop it after 30 secs
/* 1.increment counter  
/* 2.if the counter reaches 2 reverse the motor
/* 3.send gate_open message to the other ecu 
/* 4.if counter reaches 4 stop the motor  
/* 5.disable the timer
*/
void open_mechanism(void)
{
    g_tick++;
    if (g_tick == 2)
    {
        UART_sendByte(gate_open);
        MOTOR_AntiClockwise();
    }
    if (g_tick == 4)
    {
        MOTOR_stop();
        UART_sendByte(gate_closed);
        g_tick = 0;
        Timer1_DeInit();
    }
}
/******************************************************************************/
void idle_mode(void)
{
    switch (UART_recieveByte())
    {
    case new_password:
        save_password();
        break;
    case compare_passwords:
        get_password();
        authenticate_password();
        break;
    case open_gate:
        open();
        break;
    case theif:
        alarm_on();
        break;
    }
}