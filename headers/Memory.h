#include "Register.h"
// Memory of 16X8
typedef struct Memory {
  uint16_t m[256];
  REG_t regMem;
} Mem_t;
// reset the Memory
void newMem(Mem_t* mem){
  for(int16_t i=0;i<256;i++) mem->m[i]=0x0000;
}
// load the Memory from binary file

void readCode(Mem_t* mem, char text[]){
  newMem(mem);
  FILE* file = fopen(text,"rb");
  if(!file) {printf("couldn't open file\n");exit(1);}
  uint16_t buff;
  uint8_t i = 0;
  while(fread(&buff,sizeof(buff),1,file)){mem->m[i++] = buff;}
  fclose(file);
  printf("file readed...\n");
}
// print the contenu of the Memory
// output came with the form : first two caracters is for Address and second two caracters is for Instruction
void printCode(Mem_t* mem){
  printf("\nMemory Content\n-------------------------------------------------------------------------------\n");
  uint8_t i = 0;
  for(uint16_t* p = mem->m; p < mem->m+256;p++){
    printf("%04x ",*p);
    i++;
    if(i%16==0) printf("\n");
  }
  printf("-------------------------------------------------------------------------------\n");
}
// store on the Memory in specific address
void loadMem(Mem_t* mem, uint16_t value){
  mem->m[mem->regMem.content] = value;
}
// load from the Memory in specific address
uint16_t outMem(Mem_t* mem){
  return mem->m[mem->regMem.content];
}
