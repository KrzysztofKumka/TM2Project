/******************************************************************************
 * This file is a part of the Music Sequencer Project for SM2                 *
 ******************************************************************************/

/**
 * @file buttons.h
 * @author Kumka, Potoczek
 * @date Jan 2021
 * @brief File containing declarations for buttons
 * @ver 0.1
 */
 
#ifndef buttons_h
#define buttons_h

#include "pmusic.h"

void buttonsInit(void);

int buttonsGet(void);

void ifButtonClicked(void);

int getButtonNumber(void);

#endif
