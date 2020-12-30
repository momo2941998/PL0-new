#include "virtualMachine.h"
#include <stdio.h>

// Instruction Code[MAX_CODE];
int s[MAX_DATA]; // stack 
int pc, t, b;
void intepreter(Instruction* Code){
   pc = 0;
   t = -1;
   b = 0;
  int Exit = 0;
  int pause = 0;
  do {
    switch(Code[pc].op){
      case OP_LA:
        t++;
        s[t] = base(Code[pc].p) + Code[pc].q;
        break;
      case OP_LV:
        t++;
        s[t] = s[base(Code[pc].p) + Code[pc].q];
        break;
      case OP_LC:
        t++;
        s[t] = Code[pc].q;
        break;
      case OP_LI:
        s[t] = s[s[t]];
        break;
      case OP_INT:
        t = t + Code[pc].q;
        break;
      case OP_DCT:
        t = t - Code[pc].q;
        break;
      case OP_J:
        pc = Code[pc].q;
        break;
      case OP_FJ:
        if (s[t] == 0){
          pc = Code[pc].q;
          t = t - 1;
        }
        break;
      case OP_HL:
        Exit = 1;
        break;
      case OP_ST:
        s[s[t-1]] = s[t];
        t = t - 2;
        break;
      case OP_CALL:
        s[t+2] = b;
        s[t+3] = pc;
        s[t+4] = base(Code[pc].p);
        b = t + 1;
        pc = Code[pc].q;
        break;
      case OP_EP:
        t = b - 1;
        pc = s[b+2];
        b = s[b+1];
        break;
      case OP_EF:
        t = b;
        pc = s[b+2];
        b = s[b+1];
        break;
      case OP_RC:
        s[s[t]] = fgetc(stdin);
        t = t - 1;
        break;
      case OP_RI:
        scanf("%d", &s[s[t]]);
        t = t - 1;
        break;
      case OP_WRC:
        printf("%c", s[t]);
        t = t - 1;
        break;
      case OP_WRI:
        printf("%d", s[t]);
        t = t - 1;
        break;
      case OP_WLN:
        printf("\n");
        t = t - 1;
        break;
      case OP_ADD:
        t = t - 1;
        s[t] = s[t] + s[t+1];
        break;
      case OP_SUB:
        t = t - 1;
        s[t] = s[t] - s[t+1];
        break;
      case OP_MUL:
        t = t - 1;
        s[t] = s[t] * s[t+1];
        break;
      case OP_DIV:
        t = t - 1;
        s[t] = s[t] / s[t+1];
        break;
      case OP_NEG:
        s[t] = -s[t];
        break;
      case OP_CV:
        s[t+1] = s[t];
        t++;
        break;
      case OP_EQ:
        t = t - 1;
        s[t] = (s[t] == s[t+1]) ? 1 : 0;
        break;
      case OP_NE:
        t = t - 1;
        s[t] = (s[t] != s[t+1]) ? 1 : 0;
        break;
      case OP_GT:
        t = t - 1;
        s[t] = (s[t] > s[t+1]) ? 1 : 0;
        break;
      case OP_LT:
        t = t - 1;
        s[t] = (s[t] < s[t+1]) ? 1 : 0;
        break;
      case OP_GE:
        t = t - 1;
        s[t] = (s[t] >= s[t+1]) ? 1 : 0;
        break;
      case OP_LE:
        t = t - 1;
        s[t] = (s[t] <= s[t+1]) ? 1 : 0;
        break;
      case OP_BP:
        break;
      default:
        printf("not an opcode");
        break;
    }
    pc++;
  }while(Exit == 0);
}

int base(int L) {
  int c = b;
  while (L > 0) {
    c = s[c + 3];
    L --;
  }
  return c;
}
