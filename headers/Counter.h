#include "Register.h"
// 16 Byte memory Counter
typedef struct Counter {
  REG_t reg;
} COUNT_t;
// reset Counter
void newCOUT(COUNT_t* count){
  count->reg.content = 0;
}
// Jump to the address giving
void loadCOUT(COUNT_t* count, uint16_t value){
  count->reg.content = value;
}
// increment the counter
void incrCount(COUNT_t* count){
  uint16_t c = count->reg.content;
  c += 0b00000001;
  count->reg.content = c;
}
// descriment the counter
void decrCount(COUNT_t* count){
  uint16_t c = count->reg.content;
  c -= 0b00000001;
  count->reg.content = c;
}
// out the address on the counter
uint16_t outCount(COUNT_t* count){
  return count->reg.content;
}
