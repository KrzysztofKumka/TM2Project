
#include "frdm_bsp.h"
#include "pmusic.h"
#include "buttons.h"
#include "tpm_pcm.h"
#include "pit.h"
//#include "tsi.h"

int main (void) { 
	
	musicInit();  // initialize music array
	
	buttonsInit();  // initialize buttons
	
	TPM0_Init();  // initialize TPM0 interrupts
	
  PIT_Init();  // initialize PIT interrupts
	
  while(1) {

		__WFI();															/* sleep & wait for interrupt */
		
	}
}
