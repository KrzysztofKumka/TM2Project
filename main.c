
#include "MKL05Z4.h"                    	/* Device header */
#include "fsm.h"													/* Leds functions */
#include "buttons.h"											/* Buttons of external keyboard */
#include "tpm_pcm.h"											/* External speaker handling */


int main(void) {
	fsmInitialize(); /* Initialize LEDs */
	buttonsInitialize(); /* Initialize buttons */
	
	TPM0_Init_PCM();
		
	while(1){	
	 __wfi(); // Save energy and wait for interrupt
	}
}
