
#include "MKL05Z4.h"                    //Device header
#include "fsm.h"												//Declarations
#include "tpm_pcm.h"
#include "pmusic.h"

typedef enum{ RED = 8, GREEN = 9, BLUE = 10 } LedType; // Define LED position in Port B 
typedef enum{ ON = 1, OFF = 0 } LedStateType;

void ledCntrl (LedType led, LedStateType state) {
	if( state == ON)
		FPTB->PCOR |= (1 << led);
	if( state == OFF)
		FPTB->PSOR |= (1 << led);
}

void led_delay(){
volatile int delay;
	for(delay=0; delay<1200000; delay++);
}

void fsmInitialize() {
	
//Initialize registers for leds	
  SIM->SCGC5 |=  SIM_SCGC5_PORTB_MASK;      /* Enable Clock to Port B */ 
  PORTB->PCR[RED] = PORT_PCR_MUX(1);        /* Pin PTB8 is GPIO */
  PORTB->PCR[GREEN] = PORT_PCR_MUX(1);      /* Pin PTB9 is GPIO */
  PORTB->PCR[BLUE] = PORT_PCR_MUX(1);       /* Pin PTE10 is GPIO */
	FPTB->PDDR |= (1 << RED) | (1 << GREEN) | (1 << BLUE);          /* enable PTB{8, 9, 10} as Output */

// Welcome sequence 
	ledCntrl(RED, ON);
	led_delay();
	ledCntrl(RED, OFF);
	led_delay();
	ledCntrl(GREEN, ON);
	led_delay();
	ledCntrl(GREEN, OFF);
	led_delay();
	ledCntrl(BLUE, ON);
	led_delay();
	ledCntrl(BLUE, OFF);
	led_delay();
	
}
