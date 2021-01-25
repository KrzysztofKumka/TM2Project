
#include "pmusic.h"

#define SIZE 32

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

uint8_t getSize(void) {
	return size;
}

void setSize(uint8_t newSize) {
	size = newSize;
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
