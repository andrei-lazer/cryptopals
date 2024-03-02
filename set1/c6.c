#include "helpers.h"
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

int hamming(char* a, char* b, int len) { int distance = 0;
	char* xored = fixedXOR(a, b, len);
	char byte;

	for (int i = 0; i < len; i++) {
		byte = xored[i];
		while (byte) {
			byte &= byte - 1;
			distance++;
		}
	}
	return distance;
}

int find_keysize(const char* text, int start, int end, int len) {
	int best_size = 0;
	int best_hamming = INT_MAX;

	char* first_i = calloc(end, sizeof(char));
	char* second_i = calloc(end, sizeof(char));
	int curr_hamming;

	for (int i = start; i < end; i++) {
		strncpy(first_i, text, i);
		strncpy(second_i, text + i, i);

		curr_hamming = hamming(first_i, second_i, i);

		if (curr_hamming < best_hamming) {
			best_hamming = curr_hamming;
			best_size = i;
		}
	}
	return best_size;
}

/* function that solves an arbitrary length XOR cipher
 * params: FILE* file, a pointer to the file containing
 * the hexadecimal ciphertext.
 * returns: char*, the key.
 */

char* solve_XOR_cipher(FILE* file) {

	char* key;

	return key;
}

int main() {

}
