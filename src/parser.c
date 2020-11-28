#include <stdlib.h>
#include<stdio.h>
#include "reader.h"
#include "scanner.h"
#include "parser.h"
#include "error.h"

Token *currentToken;
Token *lookAhead;

void scan(void) { 
  Token* tmp = currentToken;
  currentToken = lookAhead;
  lookAhead = getValidToken();
  free(tmp);
}

void eat(TokenType tokenType) { //duyet ki hieu ket thuc
  if (lookAhead->tokenType == tokenType) {
    printToken(lookAhead);
    scan();
  } else missingToken(tokenType, lookAhead->lineNo, lookAhead->colNo);
}

int compile(char *FileName) {
  if (openInputStream(FileName) == IO_ERROR)
    return IO_ERROR;

  currentToken = NULL;
  lookAhead = getValidToken();

  compileProgram();
  printf("\n");
  free(currentToken);
  free(lookAhead);
  closeInputStream();
  return IO_SUCCESS;

}

void compileProgram(){
  assert("Parsing a Program ....");
  eat(PROGRAM);
  eat(IDENT);
  eat(SEMICOLON);
  compileBlock();
  if (lookAhead->tokenType == PERIOD) {
    printToken(lookAhead);
  } else missingToken(PERIOD, lookAhead->lineNo, lookAhead->colNo);
  assert("Program parsed!");
}

void compileBlock(){
  assert("Parsing a Block ....");
  if (lookAhead->tokenType == CONST || lookAhead->tokenType == VAR || lookAhead->tokenType == PROCEDURE || lookAhead->tokenType == BEGIN) {
    if (lookAhead->tokenType == CONST) {
      eat(CONST);
      eat(IDENT);
      eat(EQU);
      eat(NUMBER);
      while (lookAhead->tokenType == COMMA) {
        eat(COMMA);
        eat(IDENT);
        eat(EQU);
        eat(NUMBER);
      }
      eat(SEMICOLON);
    } 

    if (lookAhead->tokenType == VAR) {
      eat(VAR);
      eat(IDENT);
      if (lookAhead->tokenType == LBRACK) {
        eat(LBRACK);
        eat(NUMBER);
        eat(RBRACK);
      }
      while (lookAhead->tokenType == COMMA){
        eat(COMMA);
        eat(IDENT);
        if (lookAhead->tokenType == LBRACK) {
          eat(LBRACK);
          eat(NUMBER);
          eat(RBRACK);
        }
      }
      eat(SEMICOLON);
    } 

    while (lookAhead->tokenType == PROCEDURE) {
      eat(PROCEDURE);
      eat(IDENT);
      if (lookAhead->tokenType == LPARENT) {
        eat(LPARENT);
        if (lookAhead->tokenType == VAR) eat(VAR);
        eat(IDENT);
        while (lookAhead->tokenType == SEMICOLON){
          eat(SEMICOLON);
          if (lookAhead->tokenType == VAR) eat(VAR);
          eat(IDENT);
        }
        eat(RPARENT);
      }
      eat(SEMICOLON);
      compileBlock();
      eat(SEMICOLON);
    }

    if (lookAhead->tokenType == BEGIN) {
      eat(BEGIN);
      compileStatement();
      while (lookAhead->tokenType == SEMICOLON) {
        eat(SEMICOLON);
        compileStatement();
      }
      eat(END);
    }
    assert("Block parsed");
  }
  else {
    error(ERR_SYNTAX_ERROR, lookAhead->lineNo, lookAhead->colNo);
  }
  
}

void compileStatement(){
  assert("Parsing a Statement ....");
  switch (lookAhead->tokenType)
  {
    case IDENT:
      eat(IDENT);
      if (lookAhead->tokenType == LBRACK){
        eat(LBRACK);
        compileExpression();
        eat(RBRACK);
      }
      eat(ASSIGN);
      compileExpression();
      break;

    case CALL:
      eat(CALL);
      eat(IDENT);
      if (lookAhead->tokenType == LPARENT) {
        eat(LPARENT);
        compileExpression();
        while (lookAhead->tokenType == COMMA) {
          eat(COMMA);
          compileExpression();
        }
        eat(RPARENT);
      }
      break;

    case BEGIN:
      eat(BEGIN);
      compileStatement();
      while (lookAhead->tokenType == SEMICOLON) {
        eat(SEMICOLON);
        compileStatement();
      }
      eat(END);
      break;

    case IF: 
      eat(IF);
      compileCondition();
      eat(THEN);
      compileStatement();
      if (lookAhead->tokenType == ELSE) {
        eat(ELSE);
        compileStatement();
      }
      break;

    case WHILE: 
      eat(WHILE);
      compileCondition();
      eat(DO);
      compileStatement();
      break;

    case FOR:
      eat(FOR);
      eat(IDENT);
      eat(ASSIGN);
      compileExpression();
      eat(TO);
      compileExpression();
      eat(DO);
      compileStatement();
      break;

    default:
      break;
  }
  assert("Statement parsed");
}

void compileExpression(){
  assert("Parsing a Expression ....");
  if (lookAhead->tokenType == PLUS || lookAhead->tokenType == MINUS) 
    eat(lookAhead->tokenType);
  compileTerm();
  while (lookAhead->tokenType == PLUS || lookAhead->tokenType == MINUS){
    eat(lookAhead->tokenType);
    compileTerm();
  }
  assert("Expression parsed");
}

void compileTerm(){
  assert("Parsing a Term ....");
  compileFactor();
  while(lookAhead->tokenType == TIMES || lookAhead->tokenType == SLASH || lookAhead->tokenType == PERCENT){
    eat(lookAhead->tokenType);
    compileFactor();
  }
  assert("Term parsed");
}

void compileFactor(){
  assert("Parsing a Factor ....");
  switch (lookAhead->tokenType)
  {
  case IDENT:
    eat(IDENT);
    if (lookAhead->tokenType == LBRACK){
      eat(LBRACK);
      compileExpression();
      eat(RBRACK);
    }
    break;

  case NUMBER:
    eat(NUMBER);
    break;

  case LPARENT:
    eat(LPARENT);
    compileExpression();
    eat(RPARENT);
    break;

  default:
    error(ERR_SYNTAX_ERROR, lookAhead->lineNo, lookAhead->colNo);
    break;
  }
  assert("Factor parsed");
}

void compileCondition(){
  assert("Parsing a Condition ....");
  if (lookAhead->tokenType == ODD) {
    eat(ODD);
    compileExpression();
  }
  else {
    compileExpression();
    switch (lookAhead->tokenType)
    {
      case EQU:
      case NEQ:
      case LSS:
      case LEQ:
      case GTR:
      case GEQ:
        eat(lookAhead->tokenType);
        compileExpression();
        break;

      default:
        error(ERR_SYNTAX_ERROR, lookAhead->lineNo, lookAhead->colNo);
        break;
    }
  }

  assert("Condition parsed");
}