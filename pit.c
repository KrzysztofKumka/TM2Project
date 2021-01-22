
#include "pit.h"

void PIT_IRQHandler(void);

void PIT_Init(void) {

	SIM->SCGC6 |= SIM_SCGC6_PIT_MASK;  // Enable PIT mask in SCGC6 register
	
	PIT->MCR &= ~PIT_MCR_MDIS_MASK;  // Disable MDIS mask in MCR register
	PIT->MCR |= PIT_MCR_FRZ_MASK;  // Enable FRZ mask in MCR register
	 
	PIT->CHANNEL[0].LDVAL = PIT_LDVAL_TSV(40000*50);  // count down from
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TIE_MASK;  // Generate interrupts

  NVIC_SetPriority(PIT_IRQn, 2); // 0, 1, 2 or 3 - PIT interrupt priority level

	NVIC_ClearPendingIRQ(PIT_IRQn); 
	NVIC_EnableIRQ(PIT_IRQn);	 //Enable Interrupts
	
	PIT->CHANNEL[0].TCTRL |= PIT_TCTRL_TEN_MASK;  //Enable counter
}

void PIT_IRQHandler(void) {
	int buttonNum = 0;
	if (PIT->CHANNEL[0].TFLG & PIT_TFLG_TIF_MASK) {
		buttonNum = getButtonNumber();
		
		switch (buttonNum) {
			case 1:
				musicAddSample(kick1, 0);
				break;
			case 2:
				break;
			case 3:
				break;
			case 4:
				break;
			case 5:
				break;
			case 6:
				break;
			case 7:
				break;
			case 8:
				break;
			case 9:
				break;
			case 10:
				break;
			case 11:
				break;
			case 12:
				break;
			case 13:
				break;
			case 14:
				break;
			case 15:
				break;
			case 16:
				break;
		}
		PIT->CHANNEL[0].TFLG |= PIT_TFLG_TIF_MASK; //clear status flag
	}
}
