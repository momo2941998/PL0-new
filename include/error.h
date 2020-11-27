#ifndef __ERROR_H__
#define __ERROR_H__
#include "token.h"

typedef enum {
  ERR_NUMBER_TOO_LONG
} ErrorCode;

#define ERM_NUMBER_TOO_LONG "number too long"

// print ERM depend on ErrorCode
void error(ErrorCode err, int lineNo, int colNo);

// print missingToken
void missingToken(TokenType tokenType, int lineNo, int colNo);

// print msg+'\n'
void assert(char *msg);

#endif