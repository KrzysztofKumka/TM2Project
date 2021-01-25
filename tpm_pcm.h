
#ifndef TPM_PCM_H
#define TPM_PCM_H

#include "frdm_bsp.h"
#include "pmusic.h"
#include "GUI.h"
#include "ADC.h"

void TPM0_Init(void);

uint8_t getPlayFlag(void);

void TPM0_PCM_Play(void);

void TPM0_PCM_Pause(void);

#endif /* TPM_PCM_H */
