#ifndef FLOAT_H
#define FLOAT_H

typedef int float_32;

//use 16 bits to save the part after "."

#define FLOAT_32(A) ((float_32)(A<<16))
#define ADD_FLOAT(A,B) (A+B)
#define ADD_B_IS_INT(A,B) ADD_FLOAT(A,(B<<16))
#define SUB_FLOAT(A,B) (A-B)
#define SUB_B_IS_INT(A,B) SUB_FLOAT(A,(B<<16))
#define MULT_FLOAT(A,B) ((float_32)((((int64_t) A)*B)>>16))
#define MULT_B_IS_INT(A,B) A*B
#define DIV_FLOAT(A,B) ((float_32)((((int64_t) A)<<16)/B))
#define DIV_B_IS_INT(A,B) A/B
#define INT_16(A) ((int)(A>>16))

#define ROUNDING(A) (A>=0? ((A+(1<<15))>>16):((A-(1<<15))>>16))

#endif

