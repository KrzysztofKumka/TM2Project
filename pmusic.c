
#include "pmusic.h"

#define SIZE 32

static int music[SIZE];

static uint8_t musicTime = 0;

void musicInit(void) {  // initalization of music array
	/*
	volatile int i;
	for (i = 0; i < 32; i++) {
			music[i] = 0;
	}
	*/
	volatile int i;
	music[0] = 1;
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
	music[11] = 12;
	for (i = 12; i < SIZE; i++) {
		music[i] = 0;
	}
	
	
}

int getMusic(int a) {  // getter for music array
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
