#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Register {
  short content;
} REG_t;
REG_t newREG(){
  REG_t reg;
  return reg;
}
void clearREG(REG_t* reg){
  reg->content = 0;
}

struct Counter {
  REG_t reg;
  char der;
} COUT_t;
COUT_t newCOUT(){
  COUT_t cout;
  cout.reg = 0;
  cout.der = 0;
  return cout;
}
