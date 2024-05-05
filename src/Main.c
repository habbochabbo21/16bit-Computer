#include "../headers/Counter.h"
#include "../headers/ALU.h"
#include "../headers/Memory.h"

typedef struct Computer {
  REG_t regA,regB,regInst;
  COUNT_t count;
  ALU_t alu;
} CPU_t;

int isRuning = 1;

uint8_t Execute(CPU_t* cpu,Mem_t* mem){
  switch((cpu->regInst.content & 0xFF00)>>8){
    // NOP
    case 0x00:
    break;
    // Load from Memory to A register
    case 0x01:{
      loadREG(&mem->regMem,outREG(&cpu->regInst)& 0x00ff);
      loadREG(&cpu->regA,outMem(mem));
    }break;
    // Load from Memory to B register
    case 0x02:{
      loadREG(&mem->regMem,outREG(&cpu->regInst)& 0x00ff);
      loadREG(&cpu->regB,outMem(mem));
    }break;
    // Store to Memory from A register
    case 0x03:{
      loadREG(&mem->regMem,outREG(&cpu->regInst)& 0x00ff);
      loadMem(mem,outREG(&cpu->regA));
    }break;
    // Store to Memory from B register
    case 0x04:{
      loadREG(&mem->regMem,outREG(&cpu->regInst)& 0x00ff);
      loadMem(mem,outREG(&cpu->regB));
    }break;
    // ADD A to B
    case 0x05:{
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,1));
    }break;
    // SUB B from A
    case 0x06:{
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,2));
    }break;
    // SUB A from B
    case 0x07:{
      setAB(&cpu->alu,outREG(&cpu->regB),outREG(&cpu->regA));
      loadREG(&cpu->regA,Calc(&cpu->alu,2));
    }break;
    // MUL A with B
    case 0x08:{
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,3));
    }break;
    // DIV A by B
    case 0x09:{
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,4));
    }break;
    // DIV B by A
    case 0x0A:{
      setAB(&cpu->alu,outREG(&cpu->regB),outREG(&cpu->regA));
      loadREG(&cpu->regA,Calc(&cpu->alu,4));
    }break;
    // NOT A
    case 0x0B:{
      setB(&cpu->alu,outREG(&cpu->regA));
      loadREG(&cpu->regA,Calc(&cpu->alu,5));
    }break;
    // NOT B
    case 0x0C:{
      setB(&cpu->alu,outREG(&cpu->regB));
      loadREG(&cpu->regB,Calc(&cpu->alu,5));
    }break;
    // A AND B
    case 0x0D:{
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,6));
    }break;
    // A OR B
    case 0x0E:{
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,7));
    }break;
    // A XOR B
    case 0x0F:{
      setAB(&cpu->alu,outREG(&cpu->regA),outREG(&cpu->regB));
      loadREG(&cpu->regA,Calc(&cpu->alu,8));
    }break;
    
    // OUT A
    case 0xFE:{
      printf("%04x\n",outREG(&cpu->regA));
    }break;
    // HLT
    case 0xFF:
      isRuning = 0;
    break;
    default:
      perror("Instruction undefined!\n");
      return 1;
    break;
  }
  return 0;
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
    printf("count:%04x|A:%04x|B:%04x|Inst:%02x|InstV:%02x|Mem:%04x|\n",outCount(&cpu.count),outREG(&cpu.regA),outREG(&cpu.regB),(outREG(&cpu.regInst)& 0xFF00)>>8,outREG(&cpu.regInst)&0x00ff,outREG(&mem.regMem));
    incrCount(&cpu.count);
    if(Execute(&cpu,&mem)) exit(1);
  }

  return 0;
}
