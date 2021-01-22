
#include "pmusic.h"

static uint8_t music[7][500];

static uint8_t added[7];

void musicInit(void) {  // initalization of music array
	volatile int i;
	volatile int j;
	for (i = 0; i < 7; i++) {
		added[i] = 0;
		for(j = 0; j < 500; j++) {
			music[i][j] = 0;
			
			/* for testing purposes
			if (i == 0) music[i][j] = 0;
			if (i == 1) music[i][j] = 0;
			if (i == 2) music[i][j] = 0;
			if (i == 3) music[i][j] = 0;
			if (i == 4) music[i][j] = 0;
			if (i == 5) music[i][j] = 0;
			if (i == 6) music[i][j] = 0;
			*/
		}
	}
}

uint8_t getMusic(int a, int b) {  // getter for music array
	return music[a][b];
}

void musicAddSample(const uint8_t sample[500], uint8_t sampleTime) {  // sample adder
	volatile int j;
	for (j = 0; j < 500; j++) {
		music[sampleTime][j] = ((music[sampleTime][j] * added[sampleTime]) + sample[j]) / (added[sampleTime] + 1);  // adding new sample and normalization
	}
	added[sampleTime]++;
}

void musicReset(void) {  // reset music array
	volatile int i;
	volatile int j;
	for (i = 0; i < 7; i++) {
		added[i] = 0;
		for (j = 0; j < 500; j++) {
			music[i][j] = 0;
		}
	}
}
