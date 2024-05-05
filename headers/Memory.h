#include "Register.h"

typedef struct Memory {
  uint16_t m[256];
  REG_t regMem;
} Mem_t;

void preapreMem(Mem_t* mem){
  for(int16_t i=0;i<256;i++) mem->m[i]=0x0;
}

void readCode(Mem_t* mem, char text[]){
  preapreMem(mem);
  FILE* file = fopen(text,"rb");
  if(!file) {printf("couldn't open file\n");exit(1);}
  uint16_t buff;
  uint8_t i = 0;
  while(fread(&buff,sizeof(buff),1,file)){mem->m[i++] = buff;}
  fclose(file);
  printf("file readed...\n");
}

void printCode(Mem_t* mem){
  for(uint16_t* p = mem->m; p < mem->m+256;p++){
    printf("%04x ",*p);
  }
  printf("\nPreaparing the Execute...\n");
}

void loadMem(Mem_t* mem, uint16_t value){
  mem->m[mem->regMem.content] = value;
}
uint16_t outMem(Mem_t* mem){
  return mem->m[mem->regMem.content];
}
