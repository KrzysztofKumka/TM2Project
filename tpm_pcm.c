
#include "tpm_pcm.h"

// 3
#define UPSAMPLING 10  

void TPM0_IRQHandler(void);

static uint8_t tpm0Enabled = 0;
static uint16_t upSampleCNT = 0;

static uint16_t sampleCNT = 0;
static uint8_t  playFlag = 1;

static int play_samples[] = 
 {1, 0, 0, 0, 
	4, 0, 0, 15, 
	1, 0, 0, 0, 
	4, 0, 0, 15,
	1, 0, 0, 0, 
	4, 0, 0, 0, 
	1, 0, 0, 0, 
	4, 0, 3, 0};

//static int mt[] = {1, 0, 2, 0, 3, 0, 2, 0, 1, 0, 2, 2, 3, 0, 0, 5,
//									 1, 0, 4, 0, 3, 0, 4, 0, 1, 0, 6, 2, 2, 0, 0, 5};

volatile int i = 0;

void TPM0_Init_PCM(void) {
		
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;		
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);    // CLK ~ 41,9MHz (CLOCK_SETUP=0)

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 
	PORTB->PCR[7] = PORT_PCR_MUX(2);			// PCM output -> PTB7, TPM0 channel 2
	
	TPM0->SC |= TPM_SC_PS(2);  					  // 41,9MHz / 4 ~ 10,48MHz
	TPM0->SC |= TPM_SC_CMOD(1);					  // internal input clock source

	TPM0->MOD = 255; //+ TSI_ReadSlider(); 											// TSI_ReadSlider(); 		 8bit PCM
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
			//SILENCE SAMPLE
			if(play_samples[i] == 0) {}//{TPM0->CONTROLS[2].CnV = silence[sampleCNT];}
			
			//KICK SAMPLES 1, 2, 3
			if(play_samples[i] == 1) {TPM0->CONTROLS[2].CnV = kick1[sampleCNT];}
			if(play_samples[i] == 2) {TPM0->CONTROLS[2].CnV = kick2[sampleCNT];}
			if(play_samples[i] == 3) {TPM0->CONTROLS[2].CnV = kick3[sampleCNT];}
			
			//CLAP SAMPLES 4, 5, 6, 7
			if(play_samples[i] == 4) {TPM0->CONTROLS[2].CnV = clap1[sampleCNT];}
			if(play_samples[i] == 5) {TPM0->CONTROLS[2].CnV = clap2[sampleCNT];}
			if(play_samples[i] == 6) {TPM0->CONTROLS[2].CnV = clap3[sampleCNT];}
			if(play_samples[i] == 7) {TPM0->CONTROLS[2].CnV = clap4[sampleCNT];}
			
			//CYMBALS & HATS  SAMPLES 8, 9, 10
			if(play_samples[i] == 8) {TPM0->CONTROLS[2].CnV = openHihat1[sampleCNT];}
			if(play_samples[i] == 9) {TPM0->CONTROLS[2].CnV = openHihat2[sampleCNT];}
			if(play_samples[i] == 10) {TPM0->CONTROLS[2].CnV = crash1[sampleCNT];} // do wywalenia
			
			//TOM SAMPLES 11, 12
			if(play_samples[i] == 11) {TPM0->CONTROLS[2].CnV = tom1[sampleCNT];}
			if(play_samples[i] == 12) {TPM0->CONTROLS[2].CnV = tom2[sampleCNT];} // tak samo praktycznie
			
			// MUSICAL & FX & VOX SAMPLES 13, 14, 15, 16
			if(play_samples[i] == 13) {TPM0->CONTROLS[2].CnV = piano[sampleCNT];}
			if(play_samples[i] == 14) {TPM0->CONTROLS[2].CnV = brass[sampleCNT];}
			if(play_samples[i] == 15) {TPM0->CONTROLS[2].CnV = horn[sampleCNT];}
			if(play_samples[i] == 16) {TPM0->CONTROLS[2].CnV = boi[sampleCNT];}		//horn albo boi				
		}
		
		if (sampleCNT > 500) {
			sampleCNT = 0;
			TPM0->CONTROLS[2].CnV = 0;
			i++;
			if(i ==32) {i = 0;}
		}
		
		// 13.699 / 3 ~ 4,566kHz ~ WAVE_RATE
		if (++upSampleCNT > (UPSAMPLING-1)) upSampleCNT = 0;
	}
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK; 
}