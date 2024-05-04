#include "Register.h"

typedef struct Counter {
  REG_t reg;
} COUNT_t;

COUNT_t newCOUT(){
  COUNT_t cout;
  cout.reg.content = 0;
  return cout;
}

void loadCOUT(COUNT_t* count, int16_t value){
  count->reg.content = value;
}

void incrCount(COUNT_t* count){
  short c = count->reg.content;
  c += 0b00000001;
  count->reg.content = c;
}

void decrCount(COUNT_t* count){
  short c = count->reg.content;
  c -= 0b00000001;
  count->reg.content = c;
}

short outCount(COUNT_t* count){
  return count->reg.content;
}
