#ifndef __PARSER_H__
#define __PARSER_H__
#include "token.h"

void scan(void);
void eat(TokenType tokenType);

void compileFactor(void);//phân tích nhân tử
void compileTerm(void);//phân tích số hạng
void compileExpression(void); // phân tích biểu thức
void compileCondition(void); // phân tích điều kiện
void compileStatement(void); // phân tích câu lệnh
void compileBlock(void); // phân tích các khối câu lệnh
void compileProgram();	//Phân tích chương trình


int compile(char *fileName);

#endif