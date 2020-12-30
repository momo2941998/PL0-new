typedef enum {
  OP_LA,   // Load Address:
  OP_LV,   // Load Value:
  OP_LC,   // load Constant 
  OP_LI,   // Load Indirect 
  OP_INT,  // Increment t 
  OP_DCT,  // Decrement t
  OP_J,    // Jump 
  OP_FJ,   // False Jump 
  OP_HL,   // Halt 
  OP_ST,   // Store 
  OP_CALL, // Call
  OP_EP,   // Exit Procedure 
  OP_EF,   // Exit Function
  OP_RC,   // Read Char 
  OP_RI,   // Read Integer
  OP_WRC,  // Write Char    
  OP_WRI,  // Write Int
  OP_WLN,  // WriteLN 
  OP_ADD,  // Add 
  OP_SUB,  // Substract
  OP_MUL,  // Multiple
  OP_DIV,  // Divide
  OP_NEG,  // Negative
  OP_CV,   // Copy Top
  OP_EQ,   // Equal
  OP_NE,   // Not Equal
  OP_GT,   // Greater
  OP_LT,   // Less
  OP_GE,   // Greater or Equal
  OP_LE,   // Less or Equal
  OP_BP    // Break point.
} OpCode ;

typedef struct{
  OpCode op;
  int p;
  int q;
} Instruction;

#define MAX_CODE 1000
#define MAX_DATA 100000
#define OPCODE_COUNT 31 // khong tinh OP_NULL

void intepreter();
int base(int L);
