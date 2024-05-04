#include <stdint.h>

typedef struct Arithmetic_Logic_Unit {
    uint16_t a,b;
} ALU_t;

void setA(ALU_t* alu, uint16_t value){
    alu->a = value;
    alu->b = 0;
}

void setB(ALU_t* alu, uint16_t value){
    alu->a = 0;
    alu->b = value;
}

void setAB(ALU_t* alu, uint16_t valueA, uint16_t valueB){
    alu->a = valueA;
    alu->b = valueB;
}

uint16_t Calc(ALU_t* alu, uint8_t op){
    // NOP
    if(!op) return 0;
    // ADD
    else if(op & 0b00000001) return alu->a + alu->b;
    // SUB
    else if(op & 0b00000010) return alu->a + alu->b;
    // MULL
    else if(op & 0b00000011) return alu->a + alu->b;
    // DIV
    else if(op & 0b00000100) return (alu->b)?-1:alu->a + alu->b;
    // Other
    else return -1;
}