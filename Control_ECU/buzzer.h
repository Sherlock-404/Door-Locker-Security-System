/******************************************************************************
 *
 * Module: BUZZER
 *
 * File Name: buzzer.h
 *
 * Description: Header file for the buzzer driver
 *
 * Engineer: Youssef Taha
 *
 *******************************************************************************/
#ifndef BUZZER_H_
#define BUZZER_H_
#include "micro_config.h"
#include "std_types.h"
#include "common_macros.h"
/*******************************************************************************
 *                      Preprocessor Macros                                    *
 *******************************************************************************/
#define BUZZER_CTRL_PORT PORTD
#define BUZZER_CTRL_PORT_DIR DDRD
#define BUZZER_PIN PD2
/*******************************************************************************
 *                      Functions Prototypes                                   *
 *******************************************************************************/
void Buzzer_init(void);
void Buzzer_on(void);
void Buzzer_off(void);
#endif