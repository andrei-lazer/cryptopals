#ifndef HELPER_DEFS
#define HELPER_DEFS

int hexchartoint(char hex);
char *hextoraw(char*, int);
char *rawtobase64(char*, int);
char *rawtohex(char*, int);
char *fixedXOR(char*, char*, int);
char *singlebyteXOR(char, char*, int);
char *single_byte_XOR_solver(char*, int);

#endif
