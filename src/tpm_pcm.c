
#include "tpm_pcm.h"

void TPM0_IRQHandler(void);

static uint16_t upSampleCNT = 0;
static uint16_t sampleCNT = 0;
static uint8_t  playFlag = 0;
static uint8_t time;
static uint8_t prevTime = 0;

static uint8_t sample;
static uint8_t volume = 255;

static uint8_t upSampling;
static uint8_t speed;

void TPM0_Init(void) {
		
  SIM->SCGC6 |= SIM_SCGC6_TPM0_MASK;		
	SIM->SOPT2 |= SIM_SOPT2_TPMSRC(1);    // CLK ~ 41,9MHz (CLOCK_SETUP=0)

	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK; 
	PORTB->PCR[7] = PORT_PCR_MUX(2);			// PCM output -> PTB7, TPM0 channel 2
	
	TPM0->SC |= TPM_SC_PS(2);  					  // 41,9MHz / 4 ~ 10,48MHz
	TPM0->SC |= TPM_SC_CMOD(1);					  // internal input clock source

	TPM0->MOD = 255; 										  // 8bit PCM
																				// 10,48MHz / 256 ~ 40,96kHz
	
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
}

void TPM0_PCM_Play(void) {
	sampleCNT = 0;   /* start from the beginning */
	playFlag = 1;
}

void TPM0_PCM_Pause(void) {
	playFlag = 0;
}

void TPM0_IRQHandler(void) {
	if (playFlag) {
		speed = setSpeed();
		triggerADC();
		time = getMusicTime();
		if (upSampleCNT == 0) {
			sampleCNT++;
			switch (getMusic(time)) {
				
				//NO MUSIC
				case 0:
					sample = 0;
					break;
				
				//PLAY/PAUSE
				case 1:
					sample = 0;
					break;
				
				//KICK SAMPLES 2, 3
				case 2:
					sample = kick2[sampleCNT];
					break;
				case 3:
					sample = kick3[sampleCNT];
					break;
				
				//CLAP SAMPLES 4, 5, 6, 7
				case 4:
					sample = clap1[sampleCNT];
					break;
				case 5:
					sample = clap2[sampleCNT];
					break;
				case 6:
					sample = clap3[sampleCNT];
					break;
				case 7:
					sample = clap4[sampleCNT];
					break;
				
				//CYMBALS & HATS  SAMPLES 8, 9, 10
				case 8:
					sample = openHihat1[sampleCNT];
					break;
				case 9:
					sample = openHihat2[sampleCNT];
					break;
				case 10:
					sample = crash1[sampleCNT];
					break;
				
				//TOM SAMPLES 11, 12
				case 11:
					sample = tom1[sampleCNT];
					break;
				case 12:
					sample = tom2[sampleCNT];
					break;
				
				// MUSICAL & FX & VOX SAMPLES 13, 14, 15, 16
				case 13:
					sample = piano[sampleCNT];
					break;
				case 14:
					sample = brass[sampleCNT];
					break;
				case 15:
					sample = horn[sampleCNT];
					break;
				case 16:
					sample = boi[sampleCNT];
					break;
			}
			
			if (sample != 0) {
				TPM0->CONTROLS[2].CnV = (volume /  255) * sample;
			}
		}
		if (sampleCNT > 500) {
			sampleCNT = 0;  // play in loop
			GUI_whichSample(time, prevTime);
			prevTime = time;
			incMusicTime();
			if (getMusicTime() >= getSize()) resetMusicTime();
			TPM0->CONTROLS[2].CnV = 0;
		}
		upSampling = speed/10;
		// 40,96kHz / 10 ~ 4,1kHz ~ WAVE_RATE
		if (++upSampleCNT > (upSampling - 1)) upSampleCNT = 0;
	}
	
	TPM0->CONTROLS[0].CnSC |= TPM_CnSC_CHF_MASK;
}
