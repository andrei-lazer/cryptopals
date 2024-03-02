#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char input[] = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706"
               "f69736f6e6f7573206d757368726f6f6d";

int hexchartoint(char hex) {

  switch (hex) {
  case '0' ... '9':
    return hex - '0';
    break;

  case 'a' ... 'z':
    return hex - 'a' + 10;
    break;
  }
  return '?';
}

/* function that converts a hexadecimal string into its raw (byte string) form.
 * params: char* input, an array of hexadecimal digits
 * returns: char*, an array of bytes, with each byte equivalent to 2 hex digits
 */

char *hextoraw(char *input) {
  int len = strlen(input);
  char *output = (char *)malloc(len / 2);

  for (int i = 0; i < len / 2; i++) {
    output[i] =
        (hexchartoint(input[2 * i]) << 4) | hexchartoint(input[2 * i + 1]);
  }

  output[len / 2] = '\0';

  return output;
}

/* function that converts a raw string of bytes into a string of base64 digits
 * params: char* input, a byte array
 * returns: char*, an encoded array of base64 digits.
 */

char *rawtobase64(char *input) {
  int len = strlen(input);
  char *output = (char *)malloc(len * 4 / 3);
  char map[] =
      "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
  unsigned int temp; // every iteration, is reset and updated to
  unsigned int a, b, c;

  int k = 0;

  for (int i = 0; i < len; i += 3) {
    a = input[i] << 16;
    b = input[i + 1] << 8;
    c = input[i + 2];
    temp = a | b | c;

    // temp is the concatenation of the ith set of 3 bytes in input.
    // then, we go through this 6 bits at a time and map it to a base 64 digit

    for (int j = 3; j >= 0; j--) {
      output[k++] = map[temp>>j*6&0x3F];
    }
  }

  output[k] = '\0';
  return output;
}

int main() {
  printf("Running\n");
  char *raw = hextoraw(input);

  printf("raw: %s\n", raw);
  char *base64 = rawtobase64(raw);

  printf("solution: %s\n", base64);

	printf("strcmp with correct solution: %d\n", strcmp("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t", base64));

}
