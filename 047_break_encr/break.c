#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void freqCount(FILE* f, int* alphaCount){
	int c;
	while ((c = fgetc(f)) != EOF) {
		if (isalpha(c)) {
			alphaCount[c - 'a'] += 1;
		}
	}
}

int getMax(int* alphaCount) {
	int maxCount  = alphaCount[0];
	int maxIndex = 0;
	for(int i = 1; i < 26; i++) {
		if (alphaCount[i] > maxCount) {
			maxCount = alphaCount[i];
			maxIndex = i;
		}
	}
	return maxIndex;
}

int decrypt(int maxIndex) {
	int key = (maxIndex + 'a' - 'e' + 26) % 26;
	return key;
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr, "Usage: break inputFileName\n");
		return EXIT_FAILURE;
	}
	FILE* f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr, "could not open the file\n");
	}
	int alphaCount[26] = {0};
	freqCount(f, alphaCount);
	int maxIndex = getMax(alphaCount);
	int key = decrypt(maxIndex);
	printf("%d\n", key);
	if (fclose(f) != 0) {
		fprintf((stderr), "Failed to close the input file!\n");
		return EXIT_FAILURE;
	}
	return EXIT_SUCCESS;
}
