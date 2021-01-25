/******************************************************************************
 * This file is a part of the Music Sequencer Project for SM2                 *
 ******************************************************************************/

/**
 * @file tmp_pcm.h
 * @author Kumka, Potoczek
 * @date Dec 2020
 * @brief File containing declarations for TPM
 * @ver 0.1
 */
 
#ifndef TPM_PCM_H
#define TPM_PCM_H

#include "frdm_bsp.h"
#include "pmusic.h"
#include "GUI.h"
#include "ADC.h"

void TPM0_Init(void);

void TPM0_PCM_Play(void);

void TPM0_PCM_Pause(void);

#endif /* TPM_PCM_H */
