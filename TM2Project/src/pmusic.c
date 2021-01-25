/******************************************************************************
 * This file is a part of the Music Sequencer Project for SM2                 *
 ******************************************************************************/

/**
 * @file pmusic.c
 * @author Kumka, Potoczek
 * @date Dec 2020
 * @brief File containing definitions for music handling
 * @ver 0.1
 */
 
#include "pmusic.h"

/******************************************************************************\
* Private definitions
\******************************************************************************/
#define SIZE 32

/******************************************************************************\
* Private memory declarations
\******************************************************************************/
static int music[SIZE];

static uint8_t musicTime = 0;
static uint8_t size = SIZE;


void musicInit(void) {  // initalization of music array
	
	volatile int i;
	for (i = 0; i < 32; i++) {
			music[i] = 0;
	}
}


int getMusic(uint8_t a) {  // getter for music array
	return music[a];
}


void musicAddSample(uint8_t sampleTime, int sampleNum) {  // sample adder
	music[sampleTime] = sampleNum;
}


void musicReset(void) {  // reset music array
	volatile int i;
	for (i = 0; i < SIZE; i++) {
			music[i] = 0;
	}
}


uint8_t getSize(void) {  // geter for music array size
	return size;
}


void setSize(uint8_t newSize) {  // setter for music array size
	size = newSize;
}


uint8_t getMusicTime(void) {  // getter for currently played element of music array
	return musicTime;
}


void incMusicTime(void) {  // go to next element of music array
	musicTime++;
}


void resetMusicTime(void) {  // go back to first element of music array
	musicTime = 0;
}
