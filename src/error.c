#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(ErrorCode err, int lineNo, int colNo) {
  switch (err) {
  case ERR_NUMBER_TOO_LONG:
    printf("\nline: %-3d, column: %-3d: %s\n", lineNo, colNo, ERM_NUMBER_TOO_LONG);
    break;
  
  }
  exit(0);
}

void missingToken(TokenType tokenType, int lineNo, int colNo) {
  printf("\n%d-%d:Missing %s\n", lineNo, colNo, tokenToString(tokenType));
  exit(0);
}

void assert(char *msg) {
  printf("%s\n", msg);
}