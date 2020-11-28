#include <stdio.h>
#include <stdlib.h>

#include "reader.h"
// #include "charcode.h"
#include "token.h"
#include "error.h"
#include "scanner.h"


extern int lineNo;
extern int colNo;
extern int currentChar;

Token* getToken(void){ 
  //TODO: đọc đầu vào, trả về token
  //printf("\nGetToken: %d-%d:\n",lineNo, colNo);
  //currentChar chua ky tu doc duoc tu van ban nguon boi ham getCh()
  if (currentChar == EOF) return makeToken(NONE, lineNo, colNo);
  Token *token;
  int ln, cn;

  while (currentChar == ' ' || currentChar == '\n' || currentChar == '\t')
    readChar();

  if (isalpha(currentChar))
  { // IDENT
    token = makeToken(NONE, lineNo, colNo);
    int count = 1;

    token->string[0] = (char)currentChar;
    readChar();

    while ((currentChar != EOF) && (isalpha(currentChar) || isdigit(currentChar))) {
      if (count < MAX_IDENT_LEN) token->string[count++] = (char)currentChar;
      readChar();
    }

    token->string[count] = '\0';
    token->tokenType = checkKeyword(token->string);

    if (token->tokenType == NONE)
      token->tokenType = IDENT;

    return token;
  }

  if (isdigit(currentChar))
  { // NUMBER
    token = makeToken(NUMBER, lineNo, colNo);
    int count = 0;

    while ((currentChar != EOF) && (isdigit(currentChar))) {
      if (count < MAX_NUMBER_LEN) token->string[count++] = (char)currentChar;
      else { 
        error(ERR_NUMBER_TOO_LONG, lineNo, colNo);
        return token;
      }
      readChar();
    }

    token->string[count] = '\0';
    token->value = atoi(token->string);
    return token;
  }

  if (currentChar == '+')
  { // PLUS
    readChar();
    return makeToken(PLUS, lineNo, colNo);
  }

  if (currentChar == '-')
  { // MINUS
    readChar();
    return makeToken(MINUS, lineNo, colNo);
  }

  if (currentChar == '*')
  { // TIMES
    readChar();
    return makeToken(TIMES, lineNo, colNo);
  }

  if (currentChar == '/')
  { // SLASH
    readChar();
    return makeToken(SLASH, lineNo, colNo);
  }

  if (currentChar == '=')
  { // EQU
    readChar();
    return makeToken(EQU, lineNo, colNo);
  }

  if (currentChar == '<')
  {
    ln = lineNo;
    cn = colNo;
    readChar();
    if (currentChar == '>')
    { //NEQ: <>
      readChar();
      return makeToken(NEQ,ln,cn);
    }
    else if (currentChar == '=')
    { // LEQ: <=
      readChar();
      return makeToken(LEQ,ln,cn);
    }
    else
      return makeToken(LSS,ln,cn);
  }

  if (currentChar == '>')
  {
    ln = lineNo;
    cn = colNo;
    readChar();
    if (currentChar == '=')
    { // GEQ: >=
      readChar();
      return makeToken(GEQ, ln, cn);
    }
    else
      return makeToken(GTR, ln, cn); // >
  }

  if (currentChar == '(')
  { 
    ln = lineNo;
    cn = colNo;
    readChar();
    if (currentChar != '*') // LPARENT
      return makeToken(LPARENT, ln, cn);
    // currentChar == '*'
    int isMacthComment = 0;
    while (!isMacthComment)
    {
      readChar();
      while (currentChar != '*' && currentChar != EOF)
        readChar();
      if (currentChar != EOF) readChar();
      else return makeToken(NONE, ln, cn);
      if (currentChar == ')')
      {
        isMacthComment = 1;
        readChar();
        return getToken();
      }
    }
  }

  if (currentChar == ')')
  { // RPARENT
    readChar();
    return makeToken(RPARENT, lineNo, colNo);
  }

  if (currentChar == '[')
  { // LBRACK
    readChar();
    return makeToken(LBRACK, lineNo, colNo);
  }

  if (currentChar == ']')
  { // RBRACK
    readChar();
    return makeToken(RBRACK, lineNo, colNo);
  }

  if (currentChar == ':')
  { // MINUS
    ln = lineNo;
    cn = colNo;
    readChar();
    if (currentChar == '=')
    { // ASSIGN
      readChar();
      return makeToken(ASSIGN, ln, cn);
    }
    return makeToken(NONE, ln, cn); // error
  }

  if (currentChar == ';')
  { // SEMICOLON
    readChar();
    return makeToken(SEMICOLON, lineNo, colNo);
  }

  if (currentChar == ',')
  { // COMMA
    readChar();
    return makeToken(COMMA, lineNo, colNo);
  }

  if (currentChar == '.')
  { // PERIOD
    readChar();
    return makeToken(PERIOD, lineNo, colNo);
  }

  if (currentChar == '%')
  { // PERCENT
    readChar();
    return makeToken(PERCENT, lineNo, colNo);
  }

  return makeToken(NONE, lineNo, colNo);
}

Token* getValidToken(void) {
  Token* token = getToken();
  while (token->tokenType == NONE ){
    if (currentChar == EOF) error(ERR_END_OF_FILE, lineNo, colNo);
    else token = getToken();
  } 
  return token;
}


void printToken(Token *token) {

  printf("line: %-3d, column: %-3d: ", token->lineNo, token->colNo);

  switch (token->tokenType) {
  case IDENT: 
    printf("%s (%s)\n", tokenToString(token->tokenType), token->string);break;
  case NUMBER:
    printf("%s (%s)\n", tokenToString(token->tokenType), token->string);break;
  case BEGIN:
  case CALL: 
  case CONST: 
  case DO: 
  case ELSE: 
  case END: 
  case FOR:
  case IF:
  case ODD:
	case PROCEDURE:
  case PROGRAM:
  case THEN:
  case TO:
  case VAR:
  case WHILE:
	case PLUS:
  case MINUS:
  case TIMES:
  case SLASH:
  case EQU:
  case NEQ:
  case LSS:
  case LEQ:
  case GTR:
  case GEQ:
  case PERCENT:
	case LPARENT:
  case RPARENT:
  case LBRACK:
  case RBRACK:
  case PERIOD:
  case COMMA:
  case SEMICOLON:
  case ASSIGN:
  case NONE:
    printf("%s \n", tokenToString(token->tokenType));break;
  default:
    printf("không có token type phù hợp");
    break;
  }
}