typedef struct Register {
  short content;
} REG_t;
REG_t newREG(){
  REG_t reg;
  reg.content = 0;
  return reg;
}
void clearREG(REG_t* reg){
  reg->content = 0;
}

