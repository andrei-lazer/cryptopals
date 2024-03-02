#include "helpers.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// #### NON-CRYPTO ####

int in_string(char c, char *string, int len) {
  return strchr(string, c) != NULL;
}

int isnotprintable(char x) {
  char *notallowed = ")({}/<>+=*^%#~`#$|@_;:\\&[]";
  return ((!isprint(x) && x != '\n') ||
          in_string(x, notallowed, strlen(notallowed)));
}

// #### CONVERSIONS ####

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

char *hextoraw(char *input, int len) {
  char *output = (char *)malloc(len / 2);

  for (int i = 0; i < len / 2; i++) {
    output[i] =
        (hexchartoint(input[2 * i]) << 4) | hexchartoint(input[2 * i + 1]);
  }

  output[len / 2] = '\0';

  return output;
}

/* function that converts a byte string into a hexadecimal string
 * params: char* input, a raw byte string
 * returns; char*, an array of hexadecimal digits.
 */

char *rawtohex(char *input, int len) {
  char *output = (char *)malloc(len * 2);
  char *map = "0123456789abcdef";

  int i;
  int k = 0;
  int first_index, second_index;

  for (int i = 0; i < len; i++) {
    first_index = input[i] >> 4 & 0xF;
    second_index = input[i] & 0xF;
    output[k++] = map[first_index];
    output[k++] = map[second_index];
  }
  output[k] = '\0';

  return output;
}

/* function that converts a raw string of bytes into a string of base64 digits
 * params: char* input, a byte array
 * returns: char*, an encoded array of base64 digits.
 */

char *rawtobase64(char *input, int len) {
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
      output[k++] = map[temp >> j * 6 & 0x3F];
    }
  }

  output[k] = '\0';
  return output;
}

char *fixedXOR(char *a, char *b, int len) {
  char *output = (char *)malloc(sizeof(char) * len);
  int i;

  for (i = 0; i < len; i++) {
    output[i] = a[i] ^ b[i];
  }
  output[i] = '\0';

  return output;
}



char *singlebyteXOR(char byte, char *target, int len) {
  char* repeated = (char*) malloc(len);
  for (int i = 0; i < len; i++) {
    repeated[i] = byte;
  }

  return fixedXOR(repeated, target, len);
}

// #### SOLVERS ####

char *single_byte_XOR_solver(char *input, int len) {

  int candidate;
  char *xored = (char *)malloc(len);
  float mse;

  int isstring;

  for (candidate = 0x00; candidate < 0x100; candidate++) {
    isstring = 1;
    for (int i = 0; i < len; i++) {
      xored[i] = input[i] ^ candidate;
      if (isnotprintable(xored[i])) {
        isstring = 0;
        break;
      }
    }

    if (isstring) {
      return xored;
    }
  }
  return "NAN";
}
