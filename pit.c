#include "pit.h"

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
		//ifButtonClicked();
		uint8_t time = getMusicTime();
		uint8_t button = (uint8_t)getButtonNumber();
		
		if(button != 0) {
			musicAddSample(time, button);
		}
		
		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; //clear status flag
	}
}
