#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void lineToMatrix(int lineNum, char* str, char matrix[][10]) {
	for (int i = 0; i < 10; i++) {
		matrix[lineNum][i] = str[i];
	}
}

void rotate90(char before[][10], char after[][10]){
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			after[i][j] = before[9 - j][i];
			printf("%c", after[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char** argv) {
	if (argc != 2) {
		fprintf(stderr,"Usage: inputFileName\n");
		return EXIT_FAILURE;
	}
	FILE* f = fopen(argv[1], "r");
	if (f == NULL) {
		fprintf(stderr,"Could not open the file!\n");
		return EXIT_FAILURE;
	}
	char matrix[10][10];
	int i = 0;
	while (i < 10) {
		char str[12];
		if (fgets(str, 12, f) == NULL) {
			fprintf(stderr,"Could not read a line!\n");
			return EXIT_FAILURE;
		}
		char* p = strchr(str, '\n');
		if ((p == NULL) || (p - str) != 10) {
			fprintf(stderr, "Format of input is wrong!\n");
			return EXIT_FAILURE;
		} 
		lineToMatrix(i, str, matrix);
		i++;
	}
	char str[12];
	if (fgets(str, 12, f) != NULL) {
			fprintf(stderr, "Format of input is wrong!\n");
			return EXIT_FAILURE;
	} 
	char rotateMatrix[10][10];
	rotate90(matrix, rotateMatrix);
	return EXIT_SUCCESS;
}
