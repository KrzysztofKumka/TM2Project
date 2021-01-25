#include "ADC.h"

uint8_t ADC_Init(void) {
	
	uint16_t callib_temp;
	SIM->SCGC6 |= SIM_SCGC6_ADC0_MASK;          // connect clock to ADC0
	SIM->SCGC5 |= SIM_SCGC5_PORTB_MASK;					// connect clock to PORTB
	PORTB->PCR[2] &= (uint32_t)~(1<<2);										//PTB2 - analog input, channel 4
	ADC0->CFG1 = (ADC_CFG1_ADICLK(ADICLK_BUS_2) | ADC_CFG1_ADIV(ADIV_4)) & (~ADC_CFG1_ADLSMP_MASK);	// output clock BUS/2=10.49MHz, ADCK clock 2.62MHz (2621440Hz), long sampling time
	ADC0->CFG2 = ADC_CFG2_ADHSC_MASK;										// turn on high-frequency clock support
	ADC0->SC3  = ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(AVGS_32);		// 32-sample averaging, default triggering on demand
	ADC0->SC3 |= ADC_SC3_CAL_MASK;											// calibration start
	while(ADC0->SC3 & ADC_SC3_CAL_MASK);								// wait till the end of callibration
	
	if(ADC0->SC3 & ADC_SC3_CALF_MASK)
{
	  ADC0->SC3 |= ADC_SC3_CALF_MASK;
	  return(1);																				// calibration error
	}
	
	callib_temp = 0x00;
	callib_temp += ADC0->CLP0;
	callib_temp += ADC0->CLP1;
	callib_temp += ADC0->CLP2;
	callib_temp += ADC0->CLP3;
	callib_temp += ADC0->CLP4;
	callib_temp += ADC0->CLPS;
	callib_temp += ADC0->CLPD;
	callib_temp /= 2;
	callib_temp |= 0x8000;                       // set MSB to 1
	ADC0->PG = ADC_PG_PG(callib_temp);           // save in plus-side gain calibration register
	ADC0->SC3 &= ~(ADC_SC3_AVGE_MASK | ADC_SC3_AVGS(AVGS_32));  // turn off hardware averaging
	ADC0->SC1[0] = ADC_SC1_ADCH(4);						// channel 4 as output
	ADC0->CFG1 = (ADC_CFG1_ADICLK(ADICLK_BUS_2) | ADC_CFG1_ADIV(ADIV_1) | ADC_CFG1_MODE(MODE_8)) & (~ADC_CFG1_ADLSMP_MASK);	// ADCK clock 10.49MHz, 8bit resolution, short sampling time
	ADC0->SC2 &= ~ADC_SC2_ADTRG_MASK;          // select software trigerring
	return(0);																	// return if succeeded
}

void triggerADC(void) {
	ADC0->SC1[0] |= ADC_SC1_ADCH(4);  // trigger ADC measurement
}

uint8_t setSpeed(void) {
	if((ADC0->SC1[0] & ADC_SC1_COCO_MASK) != 0) {  // if measurement ended, return value
		return (uint8_t)ADC0->R[0];
	}
	return 0;
}
