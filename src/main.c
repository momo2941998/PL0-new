#include <stdio.h>
#include "reader.h"
//#include "scanner.h"
#include "parser.h"
#include "virtualMachine.h"
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

/* 
 * Example lexical analysis
 * 
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
*/

// extern int compile(char *fileName);

// int main(int argc, char *argv[])
// {
//   if (argc == 1){
//     compile("data/test1.pl0");
//   }
//   else if (argc == 2){
//     compile(argv[1]);
//   }

//   else
//     printf("Syntax error \n");
//   return 0;
// }

int main(int argc, char const *argv[])
{
  Instruction Code[MAX_CODE] = {
    {OP_J, 0, 1},
    {OP_INT, 0, 5},
    {OP_LA, 0, 4},
    {OP_LC, 0, 5},
    {OP_ST, 0, 0},
    {OP_LA, 0, 4},
    {OP_LC, 0, 10},
    {OP_LV, 0, 4},
    {OP_MUL, 0, 0},
    {OP_ST, 0, 0},
    {OP_LV, 0,4},
    {OP_WRI, 0, 0},
    {OP_WLN, 0, 0},
    {OP_HL, 0, 0}
  };
  intepreter(Code);
  return 0;
}
