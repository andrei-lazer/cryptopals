#include "helpers.h"
#include <stdio.h>
#include <string.h>

int main() {
  FILE *fp;
	int len = 61;
  char line[len];
  fp = fopen("4.txt", "r");

  while (fgets(line, len, fp)) {
		char* raw = hextoraw(line, len);
		char* attempt = single_byte_XOR_solver(raw, len / 2);
    if ((strcmp(raw, attempt) && strcmp(attempt, "NAN"))) {
			printf("%s", attempt);
    }
  }
}
