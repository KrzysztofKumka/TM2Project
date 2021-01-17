
#include "pmusic.h"

void musicInit(void) {
	
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 500; j++) {
			music[i][j] = kick[j];
		}
	}
}

void musicAdd(uint8_t table[500]) {
	add += 1;
	for(int j = 0; j < 500; j++) {
		music[time][j] += table[j];
	}
}

void musicReset(void) {
	add = 0;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 500; j++) {
			music[i][j] = silence[j];
		}
	}
}

void timeInit(void) {
	for (int i = 0; i < 500; i++) {
		time1[i] = kick[i];
		time2[i] = 0;
		time3[i] = 0;
		time4[i] = 0;
	}
}
