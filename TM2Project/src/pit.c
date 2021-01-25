/******************************************************************************
 * This file is a part of the Music Sequencer Project for SM2                 *
 ******************************************************************************/

/**
 * @file pit.c
 * @author Kumka, Potoczek
 * @date Jan 2020
 * @brief File containing definitions for PIT
 * @ver 0.1
 */
 
#include "pit.h"

/******************************************************************************\
* Private memory declarations
\******************************************************************************/
static uint8_t menu = 1;
static uint8_t game = 0;
static uint8_t pause = 0;
static uint8_t config = 0;
static uint8_t setArr = 0;

/******************************************************************************\
* Private prototypes
\******************************************************************************/
void PIT_IRQHandler(void);


void PIT_Init(void) {

	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;  // Enable PIT mask in SCGC6 register
	
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;  // Disable MDIS mask in MCR register
	PIT->MCR |= PIT_MCR_FRZ_MASK;  // Enable FRZ mask in MCR register
	 
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(200000);  // every 100 ms
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;  // Generate interrupts

  NVIC_SetPriority(PIT_IRQn, 1); // 0, 1, 2 or 3 - PIT interrupt priority level

	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);	 //Enable Interrupts
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;  //Enable counter
}


void PIT_IRQHandler(void) {
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		
		uint8_t button = (uint8_t)getButtonNumber();  // check which button is clicked
		
		if (menu == 1) {  // menu handling
			if (button == 1) {  // if button 1 clicked go to game
				menu = 0;
				game = 1;
				GUI_Play();
				TPM0_PCM_Play();
			}
			else if (button == 2) {  // if button 2 clicked go to config
				menu = 0;
				config = 1;
				GUI_Config();
			}
		}
		else if (game == 1) {  // game handling
			if (button == 1) {  // if button 1 clicked go to pause
				game = 0;
				pause = 1;
				TPM0_PCM_Pause();
				GUI_Pause();
			}
			else if (button != 0){  // if other button clicked play music
				uint8_t time = getMusicTime();
				musicAddSample(time, button);
			}
		}
		else if (pause == 1) {  // pause handling
			if (button == 1) {  // if button 1 clicked go to play
				pause = 0;
				game = 1;
				GUI_Play();
				TPM0_PCM_Play();
			}
			else if (button == 2) {  // if button 2 clicked go to menu
				pause = 0;
				menu = 1;
				GUI_Menu();
			}
			else if (button == 3) {  // if button 3 clicked reset music array
				GUI_Reset();
				musicReset();
				GUI_Pause();
			}
		}
		else if (config == 1) {  // configuration handling
			if (button == 1) {  // if button 1 clicked set music array size
				config = 0;
				setArr = 1;
				GUI_SetArray();
			}
			else if (button == 2) {  // if button 2 clicked go to menu
				config = 0;
				menu = 1;
				GUI_Menu();
			}
		}
		else if (setArr == 1) {  // setting music array size handling
			if (button == 1) {  // if button 1 clicked go to config
				setArr = 0;
				config = 1;
				GUI_Config();
			}
			else if (button == 2) {  // if button 2 clicked increment music array size
				uint8_t newSize = getSize();
				if(newSize < 32) {
					setSize(newSize + 1);
					GUI_CHangeArraySize();
				}
			}
			else if (button == 3) {  // if button 3 clicked decrement music array size
				uint8_t newSize = getSize();
				if(newSize > 1) {
					setSize(newSize - 1);
					GUI_CHangeArraySize();
				}
			}
		}
		
		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; //clear status flag
	}
}
