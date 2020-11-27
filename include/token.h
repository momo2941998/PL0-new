#ifndef __TOKEN_H__
#define __TOKEN_H__

#define	MAX_NUMBER_LEN   6
#define MAX_IDENT_LEN   10
#define KEYWORDS_COUNT  15

/*
* TokenType quy định enum các loại từ tố trong ngôn ngữ
*/
typedef enum {
  NONE=0, IDENT, NUMBER,
	
  BEGIN, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
		
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS, LEQ,GTR, GEQ, PERCENT,
	LPARENT, RPARENT, LBRACK, RBRACK, PERIOD, COMMA, SEMICOLON, ASSIGN
} TokenType;




typedef struct {
  char string[MAX_IDENT_LEN + 1];
  int lineNo, colNo;
  TokenType tokenType;
  int value;
} Token;

TokenType checkKeyword(char *string);
Token* makeToken(TokenType tokenType, int lineNo, int colNo);
char *tokenToString(TokenType tokenType);


#endif
