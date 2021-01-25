/******************************************************************************
 * This file is a part of the Music Sequencer Project for SM2                 *
 ******************************************************************************/

/**
 * @file buttons.c
 * @author Kumka, Potoczek
 * @date Jan 2021
 * @brief File containing definitions for buttons
 * @ver 0.1
 */
 
#include "MKL05Z4.h"  // Device header
#include "buttons.h" 

/******************************************************************************\
* Private definitions
\******************************************************************************/
#define COL 4
#define ROW 4

/******************************************************************************\
* Private memory declarations
\******************************************************************************/
static int prevVal = 0;
static int val;
static int ifAddSample = 0;


void buttonsInit(void) {  //initialization
	
	// enable clock for port A
	SIM->SCGC5 |=  SIM_SCGC5_PORTA_MASK;
	
	// initializing columns
	PORTA->PCR[12] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // set MUX to GPIO and enable pull-up resitor on Pin 12
	PORTA->PCR[11] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // set MUX to GPIO and enable pull-up resitor on Pin 11
	PORTA->PCR[10] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // set MUX to GPIO and enable pull-up resitor on Pin 10
	PORTA->PCR[9] |= PORT_PCR_MUX(1) | PORT_PCR_PE_MASK | PORT_PCR_PS_MASK; // set MUX to GPIO and enable pull-up resitor on Pin 9
	
	// initializing rows
	PORTA->PCR[8] |= PORT_PCR_MUX(1); // set MUX to GPIO on Pin 8
	PTA->PSOR |= MASK(8); // set Pin 8 to off
	PTA->PDDR |= MASK(8);  // set Pin 8 as output
	PORTA->PCR[7] |= PORT_PCR_MUX(1); // set MUX to GPIO on Pin 7
	PTA->PSOR |= MASK(7); // set Pin 7 to off
	PTA->PDDR |= MASK(7);  // set Pin 7 as output
	PORTA->PCR[6] |= PORT_PCR_MUX(1); // set MUX to GPIO on Pin 6
	PTA->PSOR |= MASK(6); // set Pin 6 to off
	PTA->PDDR |= MASK(6);  // set Pin 6 as output
	PORTA->PCR[5] |= PORT_PCR_MUX(1); // set MUX to GPIO on Pin 5
	PTA->PSOR |= MASK(5); // set Pin 5 to off
	PTA->PDDR |= MASK(5);  // set Pin 5 as output
}


int buttonsGet(void) {  // get single sample of clicked button
	
	int whichbut[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};  // array for checking which button was activated
	int count = 0;  // variable for counting buttons that are checked
	volatile int k;
	volatile int m;
	volatile int n;
	int ifOnlyOneBut = 0;
	int tmp = 0;
	for (k = 0; k < ROW; k++) {  // iterating on rows
		PTA->PCOR |= MASK(8 - k);  // activating Pin(8-k)
		for (m = 0; m < COL; m++) {  // iterating on columns
			whichbut[15 - count] = (int)(PTA->PDIR & (1<<(12-m)));  // if 1 then write it to array
			count++;
		}
		PTA->PSOR |= MASK(8 - k); // set Pin(8 - k) to off
	}
	for (n = 0; n < 16; n++) {
		if(whichbut[n] == 0) {  // if button(n) == 0
			ifOnlyOneBut += 1;  // clicked buttons counter increment
			tmp = n + 1;  // temporary result
		}
	}
	if(ifOnlyOneBut != 1) {  // if more than 1 button clicked
		return 0;  // return 0
	}
	else {
		return tmp;  // return temporary result
	}
}


void ifButtonClicked(void) {
	if(ifAddSample != 1) {  // if flag not set, check which button is clicked
		int but = buttonsGet();
		if(val == but && val != prevVal ) {  // checking if our value did not changed and if it is different than previous value
			prevVal = val;
			ifAddSample = 1;  // set the flag
		}
		else val = but;
	}
}


int getButtonNumber(void) {
	ifButtonClicked();  // if button clicked, set the flag
	if(ifAddSample) {  // if flag set, clear the flac and return value
		ifAddSample = 0;
		return val;
	}
	return 0;
}
