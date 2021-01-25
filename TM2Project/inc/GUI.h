/******************************************************************************
 * This file is a part of the Music Sequencer Project for SM2                 *
 ******************************************************************************/

/**
 * @file GUI.h
 * @author Kumka, Potoczek
 * @date Jan 2021
 * @brief File containing declarations for GUI
 * @ver 0.1
 */
 
#ifndef GUI_H
#define GUI_H

#include "lcd1602.h"
#include "pmusic.h"

/**
 * @brief Those functions are helpful in keeping code clean. They contain functions 
 * 				from lcd1602.c file in special order, so we don't have to multiply the code.
 */
 
void GUI_WelcomeSequence(void);

void GUI_Countdown(void);

void GUI_Menu(void);

void GUI_Start(void);

void GUI_Play(void);

void GUI_Pause(void);

void GUI_Reset(void);

void GUI_Config(void);

void GUI_SetArray(void);

void GUI_CHangeArraySize(void);

void GUI_setZeroes(uint8_t size);

void GUI_whichSample(uint8_t time, uint8_t prevTime);


/**
 * @brief Delay function.
 */
void delay_ms(int a);

#endif /* GUI_H */
