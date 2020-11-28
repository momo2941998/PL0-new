#ifndef __ERROR_H__
#define __ERROR_H__
#include "token.h"

typedef enum {
  ERR_NUMBER_TOO_LONG, 
  ERR_NO_TOKEN, 
  ERR_SYNTAX_ERROR, 
  ERR_END_OF_FILE
} ErrorCode;

#define ERM_NUMBER_TOO_LONG "number too long"
#define ERM_NO_TOKEN "no token"
#define ERM_SYNTAX_ERROR "syntax error"
#define ERM_END_OF_FILE "end of file"

// print ERM depend on ErrorCode
void error(ErrorCode err, int lineNo, int colNo);

// print missingToken
void missingToken(TokenType tokenType, int lineNo, int colNo);

// print msg+'\n'
void assert(char *msg);

#endif