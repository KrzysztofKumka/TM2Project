
#include "GUI.h"

void GUI_WelcomeSequence(void) {
	LCD1602_ClearAll();
	LCD1602_SetCursor(0, 0);
	LCD1602_Print("MUSIC SEQUENCER");
	LCD1602_SetCursor(0, 1);
	LCD1602_Print("KUMKA & POTOCZEK");	
	delay_ms(3000);
}

void GUI_Countdown(void) {
	LCD1602_SetCursor(10, 0);
	LCD1602_Print("3...");
	delay_ms(1000);
	LCD1602_SetCursor(10, 0);
	LCD1602_Print("2...");
	delay_ms(1000);
	LCD1602_SetCursor(10, 0);
	LCD1602_Print("1..");
	delay_ms(1000);
	GUI_setZeroes(getSize());
}

void GUI_Menu(void) {
	LCD1602_ClearAll();
	LCD1602_SetCursor(0, 0);
	LCD1602_Print("*Menu*");
	LCD1602_SetCursor(0, 1);
	LCD1602_Print("S1-Play   S2-Cfg");
}

void GUI_Play(void) {
	LCD1602_ClearAll();
	LCD1602_SetCursor(0, 0);
	LCD1602_Print("*Start in     *");
	LCD1602_SetCursor(0, 1);
	LCD1602_Print("S1-Pause");
	GUI_Countdown();
}

void GUI_Pause(void) {
	LCD1602_ClearAll();
	LCD1602_SetCursor(0, 0);
	LCD1602_Print("*Pause*  S2-Menu");
	LCD1602_SetCursor(0, 1);
	LCD1602_Print("S1-Play S3-Reset");
}

void GUI_Reset(void) {
	LCD1602_ClearAll();
	LCD1602_SetCursor(0, 0);
	LCD1602_Print("*Resetting*");
	delay_ms(1500);
}

void GUI_Config(void) {
	LCD1602_ClearAll();
	LCD1602_SetCursor(0, 0);
	LCD1602_Print("*Config*");
	LCD1602_SetCursor(0, 1);
	LCD1602_Print("S1-SetArr S2-Bck");
}

void GUI_SetArray(void) {
	LCD1602_ClearAll();
	LCD1602_SetCursor(0, 0);
	LCD1602_Print("Array size: ");
	LCD1602_SetCursor(12, 0);
	LCD1602_PrintNum(getSize());
	LCD1602_SetCursor(0, 1);
	LCD1602_Print("S1-Bck   S2^ S3v");
}

void GUI_CHangeArraySize(void) {
	LCD1602_SetCursor(12, 0);
	LCD1602_PrintNum(getSize());
}

void GUI_setZeroes(uint8_t size) {
	volatile uint8_t i;
	volatile uint8_t j;
	volatile uint8_t if2rows = 0;
	
	LCD1602_ClearAll();
	
	if (size <= 16) {
		for (i = 0; i < size; i++) {
			LCD1602_SetCursor(i,0);
			LCD1602_Print("O");
		}
	}
	else if (size <= 32) {
		if2rows = size - 16;
		for (i = 0; i < 16; i++) {
			LCD1602_SetCursor(i,0);
			LCD1602_Print("O");
		}
			
		for (j = 0; j < if2rows; j++) {
			LCD1602_SetCursor(j,1);
			LCD1602_Print("O");
		}
	}
}

void GUI_whichSample(uint8_t time, uint8_t prevTime) {
	
	if (time == 0) {
		if (prevTime <= 15) {
			LCD1602_SetCursor(prevTime,0);
			LCD1602_Print("O");
			LCD1602_SetCursor(time,0);
			LCD1602_Print("+");
		}
		else if (prevTime <= 31) {
			LCD1602_SetCursor(prevTime - 16, 1);
			LCD1602_Print("O");
			LCD1602_SetCursor(time,0);
			LCD1602_Print("+");
		}
	}
	else if (time < 16) {
		LCD1602_SetCursor(prevTime,0);
		LCD1602_Print("O");
		LCD1602_SetCursor(time,0);
		LCD1602_Print("+");
	}
	else if (time == 16) {
		LCD1602_SetCursor(prevTime, 0);
		LCD1602_Print("O");
		LCD1602_SetCursor(time-16, 1);
		LCD1602_Print("+");
	}
	else if (time > 16) {
		LCD1602_SetCursor(prevTime - 16,1);
		LCD1602_Print("O");
		LCD1602_SetCursor(time - 16,1);
		LCD1602_Print("+");
	}
}

void delay_ms(int a) {
	volatile int i;
	volatile int j;
	for (i = 0; i < a; i++) {
		for (j = 0; j < 3500; j++) {}
	}
}
