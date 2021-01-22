
#include "pmusic.h"

static volatile uint16_t music[4][500];

static int add = 0;

static int time = 0;


void musicInit(void) {
	volatile int i;
	volatile int j;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 500; j++) {
			music[i][j] = j+i;
		}
	}
}

/*
void musicAdd(uint8_t table[500]) {
	volatile int j;
	add += 1;
	for(j = 0; j < 500; j++) {
		music[time][j] += table[j];
	}
}

void musicReset(void) {
	volatile int i;
	volatile int j;
	add = 0;
	for(i = 0; i < 4; i++) {
		for(j = 0; j < 500; j++) {
			music[i][j] = silence[j];
		}
	}
}
*/

uint16_t getMusic(int a, int b) {
	return music[a][b];
}
