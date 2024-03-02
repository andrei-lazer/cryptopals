#include "helpers.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* function which takes in a string, and gives out the mean squared distance
 * from the average english letter frequency. params: char* input returns:
 * float, the MSE
 */

float freq_array[] = {0.082,  0.015, 0.028,   0.043,  0.127,  0.022, 0.020,
                      0.061,  0.07,  0.0015,  0.0077, 0.04,   0.024, 0.067,
                      0.075,  0.019, 0.00095, 0.06,   0.063,  0.091, 0.028,
                      0.0098, 0.024, 0.0015,  0.02,   0.00074};

char *alphabet = "abcdefghijklmnopqrstuvwxyz";

/* function that checks if c is in string) */

int c3_in_string(char c, char *string, int len) {
  return strchr(string, c) != NULL;
}

/* checks if x is not "nice" */

int c3_isnotprintable(char x) {
  char *notallowed = ")({}/<>+=*^%#~`#$|@_;:\\&[]";
  return ((!isprint(x) && x != '\n') ||
          c3_in_string(x, notallowed, strlen(notallowed)));
}

char *c3_single_byte_XOR_solver(char *input, int len) {

  int candidate;
  char *xored = (char *)malloc(len);
  float mse;

  int isstring;

  for (candidate = 0x00; candidate < 0x100; candidate++) {
    isstring = 1;
    for (int i = 0; i < len; i++) {
      xored[i] = input[i] ^ candidate;
      if (c3_isnotprintable(xored[i])) {
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

int main() {
  float sum = 0;
  for (int i = 0; i < 26; i++) {
    sum += freq_array[i];
  }

  char *code =
      "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  char *raw_code = hextoraw(code, strlen(code));

  printf("solution: %s\n", c3_single_byte_XOR_solver(raw_code, strlen(code) / 2));
}
