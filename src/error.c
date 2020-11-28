#include <stdio.h>
#include <stdlib.h>
#include "error.h"

void error(ErrorCode err, int lineNo, int colNo) {
  switch (err) {
  case ERR_NUMBER_TOO_LONG:
    printf("\nline: %-3d, column: %-3d: %s\n", lineNo, colNo, ERM_NUMBER_TOO_LONG);
    break;
  case ERR_NO_TOKEN: 
    printf("\nline: %-3d, column: %-3d: %s\n", lineNo, colNo, ERM_NO_TOKEN);
    break;
  case ERR_SYNTAX_ERROR: 
    printf("\nline: %-3d, column: %-3d: %s\n", lineNo, colNo, ERM_SYNTAX_ERROR);
    break;
  case ERR_END_OF_FILE: 
    printf("\nline: %-3d, column: %-3d: %s\n", lineNo, colNo, ERM_END_OF_FILE);
    break;
  }
  exit(0);
}

void missingToken(TokenType tokenType, int lineNo, int colNo) {
  printf("\nline: %-3d, column: %-3d: Missing %s\n", lineNo, colNo, tokenToString(tokenType));
  exit(0);
}

void assert(char *msg) {
  printf("%s\n", msg);
}