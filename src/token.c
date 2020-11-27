#include <stdlib.h>
#include <ctype.h>
#include "token.h"

/*
* keywords lưu trữ các các từ tố là tên riêng 
* ------------
* string: dạng text của từ tố IDENT
* Token: TokenType của từ tố IDENT
*/
struct {
  	char string[MAX_IDENT_LEN + 1];
  	TokenType Token;
} keywords[KEYWORDS_COUNT] = {
  		{"BEGIN", BEGIN},
  		{"CALL", CALL},
  		{"CONST", CONST},
  		{"DO", DO}, 
    	{"ELSE", ELSE},
      	{"END", END},
        {"FOR", FOR},
   		{"IF", IF},
     	{"ODD",ODD},
  		{"PROCEDURE", PROCEDURE},
		{"PROGRAM", PROGRAM},
    	{"THEN", THEN},
    	{"TO", TO},
		{"VAR", VAR},
  		{"WHILE", WHILE}
};

/*
* TabToken[i] : từ tố ứng với TokenType i
*/
char TabToken[][10] = {	"NONE", "IDENT", "NUMBER",		
		"BEGIN", "CALL", "CONST", "DO",  "ELSE", "END", "FOR", "IF", 
		"ODD", "PROCEDURE", "PROGRAM", "THEN", "TO", "VAR", "WHILE",
	
		"PLUS", "MINUS", "TIMES", "SLASH", "EQU", "NEQ", "LSS", 
		"LEQ", "GTR", "GEQ", "PERCENT", "LPARENT", "RPARENT", 
		"LBRACK", "RBRACK", "PERIOD", "COMMA", "SEMICOLON", "ASSIGN" 
	};

TokenType checkKeyword(char *string)
{
  //TODO: kiểm tra xâu str có phải từ khóa không
  char tmp[100];
  strcpy(tmp, string);
  for (int i = 0; i < strlen(tmp); i++)
    tmp[i] = toupper(tmp[i]);
  for (int i = 0; i < KEYWORDS_COUNT; i++)
  {
    if (!strcmp(keywords[i].string, tmp))
    { // strcmp return 0 if two string equal
      return keywords[i].Token;
    }
  }
  return NONE;
}

Token* makeToken(TokenType tokenType, int lineNo, int colNo) {
  Token *token = (Token*)malloc(sizeof(Token));
  token->tokenType = tokenType;
  token->lineNo = lineNo;
  token->colNo = colNo;
  return token;
}

char *tokenToString(TokenType tokenType){
  return TabToken[tokenType];
}