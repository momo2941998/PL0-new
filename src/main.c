#include <stdio.h>
#include "reader.h"
#include "scanner.h"
/* 
 * Example readFile
 * 

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;
  int ch = readChar();
  while (ch != EOF) {
    printf("%c",ch);
    ch = readChar();
  }
  closeInputStream();
  return IO_SUCCESS;
}
*/

int compile(char *fileName) {
  if (openInputStream(fileName) == IO_ERROR)
    return IO_ERROR;
  Token *token;
  do {
    token = getToken();
    assert(""); printToken(token);
  } while (token->tokenType != NONE);
  closeInputStream();
  return IO_SUCCESS;
}

int main(int argc, char *argv[])
{
  if (argc == 1){
    compile("data/test1.pl0");
  }
  else if (argc == 2){
    compile(argv[1]);
  }

  else
    printf("Syntax error \n");
  return 0;
}