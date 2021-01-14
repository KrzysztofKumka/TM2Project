
#include "pmusic.h"

void musicInit(void) {
	
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 16; j++) {
			
				music[i][j] = silence;
		}
	}
}

void musicConvert(void) {
	for(int i = 0; i < 8; i++) {
		for(int j = 0; j < 500; j++) {
				//sum[i][j] = (uint8_t)((int)&music[0][i][sampleCNT++] + (int)&music[1][i][sampleCNT++] + (int)&music[2][i][sampleCNT++]);
			// music[0][i][sampleCNT++] + music[1][i][sampleCNT++] + music[2][i][sampleCNT++];
		}
	}
}
