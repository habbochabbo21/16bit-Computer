#include "Register.h"

typedef struct Counter {
  REG_t reg;
} COUNT_t;

void newCOUT(COUNT_t* count){
  count->reg.content = 0;
}

void loadCOUT(COUNT_t* count, uint16_t value){
  count->reg.content = value;
}

void incrCount(COUNT_t* count){
  uint16_t c = count->reg.content;
  c += 0b00000001;
  count->reg.content = c;
}

void decrCount(COUNT_t* count){
  uint16_t c = count->reg.content;
  c -= 0b00000001;
  count->reg.content = c;
}

uint16_t outCount(COUNT_t* count){
  return count->reg.content;
}
