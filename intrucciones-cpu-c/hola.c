#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define DATA_MEM_SIZE 65536
#define PROG_MEM_SIZE 65536
#define NUM_REGS 16

enum {
    OP_ADD = 0,
    OP_LW  = 2,
    OP_SW  = 3,
    OP_BEQ = 4,
    OP_J   = 14
};

typedef struct {
    uint32_t pc;
    uint32_t psw;

    uint32_t regs[NUM_REGS];

    uint8_t  data_memory[DATA_MEM_SIZE];
    uint32_t program_memory[PROG_MEM_SIZE];

} CPU;

static inline uint32_t opcode(uint32_t instr) {
    return instr & 0xF;
}

static inline uint32_t rd(uint32_t instr) {
    return (instr >> 4) & 0xF;
}

static inline uint32_t rs1(uint32_t instr) {
    return (instr >> 8) & 0xF;
}

static inline uint32_t rs2(uint32_t instr) {
    return (instr >> 12) & 0xF;
}

static inline int16_t imm4(uint32_t instr) {
    int16_t x =
        (instr >> 16) & 0xF;

    if (x & 0x8)
        x |= 0xFFF0;

    return x;
}

static inline uint32_t jump_addr(uint32_t instr) {
    return (instr >> 4) & 0xFFFF;
}

uint16_t mem_read16(CPU *cpu, uint16_t addr) {

    if (addr + 1 >= DATA_MEM_SIZE) {

        printf("Lectura fuera de memoria\n");

        return 0;
    }

    return
        cpu->data_memory[addr] |
        (cpu->data_memory[addr + 1] << 8);
}

void mem_write16(CPU *cpu, uint16_t addr, uint16_t value) {

    if (addr + 1 >= DATA_MEM_SIZE) {

        printf("Escritura fuera de memoria\n");

        return;
    }

    cpu->data_memory[addr] =
        value & 0xFF;

    cpu->data_memory[addr + 1] =
        (value >> 8) & 0xFF;
}

int cpu_step(CPU *cpu) {

    if (cpu->pc >= PROG_MEM_SIZE) {
        printf("PC fuera de rango\n");
        return 0;
    }

    uint32_t instr = cpu->program_memory[cpu->pc];

    instr &= 0xFFFFF;

    cpu->pc++;

    switch (opcode(instr)) {

        case OP_ADD: {

            uint32_t d = rd(instr);
            uint32_t a = rs1(instr);
            uint32_t b = rs2(instr);

            cpu->regs[d] =
                cpu->regs[a] +
                cpu->regs[b];

            break;
        }

        case OP_LW: {
        
            uint32_t d = rd(instr);
            uint32_t a = rs1(instr);
        
            int16_t offset =
                imm4(instr);
        
            uint16_t addr =
                cpu->regs[a] + offset;
        
            cpu->regs[d] =
                mem_read16(cpu, addr);
        
            break;
        }

        case OP_SW: {

            uint32_t s = rd(instr);
            uint32_t a = rs1(instr);
        
            int16_t offset =
                imm4(instr);
        
            uint16_t addr =
                cpu->regs[a] + offset;
        
            mem_write16(
                cpu,
                addr,
                cpu->regs[s]
            );
        
            break;
        }

        case OP_BEQ: {
        
            uint32_t a = rd(instr);
            uint32_t b = rs1(instr);
        
            int16_t offset =
                imm4(instr);
        
            if (cpu->regs[a] ==
                cpu->regs[b]) {
        
                cpu->pc =
                    (uint16_t)(
                        (int16_t)
                        cpu->pc +
                        offset
                    );
            }
        
            break;
        }

        case OP_J: {
        
            cpu->pc = jump_addr(instr);
        
            break;
        }

        default:
            printf("Opcode inválido: %u\n", opcode(instr));
            return 0;
    }

    return 1;
}

uint32_t encode_r(uint32_t op,
                  uint32_t d,
                  uint32_t a,
                  uint32_t b) {

    return
        (op & 0xF) |
        ((d & 0xF) << 4) |
        ((a & 0xF) << 8) |
        ((b & 0xF) << 12);
}

uint32_t encode_i(uint32_t op,
                  uint32_t d,
                  uint32_t a,
                  int8_t imm) {

    return
        (op & 0xF) |
        ((d & 0xF) << 4) |
        ((a & 0xF) << 8) |
        (((uint32_t)imm & 0xF) << 16);
}

uint32_t encode_j(uint32_t addr) {

    return
        ((addr & 0xFFFF) << 4) |
        OP_J;
}

int main() {
    
    return 0;
}
