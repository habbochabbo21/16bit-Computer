#include "../headers/Counter.h"
#include "../headers/ALU.h"
#include "../headers/Memory.h"

#define TRUE 1
#define FALSE 0

typedef struct Computer {
  REG_t regA,regB,regInst;
  COUNT_t pc,sp,rp;
  ALU_t alu;
} CPU_t;
void newCPU(CPU_t* cpu){
  newREG(&cpu->regA);
  newREG(&cpu->regB);
  newREG(&cpu->regInst);
  newCOUT(&cpu->pc);
  loadCOUT(&cpu->sp,0x100);
  newCOUT(&cpu->rp);
}
// Holt signal
uint8_t isRuning = TRUE;
// execute the code on the Memory
uint8_t Execute(CPU_t* cpu,Mem_t* mem){
  switch(cpu->regInst.content & 0x00FF){
    // NOP
    case 0x00:
    break;
    // Load from Memory to A register
    case 0x01:{
      loadREG(&mem->regMem,(outREG(&cpu->regInst)& 0xFF00)>>8);
      loadREG(&cpu->regA,outMem(mem));
    }break;
    // Load from Memory to B register
    case 0x02:{
      loadREG(&mem->regMem,(outREG(&cpu->regInst)& 0xFF00)>>8);
      loadREG(&cpu->regB,outMem(mem));
    }break;
    // Store to Memory from A register
    case 0x03:{
      loadREG(&mem->regMem,(outREG(&cpu->regInst)& 0xFF00)>>8);
      loadMem(mem,outREG(&cpu->regA));
    }break;
    // Store to Memory from B register
    case 0x04:{
      loadREG(&mem->regMem,(outREG(&cpu->regInst)& 0xFF00)>>8);
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
    // Shift to left
    case 0x10:{}break;
    // Sheft to right
    case 0x11:{}break;
    // Rotate to left
    case 0x12:{}break;
    // Rotate to right
    case 0x13:{}break;
    // Push A into Stack
    case 0x14:{
      decrCount(&cpu->sp);
      loadREG(&mem->regMem,outCount(&cpu->sp));
      loadMem(mem,outREG(&cpu->regA));
    }break;
    // Push B into Stack
    case 0x15:{
      decrCount(&cpu->sp);
      loadREG(&mem->regMem,outCount(&cpu->sp));
      loadMem(mem,outREG(&cpu->regB));
    }break;
    // Pop from Stack into A
    case 0x16:{
      loadREG(&mem->regMem,outCount(&cpu->sp));
      incrCount(&cpu->sp);
      loadREG(&cpu->regA,outMem(mem));
    }break;
    // Pop from Stack into B
    case 0x17:{
      loadREG(&mem->regMem,outCount(&cpu->sp));
      incrCount(&cpu->sp);
      loadREG(&cpu->regB,outMem(mem));
    }break;
    // Call
    case 0x18:{
      loadCOUT(&cpu->rp,outCount(&cpu->pc));
      loadCOUT(&cpu->pc,(outREG(&cpu->regInst)& 0xFF00)>>8);
    }break;
    // Return
    case 0x19:{
      loadCOUT(&cpu->pc,outCount(&cpu->rp));
    }break;
    // Jump
    case 0x20:{
      loadCOUT(&cpu->pc,(outREG(&cpu->regInst)& 0xFF00)>>8);
    }break;
    
    // 
    case 0xFD:{}break;
    // OUT A
    case 0xFE:{
      printf("%04d\n",outREG(&cpu->regA));
    }break;
    // HLT
    case 0xFF:
      isRuning = FALSE;
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
  newCPU(&cpu);
  printf("\nPreaparing the Execute...\n");
  while(isRuning){
    loadREG(&mem.regMem,outCount(&cpu.pc));
    loadREG(&cpu.regInst,outMem(&mem));
    printf("PC:%04x|SP:%04x|RP:%04x|A:%04x|B:%04x|Inst:%02x|InstV:%02x|Mem:%04x|\n",outCount(&cpu.pc),outCount(&cpu.sp),outCount(&cpu.rp),outREG(&cpu.regA),outREG(&cpu.regB),outREG(&cpu.regInst)& 0x00FF,(outREG(&cpu.regInst)&0xFF00)>>8,outREG(&mem.regMem));
    incrCount(&cpu.pc);
    if(Execute(&cpu,&mem)) exit(1);
  }
  printCode(&mem);

  return 0;
}
