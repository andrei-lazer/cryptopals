#include "helpers.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *plaintext = "Burning 'em, if you ain't quick and nimble\n"
                  "I go crazy when I hear a cymbal";

char *true_encoded =
    "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a2622632427276527"
    "2"
    "a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";

char *repeat_XOR_encode(char *plaintext, char *key, int plain_len,
                        int key_len) {
  int i;
  char *encoded = (char *)malloc(plain_len);

  for (i = 0; i < plain_len; i++) {
    encoded[i] = plaintext[i] ^ key[i % key_len];
  }

  return encoded;
}

int main() {

  char *raw_encoded = repeat_XOR_encode(plaintext, "ICE", strlen(plaintext), 3);
  char *hex_encoded = rawtohex(raw_encoded, strlen(plaintext));

  printf("%s\n", hex_encoded);
	printf("strcmp with correct sol: %d\n", strcmp(true_encoded, hex_encoded));
}
