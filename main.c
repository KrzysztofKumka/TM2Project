
#include "frdm_bsp.h"
#include "pmusic.h"
#include "buttons.h"
#include "tpm_pcm.h"
#include "pit.h"
#include "lcd1602.h"
//#include "tsi.h"

/* 
Connections

Matrix Keypad:
C4 -> PTA9
C3 -> PTA10
C2 -> PTA11
C1 -> PTA12
R1 -> PTA8
R2 -> PTA7
R3 -> PTA6
R4 -> PTA5

Speaker:
GND -> GND
+5V -> 3.3V
AUDIO_IN -> PTB7

LCD Display:
GND -> GND
VCC -> 5V
SDA -> PTB4
SCL -> PTB3
*/

int main (void) { 
	
	musicInit();  // initialize music array
	
	buttonsInit();  // initialize buttons
	
	LCD1602_Init();  // initialize lcd display
	LCD1602_Backlight(TRUE);  // turn on display backlight
	LCD1602_WelcomeSequence();  // display welcome sequence and countdown to start
	LCD1602_setZeroes();  // set "O" for each of 32 character slots
	
	TPM0_Init();  // initialize TPM0 interrupts
	
  PIT_Init();  // initialize PIT interrupts
	
  while(1) {

		__WFI();															/* sleep & wait for interrupt */
		
	}
}
