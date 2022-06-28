#include <stdio.h>
#include <stdint.h>

#define MEM_SIZE 4096
int32_t mem[MEM_SIZE]; //4096 palavras (de 32-bits), 16384 bytes (de 8-bits)
int32_t ret, ret2;

int32_t main() {
  int32_t lw(uint32_t, int32_t);
  int32_t lb(uint32_t, int32_t);
  int32_t lbu(uint32_t, int32_t);
  void sw(uint32_t, int32_t, int32_t);
  void sb(uint32_t, int32_t, int8_t);
  int8_t b1, b2, b3, b4;
  int32_t w1, w2, w3, w4;
  int32_t temp_print;

  //leitura 1
  scanf("%hhx,%hhx,%hhx,%hhx", &b1, &b2, &b3, &b4);
  sb(0,0,b1); //0x04
  sb(1,0,b2);
  sb(2,0,b3);
  sb(3,0,b4);
  //leitura 2
  scanf("%hhx,%hhx,%hhx,%hhx", &b1, &b2, &b3, &b4);
  sb(4,0,b1); //0xff
  sb(5,0,b2);
  sb(6,0,b3);
  sb(7,0,b4);
  //leitura 3
  scanf("%x %x %x %x", &w1, &w2, &w3, &w4);
  sw(8,0,w1); //0xff
  sw(12,0,w2);
  sw(16,0,w3);
  sw(20,0,w4);
  // ler da memoria
  printf("%08x\n", mem[0]);
  printf("%08x\n", mem[1]);
  printf("%08x\n", mem[2]);
  printf("%08x\n", mem[3]);
  printf("%08x\n", mem[4]);
  printf("%08x\n", mem[5]);

  // ler pelos metodos
  temp_print = (lb(4,3) << 24) | (lb(4,2) << 16) | (lb(4,1) << 8) | lb(4,0);
  printf("%08x\n",temp_print);
  temp_print = (lbu(4,3) << 24) | (lbu(4,2) << 16) | (lbu(4,1) << 8) | lbu(4,0);
  printf("%08x\n",temp_print);
  printf("%08x\n",lw(12,0));
  printf("%08x\n",lw(16,0));
  printf("%08x\n",lw(20,0));

};

int32_t lw(uint32_t address, int32_t kte) {
  int32_t endereco = address + kte;
  int32_t mem_value;
  
  if (endereco % 4 != 0) {
    printf("Erro: endereco nao e multiplo de 4.\n");
    return 0;
  } else {
    int mem_index = endereco >> 2;
    mem_value = mem[mem_index];
    
    return mem_value;
  }
};

int32_t lb(uint32_t address, int32_t kte) {
  uint32_t mask  = 0x000000ff;
  uint32_t sub_address;
  int32_t mem_value;
  int8_t mem_byte;
  
  address = address + kte;
  sub_address = address % 4;
  
  int mem_index = address >> 2;
  mem_value = mem[mem_index];

  mask = mask << sub_address * 8;
  mem_byte = mask & mem_value;
  mem_byte = mem_byte >> sub_address * 8;

  int32_t extended_byte = mem_byte;
  return extended_byte;
  
};

int32_t lbu(uint32_t address, int32_t kte) {
  uint32_t mask = 0x000000ff;
  uint32_t sub_address;
  uint32_t mem_value;
  uint8_t mem_byte;

  address = address + kte;
  sub_address = address % 4;
  
  int mem_index = address >> 2;
  mem_value = mem[mem_index];
  
  mask = mask << sub_address * 8;
  mem_byte = mask & mem_value;
  mem_byte = mem_byte >> sub_address * 8;
  
  mask = mask >> sub_address * 8;
  mem_byte = mask & mem_byte;

  return mem_byte;
  
};

void sw(uint32_t address, int32_t kte, int32_t dado) {
  int32_t endereco = address + kte;
  
  if (endereco % 4 != 0) {
    printf("Erro: endereco nao e multiplo de 4.\n");
  } else {
    int mem_index = endereco >> 2;
    mem[mem_index] = dado;
  }
};

void sb(uint32_t address, int32_t kte, int8_t dado) {
  uint32_t dado_mask   = 0x000000ff;
  uint32_t erase_mask  = 0x000000ff;
  uint32_t sub_address;
  int32_t mem_value;

  address = address + kte;
  sub_address = address % 4;

  int mem_index = address >> 2;
  mem_value = mem[mem_index];

  dado_mask = dado_mask & dado;
  dado_mask = dado_mask << sub_address * 8;

  erase_mask = erase_mask << sub_address * 8;
  erase_mask = ~erase_mask;
  int32_t erased_value = mem_value & erase_mask;
  int32_t written_value = erased_value ^ dado_mask;

  mem[mem_index] = written_value;
};

