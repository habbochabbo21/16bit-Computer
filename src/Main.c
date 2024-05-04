#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../headers/Counter.h"
#include "../headers/ALU.h"

typedef struct Computer {
  REG_t regA,regB,regInst;
  COUNT_t count;
  ALU_t alu;
} CPU_t;

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
    printf("%02x",*p);
  }
  printf("\nPreaparing the Execute...\n");
}

void loadMem(Mem_t* mem, uint16_t value){
  mem->m[mem->regMem.content] = value;
}
uint16_t outMem(Mem_t* mem){
  return mem->m[mem->regMem.content];
}

int isRuning = 1;

void Execute(CPU_t* cpu,Mem_t* mem){
  switch(cpu->regInst.content & 0xFF00){
    case 0x00:
    break;
    case 0x01:{
      loadREG(&mem->regMem,outREG(&cpu->regInst)>>8);
      loadREG(&cpu->regA,outMem(mem));
    }break;
    case 0x02:{
      loadREG(&mem->regMem,outREG(&cpu->regInst)>>8);
      loadREG(&cpu->regB,outMem(mem));
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,1));
    }break;
    case 0x03:{
      loadREG(&mem->regMem,outREG(&cpu->regInst)>>8);
      loadREG(&cpu->regB,outMem(mem));
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,2));
    }break;
    case 0x04:break;
    case 0xFE:{
      printf("%02x",outREG(&cpu->regA));
    }      
    break;
    case 0xFF:
      isRuning = 0;
      break;
    
  }
}

int main(int argc, char* argv[]){
  Mem_t mem;
  CPU_t cpu;
  readCode(&mem,argv[1]);
  printCode(&mem);
  newCOUT(&cpu.count);
  while(isRuning){
    loadREG(&mem.regMem,outCount(&cpu.count));
    loadREG(&cpu.regInst,outMem(&mem));
    incrCount(&cpu.count);
    Execute(&cpu,&mem);
  }

  return 0;
}
