
#ifndef buttons_h
#define buttons_h


#include "fsm.h"
#include "pmusic.h"

void buttonsInitialize(void);
void buttonsService(void);							//buttons' interrupt service procedure

void delay_ms(int n);

void buttonsInit(void);
int buttonsGet(void);
int getButtonNumber(void);

#endif
