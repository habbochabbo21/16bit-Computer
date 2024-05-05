#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifndef REGISTER_H
#define REGISTER_H
// Register of 2Byte capacity memory
typedef struct Register {
    uint16_t content;
} REG_t;
// reset the register
REG_t newREG(){
  REG_t reg;
  reg.content = 0;
  return reg;
}
// Store to the register
void loadREG(REG_t* reg, uint16_t value){
  reg->content = value;
}
// clear the contenu of the register
void clearREG(REG_t* reg){
  reg->content = 0;
}
// load the contenu from the register
uint16_t outREG(REG_t* reg){
  return reg->content;
}
#endif
