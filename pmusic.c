
#include "pmusic.h"

#define SIZE 32

static int music[SIZE];

static uint8_t musicTime = 0;

void musicInit(void) {  // initalization of music array
	
	volatile int i;
	for (i = 0; i < 32; i++) {
			music[i] = 0;
	}
	
	/*
	//testing purposes
	music[0] = 2;
	music[1] = 0;
	music[2] = 0;
	music[3] = 5;
	music[4] = 0;
	music[5] = 0;
	music[6] = 7;
	music[7] = 0;
	music[8] = 0;
	music[9] = 12;
	music[10] = 0;
	music[11] = 13;
	music[12] = 12;
	music[13] = 13;
	music[14] = 0;
	music[15] = 12;
	music[16] = 0;
	music[17] = 0;
	music[18] = 5;
	music[19] = 0;
	music[20] = 0;
	music[21] = 7;
	music[22] = 0;
	music[23] = 0;
	music[24] = 12;
	music[25] = 0;
	music[26] = 13;
	music[27] = 12;
	music[28] = 13;
	music[29] = 0;
	music[30] = 12;
	music[31] = 0;
	*/
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

uint8_t getMusicTime(void) {
	return musicTime;
}

void incMusicTime(void) {
	musicTime++;
}

void resetMusicTime(void) {
	musicTime = 0;
}
