
#include "tpm_pcm.h"
#include "pmusic.h"

// 3
#define UPSAMPLING 10  

void TPM0_IRQHandler(void);

static uint8_t tpm0Enabled = 0;
static uint16_t upSampleCNT = 0;

static uint16_t sampleCNT = 0;
static uint8_t  playFlag = 1;

void TPM0_Init_PCM(void) {
		
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;		
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);    // CLK ~ 41,9MHz (CLOCK_SETUP=0)

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 
	PORTB->PCR[7] = PORT_PCR_MUX(2);			// PCM output -> PTB7, TPM0 channel 2
	
	TPM0->SC |= TPM_SC_PS(2);  					  // 41,9MHz / 4 ~ 10,48MHz
	TPM0->SC |= TPM_SC_CMOD(1);					  // internal input clock source

	TPM0->MOD = 255; 										  // 8bit PCM - docelowo 765??
																				// 10,48MHz / 765 ~ 13.699 kHz
	
// "Edge-aligned PWM true pulses" mode -> PCM output
	TPM0->SC &= ~TPM_SC_CPWMS_MASK; 		
	TPM0->CONTROLS[2].CnSC |= (TPM_CnSC_MSB_MASK | TPM_CnSC_ELSB_MASK); 
	TPM0->CONTROLS[2].CnV = 0; 
	
	
// "Output compare" -> for intterrupt
	TPM0->SC &= ~TPM_SC_CPWMS_MASK;
	TPM0->CONTROLS[0].CnSC |= (TPM_CnSC_MSA_MASK | TPM_CnSC_ELSA_MASK);
	TPM0->CONTROLS[0].CnV = 0;
  
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHIE_MASK; // Enable interrupt
	
	NVIC_SetPriority(TPM0_IRQn, 1);  /* TPM0 interrupt priority level  */

	NVIC_ClearPendingIRQ(TPM0_IRQn); 
	NVIC_EnableIRQ(TPM0_IRQn);	/* Enable Interrupts */
	
	tpm0Enabled = 1;  /* set local flag */
}

void TPM0_PCM_Play(void) {
	sampleCNT = 0;   /* start from the beginning */
	playFlag = 1;
}

void TPM0_IRQHandler(void) {
	
	if (playFlag) {
		if (upSampleCNT == 0) {
			sampleCNT++;
			TPM0->CONTROLS[2].CnV = getMusic(0, sampleCNT);
		}
		if (sampleCNT > 500) {
			sampleCNT = 0;
			TPM0->CONTROLS[2].CnV = 0;
		}
		
		// 13.699 / 3 ~ 4,566kHz ~ WAVE_RATE
		if (++upSampleCNT > (UPSAMPLING-1)) upSampleCNT = 0;
	}
	
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 
}
