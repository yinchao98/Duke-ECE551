#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int* array, size_t n) {
	if (n == 0) {
		return 0;
	} else {
		size_t currentNum = 1;
		size_t maxNum = currentNum;
		for (size_t i = 1; i < n; i++) {
			if (*(array + i) > *(array + i -1)) {
				currentNum ++;
			} else {
				currentNum = 1;
			}
			if (currentNum > maxNum) {
					maxNum = currentNum;
			}
		}
		return maxNum;
	}
}
