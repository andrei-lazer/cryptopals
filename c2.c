#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"

char* c2_fixedXOR(char* a, char* b, size_t len) {
	printf("len = %lu\n", len);
	char* output = (char *) malloc(sizeof(char) * len);
	int i;

	for (i = 0; i < len; i++) {
		output[i] = a[i] ^ b[i];
	}
	output[i] = '\0';

	return output;
}


int main() {
	char* a = "1c0111001f010100061a024b53535009181c";
	char* b = "686974207468652062756c6c277320657965";
	int len = strlen(b);
	char* raw_a = hextoraw(a, len);
	char* raw_b = hextoraw(b, len);
	char* raw_sol = c2_fixedXOR(raw_a, raw_b, len/2);
	char* hex_sol = rawtohex(raw_sol, len/2); 

	printf("Raw solution: %s\n", raw_sol); 
	printf("Hex solution: %s\n", hex_sol); 

	printf("strcmp with correct result: %d\n", strcmp("746865206b696420646f6e277420706c6179", hex_sol));

}
