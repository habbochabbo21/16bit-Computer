#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "header\Counter.h"

int main(){
  REG_t reg = newREG();
  loadREG(&reg,1);
  printf("%x\n",outREG(&reg));
  COUNT_t counter = newCOUT();
  loadCOUT(&counter, 5);
  incrCount(&counter);
  printf("%x\n",outCount(&counter));
  return 0;
}
