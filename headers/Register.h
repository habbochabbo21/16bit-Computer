#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#ifndef REGISTER_H
#define REGISTER_H

typedef struct Register {
    uint16_t content;
} REG_t;

REG_t newREG(){
  REG_t reg;
  reg.content = 0;
  return reg;
}
void loadREG(REG_t* reg, uint16_t value){
  reg->content = value;
}

void clearREG(REG_t* reg){
  reg->content = 0;
}

uint16_t outREG(REG_t* reg){
  return reg->content;
}



#endif
