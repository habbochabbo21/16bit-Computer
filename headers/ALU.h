#include <stdint.h>

typedef struct Arithmetic_Logic_Unit {
    uint16_t a,b;
} ALU_t;
// set the value of port a if you want just to do the operation  to a 
void setA(ALU_t* alu, uint16_t value){
    alu->a = value;
    alu->b = 0;
}
// set the value to port b if you want just to do the operation to b
void setB(ALU_t* alu, uint16_t value){
    alu->a = 0;
    alu->b = value;
}
// set the value to ports a et b if you want to do the operation to a et b
void setAB(ALU_t* alu, uint16_t valueA, uint16_t valueB){
    alu->a = valueA;
    alu->b = valueB;
}
// the ALU will do a operation back to the microcode op
uint16_t Calc(ALU_t* alu, uint8_t op){
    // NOP
    if(!op) return 0;
    // ADD
    else if(op & 0b00000001) return alu->a + alu->b;
    // SUB
    else if(op & 0b00000010) return alu->a - alu->b;
    // MULL
    else if(op & 0b00000011) return alu->a * alu->b;
    // DIV
    else if(op & 0b00000100) return (alu->b)?-1:alu->a / alu->b;
    // NOT
    else if(op & 0b00000101) return ~(alu->b);
    // AND
    else if(op & 0b00000110) return alu->a&alu->b;
    // OR
    else if(op & 0b00000111) return alu->a|alu->b;
    // XOR
    else if(op & 0b00001000) return alu->a^alu->b;
    // Other
    else return -1;
}