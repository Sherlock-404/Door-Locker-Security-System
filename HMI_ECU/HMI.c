/******************************************************************************
 *
 * File Name: HMI.c
 *
 * Description: source file for the interface ECU 
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/
#include "HMI.h"
static uint8 counter = 0;
static uint8 counter2 = 0;
/******************************************************************************/
/*
/* Description : Function to initialize password
/* 	1. get the password from user
/* 	2. confirm the password from user
/*  3. if they are not matched recall the function
/*  4. if the are matched send the password to the other ecu
*/
void initialize_password(void)
{
    LCD_clearScreen();
    uint8 password[password_size];
    uint8 confirm_password[password_size];
    LCD_displayString("Set Password:");
    LCD_goToRowColumn(1, 0);
    get_password(password);

    LCD_clearScreen();
    LCD_displayString("Confirm Password");
    LCD_goToRowColumn(1, 0);
    get_password(confirm_password);
    LCD_clearScreen();

    if (check_password(password, confirm_password) == FALSE)
    {
        LCD_displayString("Not matched");
        _delay_ms(1000);
        initialize_password();
    }
    else
    {
        LCD_displayString("Confirmed");
        _delay_ms(1000);
        LCD_clearScreen();
        UART_sendByte(new_password);
        send_password(password);
    }
}
/******************************************************************************/
/*
/* Description : Function to ecu idle mode
/* 	1. get key from the user through keypad
/* 	2. if it '-' then call the set password function
/*  3. if it '+' then call open_door function
*/
void idle_mode(void)
{
    LCD_clearScreen();
    LCD_displayString("+: Open gate");
    LCD_goToRowColumn(1, 0);
    LCD_displayString("-: Set password");
    while (KeyPad_getPressedKey() != '-' && KeyPad_getPressedKey() != '+')
    {
    }
    if (KeyPad_getPressedKey() == '+')
    {
        _delay_ms(400);
        open_door();
    }
    else if (KeyPad_getPressedKey() == '-')
    {
        _delay_ms(400);
        set_password();
    }
}
/******************************************************************************/
/*
/* Description : Function to open the gate door
/* 	1. get the password from user and send it to the other ecu to check it
/* 	2. if it true send 'open gate' to the other ecu to open the gate
/*  3. if it false increment the Attempts counter and recall open gate function
/*  4. if the user entered wrong password for 3 times send "theif" to the other ecu to open the alarm
*/
void open_door(void)
{
    uint8 Entered_password[password_size];
    counter++;
    if (counter == 4)
    {
        LCD_clearScreen();
        UART_sendByte(theif);
        LCD_displayString("Thief");
        while (UART_recieveByte() != safe)
        {
        }
        counter = 0;
        idle_mode();
    }
    LCD_clearScreen();
    LCD_displayString("Enter Password");
    LCD_goToRowColumn(1, 0);
    get_password(Entered_password);
    UART_sendByte(compare_passwords);
    send_password(Entered_password);
    UART_sendByte(ready);
    if (UART_recieveByte() == TRUE)
    {
        UART_sendByte(open_gate);
        LCD_clearScreen();
        LCD_displayString("Opening gate");
        while (UART_recieveByte() != gate_is_open)
        {
        }
        LCD_clearScreen();
        LCD_displayString("Closing gate");
        while (UART_recieveByte() != gate_is_closed)
        {
        }
        counter = 0;
        idle_mode();
    }

    else
    {
        LCD_clearScreen();
        LCD_displayString("Wrong Password");
        _delay_ms(500);
        open_door();
    }
}
/******************************************************************************/
/*
/* Description : Function to reset the password
/* 	1. get the password from user and send it to the other ecu to check it
/* 	2. if it true send call initialize password function 
/*  3. if it false increment the Attempts counter and recall open gate function
/*  4. if the user entered wrong password for 3 times send "theif" to the other ecu to open the alarm
*/
void set_password(void)
{

    uint8 Entered_password[password_size];
    uint8 new_entered_password[password_size];

    counter2++;
    if (counter2 == 4)
    {
        LCD_clearScreen();
        UART_sendByte(theif);
        LCD_displayString("Thief");
        while (UART_recieveByte() != safe)
        {
        }

        counter2 = 0;
        idle_mode();
    }

    LCD_clearScreen();
    LCD_displayString("Enter Password");
    LCD_goToRowColumn(1, 0);
    get_password(Entered_password);
    UART_sendByte(compare_passwords);
    send_password(Entered_password);

    UART_sendByte(ready);

    if (UART_recieveByte() == TRUE)
    {
        initialize_password();
        LCD_clearScreen();
        LCD_displayString("Done");
        _delay_ms(500);
        idle_mode();
    }

    else
    {
        LCD_clearScreen();
        LCD_displayString("Wrong Password");
        _delay_ms(500);
        set_password();
    }
}
/******************************************************************************/
/*
/* Description : Function to send the entered password to the other ecu
/* send every byte through uart to the other ecu
*/
void send_password(uint8 *password)
{
    while (UART_recieveByte() != ready)
    {
    }

    for (uint8 i = 0; i < password_size; i++)
    {
        UART_sendByte(password[i]);
        _delay_ms(20);
    }
}
/******************************************************************************/
/*
/* Description : Function to get the password from user
/* get the keypad pressed key and store it in global array
*/
void get_password(uint8 *password)
{

    for (uint8 i = 0; i < password_size; i++)
    {
        password[i] = KeyPad_getPressedKey();
        LCD_integerToString(password[i]);
        _delay_ms(400);
    }
}
/******************************************************************************/
/*
/* Description : Function to check the correctness of entered password
/* 	1. get the original password from eeprom 
/* 	2. compare between the entered password and the original password
/*  3. retrun 0 if false , 1 if true
*/
uint8 check_password(uint8 *password, uint8 *Entered_password)
{
    for (uint8 i = 0; i < password_size; i++)
    {
        if (password[i] != Entered_password[i])
        {
            return FALSE;
        }
    }
    return TRUE;
}
/******************************************************************************/
/*
/* Description : Function to initialize the mcu
/* 1.initialize the uart
/* 2.initialize the LCD
/* 3.wait untel the other ecu sends "ready" message
*/
void mcu_init(void)
{
    UART_init();
    LCD_init();

    while (UART_recieveByte() != ready)
    {
    }
}