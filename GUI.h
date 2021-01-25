
#ifndef GUI_H
#define GUI_H

#include "lcd1602.h"
#include "pmusic.h"

void GUI_WelcomeSequence(void);

void GUI_Countdown(void);

void GUI_Menu(void);

void GUI_Start(void);

void GUI_Play(void);

void GUI_Pause(void);

void GUI_Config(void);

void GUI_SetArray(void);

void GUI_CHangeArraySize(void);

void GUI_setZeroes(uint8_t size);

void GUI_whichSample(uint8_t time, uint8_t prevTime);

void delay_ms(int a);

#endif /* GUI_H */
